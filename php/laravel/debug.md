## 발생할 수 있는 버그 종류
1. 문법 오류 : php 인터프리터가 문법 오류를 낸다.
1. 로직 오류 : 무한 루프나 잘못된 조건분기등의 오류로 잘못된 데이터 출력등의 문제 발생
1. 리소스 오류 : null 포인터나 초기화하지 않은 변수ㅡ 뎅이터타입등의 오류로 `Trying to get property of non-object` 또는 `Call to undefined method`메서지로 표시된다. 이를 방지하기 위해 메서드의 매개변수 앞에 `타입 힌트`를 사용하는 편이 좋은 습관이고 php7부터는 타입을 지정이 가능하다.
1. 계산 버그 : 0으로 값을 나누거나 반올림 자릿수를 잘못 입력해 이상한 데이터를 출력하는 문제 발생 => 돈과 관련된 서비스에서는 치명적일 수 있다.
1. 동시성 오류 : php는 단일 스레드 언어로 다중 스레드 문제는 많이 발생하지 않지만 트래픽이 많은 db에서는 발생할 수 있고 이때 트랜잭션 기능을 이용할 수있다.
    - [트랜잭션 문서](https://laravel.kr/docs/database#database-transactions)
1. 잘못된 사용 : api를 잘못 사용할 때 발생 할 수 있는 오류
1. 팀워크 오류 : 여러명이 같은 코드를 짜고 고치는 과정에서 충돌, side effect등이 발생 할 수 있다.
1. 성능 오류 
1. 보안 오류 : 서비스의 데이터가 오염, 유실, 탈취되는 문제
1. 설계 오류 : 잘못된 설계 명세서에 의해서 엉뚱한 결과물이 나올 수도 있다.

<br><br>

## 디버깅 방법
### 1. dd() 함수
```php
//controller
public function show($id){
    $article = \App\Article::findeOrFail($id);
    dd($article);
    return $article->toArray();
}
```

dd()메서드는 디버거로 중단점을 찍는 것과 똑같은 일을 수행하여 인자로 받은 값을 덤프하고 실행을 멈춘다. 이는 뷰를 디버깅할때도 사용이 가능하다. 라라벨은 블레이드 엔진으로 뷰를 컴파일한 후 storage/framework/view 디렉토리 아래에 캐시해 놓는데, 이 캐시된 파일을 열어 뷰 디버깅을 할 수도 있다 하지만 엔진이 컴파일한 php파일이라 보기 불편할 수 있은데 이때 `render()`메서드를 이용하면 된다.

controller에서 `dd(view('article.index',compact('articles'))->render());`와 같이 작성하면 render()메서드가 뷰 인스턴스에 저장된 html코드를 출력해준다.

<br>

### 2. 쿼리 디버깅
```php
php artisan tinker
>>> $queryLoyalUsers = App\User::wher(
    'last_login', '>', Carbon\Carbon::now()->subMonth()
)->toSql();
```
`DB::listen(function ($query){...})`구문을 이용하거나 컬렉션을 얻는 쿼리일 때는 위와 같이 `toSql()`메서드를 이용할 수 있다. 모델 쿼리에서 get()메서드를 toSql()로 바꾸기만 하면 된다.
