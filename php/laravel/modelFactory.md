더미 데이터를 빠르게 만들기 위한 도구

### 기본 사용 방법
```php
factory(App\Models\User::class)->make();
factory(App\Models\User::class,5)->make();
factory(App\Models\User::class)->make(['name'=>'foo']);
```

<br>

## 시더 이용
make()메서드는 모델 인스턴스를 만들기만 할 뿐 실제 db에 저장이 되지 않기 때문에 seeder에서 create()메서드를 이용해서 db에 저장해줄 수 있다.

```php
class UsersTableSeeder extends Seeder
{
    public function run()
    {
        factory(App\User::class, 5)->create();
    }
}
```

<br><br>


## 모델팩토리 생성
```php
class ModelFactory extends Factory
{
    protected $model = Article::class;

    public function definition()
    {
        $date = $faker->dateTimeThisMonth;

        return [
            'name' => $this->faker->name(),
            'email' => $this->faker->unique()->safeEmail(),
            'email_verified_at' => now(),
            'password' => '$2y$10$92IXUNpkjO0rOQ5byMi.Ye4oKoEa3Ro9llC/.og/at2.uheWG/igi', // password,
            'month'=> $date,
            'remember_token' => Str::random(10),
        ];
    }

    public function unverified()
    {
        return $this->state(function (array $attributes) {
            return [
                'email_verified_at' => null,
            ];
        });
    }
}

```
definition()메서드를 이용해서 factory()메서드의 내용을 정의해주면된다.

<br>

## depth 관계 Seeder추가해보기
```php
class UsersTableSeeder extends Seeder
{
    public function run()
    {
        $users = App\Users::all();

        $users->each(function ($user) {
            $user->articles()->save(
                factory(App\Article::class)->make()
            );
        });
    }
}
```

엘로퀀트 컬렉션에서 쓸 수 있는 each메서드를 이용해서 컬렉션을 순회할 수 있고, foreach()도 가능하다.

이도 단순히 make()로는 db에 저장이 되지 않기 때문에 저장을 해주어야 하는데 create()가 아니라 save()를 사용한다. save()는 create()와 역할은 같지만 받을 수 있는 타입이 save()는 객체, create()는 배열이라는 점이 다르다.