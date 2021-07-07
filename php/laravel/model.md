## 모델 
```php
class User extends Authenticatable
{
    use HasFactory, Notifiable;

    /**
     * The attributes that are mass assignable.
     *
     * @var array
     */
    protected $fillable = [
        'name',
        'email',
        'password',
    ];

    /**
     * The attributes that should be hidden for arrays.
     *
     * @var array
     */
    protected $hidden = [
        'password',
        'remember_token',
    ];

    /**
     * The attributes that should be cast to native types.
     *
     * @var array
     */
    protected $casts = [
        'email_verified_at' => 'datetime',
    ];
}
```
위는 라라벨의 기본적으로 있는 User모델이다.

`fillable`로 대량할당 컬럼이 가능하도록 지정할 수 있고, `hidden`프로퍼티로 조회 쿼리시 제외할 열을 정의할 수 있다.

<br><br>

## 모델 만들기
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

<br><br>

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
