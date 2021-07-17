실제 요청에 해당하는 url에 맞는 라우터를 찾는 부분

`Illuminate\Support\Facades\Route`를 traits하여 Route의 메서드들로 요청을 라우팅할 수 있다.

get,post등과 같은 메서드들을 이용할 수 있고 첫번째 인자는 요청경로이며, 두번째 인자는 요청이 왔을때 해당 함수를 동작한다는 의미이다. 이때 두번째 인자의 함수를 `클로저`라고 한다.

<br>

```php
Route::get('/', function() {
    return view('welcome');
});
```

`view()`를 통해 resources/views/ 에 있는 파일을 return할 수 있다.

<br>

```php
Route::get('/', function() {
    return '{id: "gowoo"}';
});
```

첫번째 예시처럼 html view나 위와같이 문자열을 반환할 수 있는데 문자열을 바로 반환하면 `controller`가 할 일을 클로저가 대신해서 한 것으로 controller가 없이도 개발이 가능하다는 것을 보여준다.
물론, 좋은 방법은 아니다.

<br><br>

## 파라미터

```php
Route::get('/{foo}', function($foo) {
    return $foo;
});

Route::get('/{boo?}', function($boo = 'bar') {
    return $boo;
});
```

url 파라미터를 `{}`로 감싸면 파라미터 값을 변수로 참조가 가능하고, 파라미터가 없을때 기본값을 주고 싶다면 `?`를 붙여 사용할 수 있다.

<br><br>

## 파라미터 패턴

```php
Route::pattern('foo','[0-9a-zA-z]{3}')

Route::get('/{foo}', function($foo) {
    return $foo;
});
```

Route의 pattern메서드를 이용해서 파라미터에 대해 유효성 검사를 할 수 있고 Pattern에 맞지 않는다면 `NotFound` 예외를 발생시킨다.

<br>

```php
Route::get('/{foo}', function($foo) {
    return $foo;
})->where('foo','[0-9a-zA-z]{3}');
```

pattern()대신 get()에 where()을 메서드 체이닝을 이용해서 사용할 수도 있다.

<br><br>

## 별칭

```php
Route::get('/{foo}',
    'as' => 'foo',
    function($foo) {
        return $foo;
    }
]);

Route::get('/home', function() {
    return redirect(route('home'));
});
```

컨트롤러나 뷰에서 다른 route로 이동하는 링크를 만들때 각 라우트마다 이름을 부여하면 쉽게 이동할 수 있다.
Route::get() 메서드의 두번째 인자로 배열을 전달하면 되는데, 위와 같이 배열에 `as`를 key로 하고 별칭을 value로 하는 값과 `클로저`를 담아 전달하면 된다.

<br>

## Group

```php
//middleware
Route::middleware(['first', 'second'])->group(function () {
    Route::get('/', function () {
        // Uses first & second middleware...
    });

    Route::get('user/profile', function () {
        // Uses first & second middleware...
    });
});

//sub domain
Route::domain('{account}.myapp.com')->group(function () {
    Route::get('user/{id}', function ($account, $id) {
        //...
    });
});

//prefix
Route::prefix('admin')->group(function () {
    Route::get('users', function () {
        // Matches The "/admin/users" URL
    });
});
```

group()메서드는 공통된 url에 미들웨어를 붙이거나 서브도메인/하위 prefix를 묶을때 이용할 수 있다.

<br>

## 오버라이드

같은 경로의 라우터를 두번 정의하면 가장 아래쪽에 정의한 라우트가 실행된다.
