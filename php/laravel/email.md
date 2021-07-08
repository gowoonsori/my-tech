알림기능 중 가장 전통적인 방법인 메일은 `smtp`,`mail`,`mailgun`,`log`등 여러 드라이버 중에서 선택해서 사용할 수 있다.

`config/mail.php`에서 `from` 부분의 value를 수정하여 보내는 사람에 관한 전역설정을 할 수 있다.

<br>

## gmail
gmail은 smtp프로토콜을 이용하고 지메일 드라이버를 설정해주어야 하는데 `.env`파일을 열어 다음과 같이 작성해주면 된다.
```
MAIL_MAILER=smtp
MAIL_HOST=smtp.gmail.com
MAIL_PORT=587
MAIL_USERNAME={username}@gmail.com
MAIL_PASSWORD={password}
MAIL_ENCRYPTION=tls
```
그리고 지메일에 로그인하여 `내계정=>로그인 및 보안페이지=>보안수준 낮은앱 허용`을 사용함으로 바꾸어 주어야 한다.

<br>

### 메일 보내는 로직 예시
```php
Route::get('mail', function(){
    $article = App\Article::with('user')->find(1);

    return Mail::send(
        'emails.articles.created',
        compact('article'),
        function($message) use ($article){
            $message->to('dest@domain');
            $message->subject('새 글이 등록되었습니다.' . $article->title);
        }
    );
});
```

Mail 파사드의 send()메서드로 메일을 보내며 이 메서드의 첫번째 인자는 메일 본문에 사용할 `뷰`이다. 두번째 인자는 뷰에 전달할 `데이터`이고 세번째 인자는 메일 내용을 구성하는 `클로저`이다. 클로저에서 $message를 인자로 받아 subject()는 메일 제목을, to()메서드로 수신자를 정의 한다

`use()` 키워드는 클로저 밖에 있는 데이터를 클로저 컨텍스트에 바인딩하는 문법으로 이 키워드가 없으면 `$article` 변수를 클로저 안에서 쓸 수 없다.

<br><br>

## 메일건
smtp는 비교적 느린 프로토콜로 메일 발송을 할때 느릴 수가 있는데 메일건을 이용하면 http로 메일 발송을 요청하고 그 이후에 smtp로 보내주는 방식이기 때문에 사용자의 화면 응답시간을 줄일 수 있다. 이를 위해서는 우리 서버가 메일건 서버와 http로 통신할 수 있어야 한다. `compser require "guzzlehttp/guzzle:~5.3|6.0"`으로 http 클라이언트 컴포넌트를 설치 해주면 된다.

메일건을 회원가입하고 .env파일을 아래와 같이 수정하자. random number는 메일건에 로그인하면 대시보드에 표시되어있다.
```
MAIL_DRIVER=mailgun
MAILGUN_DOMAIN={sandbox_random_number}.mailgun.org
MAILGUN_SECRET={key-RANDOM_NUMBER}
```

<br><br>

## 추가 메서드
- $message->to(array $address) : 받는 사람이 여러명일때는 배열을 이용
- $message->from(string $addr, string $name = null) : 전역으로 설정한 보내는 사람의 이메일 주소와 이름을 오버라이드 할 수 있다.
- $message->cc(string $addr, string $name=null) : 참조. 여러명일 때는 체인 이용
- $message->bcc(string $addr, string $name=null) : 숨은 참조. 여러명일 때는 체인 이용
- $massage->attach(string $file, array $options = []) : 파일 첨부. ['as' => '파일 별칭', 'mime' => 'application/zip']과 같이 두번째 인자에 옵션을 줄 수 있다.
    - $message->attach(storage_path('elephant.png')) : `storage_path()`메서드는 storage 디렉토리 아래에 있는 파일의 절대 경로를 반환하는 도우미 함수이다.
    - {{ $message->embed(storage_path('elephant.png')) }} : view에서 이미지를 본문에 추가할 때는 `embed(string $file)`메서드를 이용하면 된다.