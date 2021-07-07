```php
Route::get('/','WelcomeController@index');
```
web.php에서 라우팅을 할때 콜백함수로 구문을 처리했었는데, 컨트롤러로 위임하기 위해서는  `컨트롤러 이름@메서드명`을 두번째 인자로 주면 된다.

<br>

## 컨트롤러 만들기
```sh
$ php artisan make:controller WelcomeController
```
artisan으로 컨트롤러를 만들면 App\Http\Controllers 밑에 컨트롤러사 생성이 된다.

<br>

```php
<?php
namespace App\Http\Controllers;

class WelcomeController extends Controller
{
    public function index(){
        return view('welcome');
    }
}
```

<br>

### Restful 리소스 컨트롤러
`php artisan make:controller ArticlesController --resource` 명령어로 컨트롤러를 생성하면 index(), create(), store(),show(), edit(), update(), destroy() 메서드들을 포함하고 있는 컨트롤러가 생성이 된다.

- index() : 조회
- store() : 새 모델 생성
- create() : 새 모델 프로퍼티 값을 입력받기 위한 폼
- show() : 기본키 값을 가진 모델 조회
- update() : 기본키값을 가진 모델 값 수정
- edit() : 기본키 값을 가진 모델 수정값을 입력받기 위한 폼
- delete() : 기본키 값을 가진 모델 값 삭제 

post방식의 http요청을 보내면 라라벨은 기본적으로 미들웨어에서 csrf공격을 막고자 토큰(_token)이 존재하는지 검사하고 없으면 예외를 반환하는데 VerifyCsrfToken.php에서 특정 uri를 제외시킬 수 있다.

<br>

```php
Route::resource('articles','AritclesController');
```
리소스 컨트롤러는 get()이 아니라 resource()를 이용하고 매개변수로 클래스명만 적어주면 된다.

<br>

### 번외) csrf 보호 동작 방식
1. 컨트롤러의 create()와 같은 메서드에서 숨은 필드로 _token값을 담아 새로운 폼을 응답한다.
1. 브라우저가 _token 필드를 http요청 본문에 담아 post articles요청을 한다.
1. 라우터가 컨트롤러에게 작업을 할당하기 전에 미들웨어 그룹을 실행한다.
1. csrf 토큰 미들웨어가 폼을 응답했던 세션에서 만든 _token과 지금 요청으로 받은 _token을 비교한다.
1. 통과하면 컨트롤러의 메서드에게 작업을 위임하고 아니면 예외를 던진다.

<br>

### 라우트 확인
```sh
$ php artisan route:list
```
위 명령어로 현재 라우트를 확인할 수 있는데 항목은 다음과 같다.
- Domain : Url경로 뿐만 아니라 도메인에 따라 라우팅도 분리가능
- Method : http 요청 메서드
- URI : 경로
- name : 라우트 이름(별칭)
- Action : 라우팅을 처리할 컨트롤러와 메서드
- Middleware : 라이퉁에 적용할 전역 미들웨어, http 미들웨어