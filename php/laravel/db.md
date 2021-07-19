## db 마이그레이션

테이블 스키마의 버전관리로 테이블에 새로운 열을 추가,수정 이력을 남겨 롤백하는 등의 작업을 수행할 수 있게 해준다.

<br><br>

## 마이그레이션이 필요한 이유

1. 모던 개발 방법론

   팀 내 개발자들은 같은 스키마로 개발해야 하기 때문에 개발환경뿐만 아니라 운영환경을 쉽고 빠르게 만들수 있게 해준다.

1. 시간이지남에 따라 요구사항이 바뀌고 모델링이 바뀌게 되기도 하고, 실수가 발생했을때 빠르게 롤백해야 하는 상황하는 것과 같이 효과적으로 대응할 수 있기 때문이다.

<br><br>

## 만드는 방법

```sh
$ php artisan make:migration create_posts_table --create=posts
$ php artisan make:migration create_authors_table --create=authors
```

생성을 하면 `database/migrations`디렉토리 하위에 생성되고 관례적으로 `스네이크 표기법`을 사용해서 `create_`,`make_`,`add_`,`drop_`,`change_`등으로 시작하고 `_table`로 끝난다.

옵션으로 --create옵션을 주면 up과 down이 create와 drop으로 생성이 되고, --table옵션을 주면 up(),down()메서드가 table()메서드로 자동생성된다.

### create옵션

```php
class CreatePostsTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('posts', function (Blueprint $table) {
            $table->id();
            $table->timestamps();
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('posts');
    }
}

```

### table 옵션

```php
class CreateExampleTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::table('example', function (Blueprint $table) {
            //
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::table('example', function (Blueprint $table) {
            //
        });
    }
}
```

<br>

```php
class CreateAuthorsTable extends Migration
{
    /**
     * Run the migrations.
     *
     * @return void
     */
    public function up()
    {
        Schema::create('authors', function (Blueprint $table) {
            $table->increments('id');
            $table->string('email',255);
            $table->string('password',60);
            $table->timestamps();
        });
    }

    /**
     * Reverse the migrations.
     *
     * @return void
     */
    public function down()
    {
        Schema::dropIfExists('authors');
    }
}
```

up()메서드는 마이그레이션을 실행하는 메서드이고 down()은 롤백을 위한 메서드이다. up()내부의 increments()는 자동증가 기본 키 컬럼을 만들고, timestamp()는 created_at과 updated_at 컬럼을 만든다.

create()메서드의 두번째 매개변수는 콜백 함수이고 이 함수의의 매개변수로 `Blueprint`는 타입 힌트로써, 해당 클래스의 인스턴스여야한다고 강제하는 것이다.

- Schema::create() : 테이블을 생성
- Schema::drop() : 테이블을 삭제
- Schema::table() : 테이블을 생성/삭제를 제외한 나머지 스키마 관련 작업들

<br>

### 컬럼타입에 대응되는 메서드 종류

- boolean(), dateTime(), enum(), integer()등과 같은 컬럼타입 메서드
- timestamps(), softDeletes()등의 도우미 메서드
- nullable(), default(), unsinged()등의 장식 메서드
- unique(), index()등의 인덱스 메서드
- dropColumn()

이외에도 [공식문서](https://laravel.com/docs/migrations)을 보면 많은 메서드가 존재한다.

<br><br>

## 실행

```sh
$ php artisan migrate
```

 <br>

## 롤백

```sh
$ php artisan migrate:rollback
```

 <br>

## 초기화

```sh
$ php artisan migrate:refresh
```

<br>

## 작성되는 SQL문 보기

```sh
$ php artisan migrate --pretend
```
