## 엘로퀀트

라라벨이 제공하는 ORM구현체로 DB와 객체간 맵핑기술

### 쿼리

```php
>>> $post = App\Models\Post::get();
```

모델 클래스를 이용해서 쿼리빌더와 같이 메서드로 쿼리를 수행할 수 있는데 이는 Model클래스를 상속받기 때문에 메서드를 이용할 수 있다.

<br>

### save()

```php
>>> $post = App\Models\Post::first();
>>> $post->title = 'foo';
>>> $post->save();  //error발생
```

위에서 save()를 실행하면 예외가 발생하는데, 엘로퀀트는 모든 테이블에 `created_at`,`updated_at`이 있다고 과정하고 현재의 타임스탬프값을 할당하는데 해당 컬럼이 존재하지 않아 발생하는 에러이다. 해당 컬럼을 추가해주거나 타임스탬프 자동입력기능을 끄는 방법으로 해결할 수 있다.

`public $timestamps = false;`을 추가해 자동입력기능을 끌 수 있다.

<br>

### create()

save()메서드는 모델의 프로퍼티 값을 하나씩 할당해주어야 하는데 여러개의 프로퍼티값을 한번에 할당하는 경우에는 create()를 사용하면 편하게 작업할 수 있다.

```php
>>> App\Models\Post::create([
    'email' => 'test@test.com',
    'password' => 'bcrypt('1234')',
]);
```

create()메서드를 이용해 매개변수로 `associate array`를 넘겨주어 값을 할당해 줄 수 있다.

`bcrypt()`는 60바이트짜리 단방향 해시를 만드는 도우미 함수로 복호화가 불가능하기때문에 비밀번호 찾기가 불가능하다.

위 코드를 실행시켜보면 `MassAssignmentException`이 발생하는데 이는 엘로퀀트 자체에서 해커의 대량 할당 공격을 보호하기 위한 예외이다. 이를 위해서는 두가지 방법을 제공하는데 하나는 `$fillable` 프로퍼티를 이용하는 허용목록 방식이고, 하나는 `$guarded`프로퍼티를 이용한 금지목록 방식이다.

<br><br>

## 연관관계

### 1. 일대다 관계

```php
<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

class CreatePostsTable extends Migration
{
    public function up()
    {
        Schema::create('posts', function (Blueprint $table) {
            $table->increments('id');
            $table->integer('user_id')->unsigned()->index();
            $table->timestamps();

            $table->foreign('user_id')->references('id')->on('users')->onUpdate('cascade')->onDelete('cascade');
        });
    }

    public function down()
    {
        Schema::dropIfExists('posts');
    }
}
```

마이그레이션에서 `다(N)`가 되는 쪽에 `foreign()`메서드를 이용해서 테이블끼리의 외래 키 관계를 연결 해주고 모델에서 아래와 같이 연결관계를 표현해주면 된다.

```php
//User
class User extends Authenticatable
{
    use HasFactory, Notifiable;

    protected $fillable = [
        'name',
        'email',
        'password',
    ];

    protected $hidden = [
        'password',
        'remember_token',
    ];

    public function posts(){
        return $this->hasMany(Post::class);
    }
}

//Post
class Post extends Model
{
    use HasFactory;

    protected $fillable = [
        'title',
        'body',
    ];

    public $timestamps = false;

    public function user(){
        return $this->belongsTo(User::class,'custom_user_id');
    }
}
```

각 모델내에서 연관관계설정할 모델이름의 메서드를 만들어 hasMany(), belongsTo()메서드와 같이 접근 할 수 있게 정의 해줄 수 있는데 이때 메서드 명으로 관례상 1이 되는 쪽 모델을 접근하는 메서드는 단수, N이 되는 모델을 접근하는 메서드는 복수를 사용한다. 1이되는쪽에서 N을 연결할때 hasMany()를, N이 되는쪽에서 1을 연결할때 belongsTo()를 이용한다.

외래키 이름은 모델명을 가지고 엘리퀀트가 유추하여 연결하지만 특별한 id로 연결을 원한다면 Post모델의 user()과 같이 매개변수로 외래키 이름을 지정해줄 수 있다.

<br><br>

### 다대다 연결

```php
$ php artisan make:migration create_article_tag_table --create=article_tag

class CreateArticleTagTable extends Migration
{
    public function up()
    {
        Schema::create('article_tag', function (Blueprint $table) {
            $table->increments('id');
            $table->integer('article_id')->unsigned();
            $table->integer('tag_id')->unsigned();

            $table->foreign('article_id')->references('id')->on('articles')->onDelete('cascade');
            $table->foreign('tag_id')->references('id')->on('articles')->onDelete('cascade');
        });
    }

    public function down()
    {
        Schema::dropIfExists('article_tag');
    }
}

```

