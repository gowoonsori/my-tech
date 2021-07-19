라라벨의 DB 쿼리 빌더는 DB쿼리를 만들고 운영하는데 많은 기능들을 제공하며, PDO 파라미터 바인딩을 사용하여 SQL 인젝션을 방지한다.

<br>

## 쿼리 조회

### get()

```php
$users = DB::table('users')->get();
```

get() 메소드는 앞에 체이닝한 메소드들의 결과물을 가져오는 메소드로 `Collection`을 반환한다.

Collection을 반환하기 때문에 내부에 `items[]`를 가지고 있어 `empty()`로 비어있는지 확인이 안된다. 이는 반환된 컬렉션의 `all()`을 통해 내부 items배열을 접근하여 확인이 가능하다.

```php
foreach ($users as $user) {
    echo $user->name;
}
```

foreach를 통해 각각의 컬럼에 접근할 수도 있다.

### first() / value() / find()

```php
$user = DB::table('users')->where('name', 'John')->first();

$email = DB::table('users')->where('name', 'John')->value('email');
```

first()메서드는 앞의 조건을 만족하는 하나의 행을 반환하고 value()는 앞의 조건을 만족하는 행중 value의 컬럼만 조회하는 메서드이다.

first()는 하나의 모델(객체)를 반환하고 value()는 단일 값을 반환한다.

### find()

```php
$user = DB::table('users')->find(3);
```

id를 이용해서 검색하고자 한다면 find()를 이용할 수 있다. find()도 모델(객체)를 반환한다.

### pluck()

```php
$titles = DB::table('roles')->pluck('title');
```

테이블에서 한개의 컬럼값을 가지고 있는 모든 테이블의 컬렉션을 조회하는 메서드이다.

<br>

## 결과 분할

```php
DB::table('users')->where('active', false)
    ->chunkById(100, function ($users) {
        foreach ($users as $user) {
            DB::table('users')
                ->where('id', $user->id)
                ->update(['active' => true]);
        }
    });
```

많은 행의 작업을 수행하려고 한다면 chunk()를 이용해 클로저로 처리할 수 있으며 clousre의 반환값을 `false`를 주면 중간에 중단 할 수 있다.

결과를 청킹(벌크)하는데 데이터의 무결성을 위해 update시에는 chunkById()를 이용하는 것이 좋다.

<br>

## 함수

### count / max / avg / min / sum

```php
$users = DB::table('users')->count();

$price = DB::table('orders')->max('price');

$price = DB::table('orders')
                ->where('finalized', 1)
                ->avg('price');
```

### exists / doesntExist

```php
return DB::table('orders')->where('finalized', 1)->exists();

return DB::table('orders')->where('finalized', 1)->doesntExist();
```

레코드가 존재하는지 확인해 볼 수도 있다.

<br>

## select

```php
$users = DB::table('users')->select('name', 'email as user_email')->get();

//distinct
$users = DB::table('users')->distinct()->get();

//addSelect
$query = DB::table('users')->select('name');
$users = $query->addSelect('age')->get();
```

내가 원하는 컬럼만 가져오고 싶을때는 select로 지정해줄 수 있다.

<br>

## raw query

```php
DB::raw(select * from users)->get();

//selectRaw
$orders = DB::table('orders')
                ->selectRaw('price * ? as price_with_tax', [1.0825])
                ->get();

//whereRoaw
$orders = DB::table('orders')
                ->whereRaw('price > IF(state = "TX", ?, 100)', [200])
                ->get();
//havnigRaw
$orders = DB::table('orders')
                ->select('department', DB::raw('SUM(price) as total_sales'))
                ->groupBy('department')
                ->havingRaw('SUM(price) > ?', [2500])
                ->get();

```

전체나 일부분을 직접 SQL문을 이용해 작성할 수도 있다.

<br>

## Join

### inner join

```php
$users = DB::table('users')
            ->join('contacts', 'users.id', '=', 'contacts.user_id')
            ->join('orders', 'users.id', '=', 'orders.user_id')
            ->select('users.*', 'contacts.phone', 'orders.price')
            ->get();
```

join()메서드를 이용하면 기본적으로 inner join이 수행되고 이때 메서드의 첫번째 인자는 `join을 수행할 테이블 이름`이고 그 이후는 `join 제약조건` 이다.

<br>

### left / outer join

```php
$users = DB::table('users')
            ->leftJoin('posts', 'users.id', '=', 'posts.user_id')
            ->get();

$users = DB::table('users')
            ->rightJoin('posts', 'users.id', '=', 'posts.user_id')
            ->get();
```

### 여러 테이블 join

```php
DB::table('users')
        ->join('contacts', function ($join) {
            $join->on('users.id', '=', 'contacts.user_id')->orOn(...);
        })
        ->get();
```

join의 두번째 인자로 클로저를 이용해서 여러테이블을 join할 수도 있다.

<br>

### 서브 쿼리 조인

```php
$latestPosts = DB::table('posts')
                   ->select('user_id', DB::raw('MAX(created_at) as last_post_created_at'))
                   ->where('is_published', true)
                   ->groupBy('user_id');

$users = DB::table('users')
        ->joinSub($latestPosts, 'latest_posts', function ($join) {
            $join->on('users.id', '=', 'latest_posts.user_id');
        })->get();
```

`joinSub`, `leftJoinSub`, `rightJoinSub`메서드를 이용해 서브쿼리에 조인을 이용할 수 있다.

<br>

### Union

```php
$first = DB::table('users')
            ->whereNull('first_name');

$users = DB::table('users')
            ->whereNull('last_name')
            ->union($first)
            ->get();
```

미리 쿼리를 생성해두었다면 해당 쿼리를 union()메서드를 이용해서 합칠 수 있다.
