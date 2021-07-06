## tinker 
`repl`은 콘솔 환경에서 명령을 내리고 실행 결과를 확인하기 위해 사용하는 도구이며 tinker는 라라벨이 제공하는 repl이다.

`php artisan tinker`로 tinker를 실행할 수 있다.

```php
>>> DB::select('SELECT * FROM posts');
>>> DB::insert('INSERT INTO posts(title,body) VALUES(?.?), ['Hello','Hi']);
>>> $posts = DB::select('SELECT * FROM posts');
>>> $posts[0]->title;
>>> $posts = DB::selectOne('SELECT * FROM WHERE id = ?',[1]);
```
tinker콘솔에 위와 같이 `DB::insert()/selct()`등으로 쿼리를 실행할 수 있고 이때 DB는 라라벨의 특수한 문법인 `파사드(Facade)`라고 한다.

위와 같이 직접 쿼리문을 작성할 수도 있지만 실전에서는 거의 사용하지 않는다.

<br>

## 쿼리 빌더
SQL문장을 php클래스 문법으로 사용한 것으로 메서드를 통해 자동으로 query를 build해준다.

### get
```php
>>> DB::table('posts')->get();
>>> DB::table('posts')->first();
>>> DB::table('posts')->find(2);
>>> DB::table('posts')->get(['Hello','id']);
```

### where
```php
>>> DB::table('posts')->where('id', '=', 1)->get();
>>> DB::table('posts')->where('id', 1)->get();
>>> DB::table('posts')->whereId(1)->get();
>>> DB::table('posts')->where(function ($query){query -> where('id',1);})->get();
```
4개 모두 같은 결과를 반환하며, 첫번째와 같이 조건절이 `=`일 경우에는 생략이 가능하다. 3번째 방법은 메서드명을 보고 동적으로 쿼리를 작성해주는 방식으로 `카멜표기법`으로 표기하면 되고, 복잡한 조건일 경우에는 클로저를 이용할 수도 있다.

이외에도 `insert(array $v)`,`update(associate array $v)`, `delete(int $id)`, `pluck(string $col, string $key = null)`, `limit(int $v)`, `orderBy(string $col, string $dir='asc')`, count, distinct,join, union등 웬만한 SQL문을 메서드로 표현가능하다.

<br><br>

## 엘로퀀트 
라라벨이 제공하는 ORM구현체로 DB와 객체간 맵핑기술

### 모델 만들기
```sh
$ php artisan make:model Post
$ php artisan make:model Author
```
직접 타이핑해서 만들어도 되지만 아티즌명령어 인터페이스로 모델의 뼈대 코드를 빠르게 생성이 가능하며 `app/Models/`하위에 생성이된다.

```php
<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Factories\HasFactory;
use Illuminate\Database\Eloquent\Model;

class Post extends Model
{
    use HasFactory;
}
```
자동으로 위와 같이 만들어지는데 `Illuminate\Database\Eloquent\Model`를 상속하기만하면 모델로 사용된다.

보통 테이블이름은 여러컬럼을 가지고있기 때문에 복수로 짓지만 모델은 하나의 인스턴스만 담고 있기 대문에 주로 단수로 짓는다. 이때문에 자동으로 단수가 복수로 변경되 맵핑되고, 다른 이름으로 맵핑을 하고자 한다면 `protected $table = '특정 이름';`을 정의해 명시해주어야 한다.

<br>

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

`bcrypt()`는  60바이트짜리 단방향 해시를 만드는 도우미 함수로 복호화가 불가능하기때문에 비밀번호 찾기가 불가능하다.

위 코드를 실행시켜보면 `MassAssignmentException`이 발생하는데 이는 엘로퀀트 자체에서 해커의 대량 할당 공격을 보호하기 위한 예외이다. 이를 허용하기 위해서는 두가지 방법을 제공하는데 하나는 `$fillable` 프로퍼티를 이용하는 허용목록 방식이고, 하나는 