N:N관계를 연결하기 위해서는 테이블 한개를 더 생성해주어야 한다.

<br>

```php
//Post
class Post extends Model
{
    use HasFactory;

    public $timestamps = false;

    protected $fillable = [
        'title',
        'body',
    ];

    public function user(){
        return $this->belongsTo(User::class,'custom_user_id');
    }

    public function tags(){
        return $this->belongsToMany(Tag::class);
    }
}

//tag
class Tag extends Authenticatable
{
    use HasFactory, Notifiable;

    protected $fillable = [
        'name'
    ];

    public function posts(){
        return $this->belongsToMany(Post::class);
    }
}
```

N:N은 양쪽 다 belongsToMany()를 이용하여 연결을 해주면 되는데 첫번째에서 테이블을 한개더 생성하는 이유는 이 테이블이 N:N관계를 연결시켜주는 피벗 테이블이 되기 때문이다.

<br><br>

## 조회

### all()

```php
$flights = App\Models\Flight::all();

foreach ($flights as $flight) {
    echo $flight->name;
}

```

all()메서드를 통해 테이블을 조회할 수있지만 이는 모든 행이 조회되기 때문에 쿼리빌더와 비슷하게 조건들을 추가할 수 있다.

엘로퀀트 모델은 모두 쿼리빌더이기 때문에 쿼리 빌더의 모든 메서드를 이용할 수 있다.

```php
$flights = App\Models\Flight::where('active', 1)
               ->orderBy('name', 'desc')
               ->take(10)
               ->get();
```

<br>

## cursor()

```php
$users = App\Models\User::cursor()->filter(function ($user) {
    return $user->id > 500;
});

foreach ($users as $user) {
    echo $user->id;
}
```

cursor메서드는 단하나의 쿼리를 실행을 통해 대량의 데이터를 처리 할 수 있어 메모리 사용량을 크게 줄일 수 있다. 이때 반환값으로 `LazyCollection`을 반환하기 때문에 Collection 메서드들을 이용할 수 있다.

<br>

## 삽입

```php
$flight = new Flight;

$flight->name = $request->name;

$flight->save();
```

쿼리빌더의 insert보다 간편하게 save()메서드로 삽입을 수행할 수 있다. 이때 타임스탬프는 자동으로 설정되어 수동으로 지정할 필요가 없다.

또한, 이미 존재하는 행이라면 update를 수행한다.

<br>

## 속성 변경 확인

### isDirty() | isClean()

```php
$user = User::create([
    'first_name' => 'Taylor',
    'last_name' => 'Otwell',
    'title' => 'Developer',
]);

$user->title = 'Painter';

$user->isDirty(); // true
$user->isDirty('title'); // true
$user->isDirty('first_name'); // false

$user->isClean(); // false
$user->isClean('title'); // false
$user->isClean('first_name'); // true

$user->save();

$user->isDirty(); // false
$user->isClean(); // true
```

현재 모델이 db에 flush가 되었는지 각 컬럼별로 확인기 가능하다.

### wasChanged()

```php
$user = User::create([
    'first_name' => 'Taylor',
    'last_name' => 'Otwell',
    'title' => 'Developer',
]);

$user->title = 'Painter';
$user->save();

$user->wasChanged(); // true
$user->wasChanged('title'); // true
$user->wasChanged('first_name'); // false
```

현재 요청주기내에 모델의 속성이 변경되었는지 확인하는 메서드

### getOriginal()

```php
$user = User::find(1);

$user->name; // John
$user->email; // john@example.com

$user->name = "Jack";
$user->name; // Jack

$user->getOriginal('name'); // John
$user->getOriginal(); // Array of original attributes...
```

flush되기 전의 모델의 수정된 이전 값을 확인하는 메서드

<br>

## 대량 할당

모델의 값 프로퍼티를 각각 채워 save()로 저장하는 방법 외에 `create()`메서드를 이용하여 한번에 저장 할 수도 있다.

```php
$flight = App\Models\Flight::create(['name' => 'Flight 10']);
```

하지만, 엘로퀀트는 기본적으로 대량 할당으로부터 보호하기 때문에 사용할 수 없어 `fillable`속성에 컬럼들을 추가해주어야 한다.
