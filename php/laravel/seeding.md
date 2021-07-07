db 테이블에 데이터를 심는 행위를 시딩이라고 하고 이는 서비스 구성에 필요한 기본 데이터, 개발 중에 필요한 데이터, 테스트를 위한 데이터를 빨게 준비할 때 사용한다.

라라벨은 클래스 문법으로 데이터 시딩을 자동화할 수 있는 방법을 제공하고 있다.

```sh
$ php artisan make:seeder UsersTableSeeder
```
위 명령어를 치면 database/seeds 하위에 생성이 되고 클래스 이름은 자유롭게 지으면 된다. 클래스 내부의 run()메서드를 이용해 시딩이 이루어지기 때문에 시딩 로직을 넣어주면 된다.

<br>

```php
class UsersTableSeeder extends Seeder
{
    public function run()
    {
        App\User::create([
            'name'=> sprintf('%s %s',str_random(3), str_random(4)),
            'email' => str_random(10) . '@example.com',
            'password' => bcrypt('password'),
        ]);
    }
}

```

<br><br>

## 마스터 시더
모델마다 아티즌 시딩 명령을 수행하는 것은 번거롭기 때문에 시더 클래스를 한번에 등록할 수 있는 마스터 시더 클래스를 사용하는 것이 편하고 이를 이용해서 수행해야 하는 이유는 시딩의 순서때문이다. 각 테이블간의 연관관계가 없다면 모르겠지만 존재한다면 시딩하는 순서도 중요하기 때문이다. (없는 컬럼에 종속된 컬럼은 삽입이 불가능하기 때문에)

```php
class DatabaseSeeder extends Seeder{
    public function run(){
        if(config('database.default') !== 'sqlite'){
            DB::statement('SET FOREIGN_KEY_CHECKS=0');
        }

        //Model::unguard();

        App\User::truncate();
        $this->call(UsersTableSeeder::class);

        App\Article::truncate();
        $this->call(ArticlesTableSeeder::class);

        //Model::reguard();

        if(config('database.default') !== 'sqlite'){
            DB::statement('SET FOREIGN_KEY_CHECKS=1');
        }
    }
}
```
Model::unguard()와 Model::reguard() 메서드는 엘로퀀트 모델에 정의한 대량 할당 제약 사항을 풀었다가 잠그는 명령으로 라라벨5.2이상은 시딩할 때 자동으로 풀고 잠근다.

- config('database.default') : config/database.php파일에서 default키에 할당된 값을 읽어오는 구문으로 db종류가 반환된다. sqlite는 외부키를 꺼두는 기능을 지원하지 않기 때문에 예외처리한 구문
- truncate() : 테이블에 담긴 모든 데이터를 버리는 메서드로, delete()와 같을 수 있지만 이는 기본키를 1로 재배열한다.
- call() : $class::run() 메서드의 본문을 실행하고 콘솔에 결과를 출력한다.

`php artisan db:seed`로 마스터 시드를 시딩할 수 있다.

<br>

`php artisan migrate:refresh --seed` : 마이그레이션과 시딩을 한번에 실행