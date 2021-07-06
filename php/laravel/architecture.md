## 라라벨 기본 디렉토리 구조
- .env : 글로벌 설정 중 민감한 값
- app 
    - Console : 사용자가 만든 콘솔 명령들
        - Kernel.php : 콘솔 명령, 크론 잡등 등록
    - Exceptions 
        - Handler.php : 전역 예외처리 정의
    - Http
        - Controllers : http 요청을 처리하는 컨트롤러
            - Auth : 라라벨에 기본 내장된 사용자 인증 컨트롤러
        - Middleware : Authenticate, Encrypt,csrfToken등과 같이 미들웨어들 정의
        - Kernel.php : http 요청 처리를 위해 기본이 되는 커널
    - Providers 
        - AppServiceProvider.php : 서비스를 컨테이너에 등록하기 위한 클래스
        - AuthServiceProvider.php : 사용자 인가와 관련된 정책 등록하기 위한 클래스
        - BroadcastServiceProvider.php : 브로드캐스트 메시지 전송 제어 클래스
        - EventServiceProvider.php : 이벤트와 이벤트 처리기 연결 클래스
        - RouteServiceProvider.php : routes 디렉토리에서 정의한 라우팅 활성화 클래스
    - Models
        - User.php : 기본 내장 User model
- bootstrap : 프레임워크 부팅 스크립트
- composer.json : npm의 package.json과 같은 프로젝트 의존성 관리 레지스트리
- composer.lock : 현재 환경에 설치한 의존성의 버전 잠금 파일
- config : db, 큐, 메일등 전역 설정을 담는 디렉토리
- database 
    - factories : 더미 모델을 만들기 위한 레시피를 담는 디렉토리
    - migrations : 해당 프로젝트의 db테이블 스키마를 담는 디렉토리
    - seeds : 생성한 테이블에 더미 데이터를 삽입하는 레시피를 담는 디렉토리
- package.json : 이 프로젝트가 의존하는 프론트엔드 리소스 레지스트리
- phpunit.xml : PhpUnit(테스트 프레임워크) 설정
- public : 웹서버 루트 디렉토리
- resources 
    - css/js
    - lang : 다국어 지원을 위한 언어별 사전을 담는 디렉토리
    - vies : 뷰 파일을 담는 디렉토리
- routes 
    - api.php : api 엔드 포인트
    - console.php : 클로저 형식으로 작성한 artisan 콘솔 명령
    - web.php : 웹 엔드 포인트
- server.php: 로컬 웹 서버 구동을 위한 스크립트
- storage : 라라벨의 파일 저장소(캐시, 로그 등)
- tests : 테스트 파일들을 담는 디렉토리
- vendor : 해당 프로젝트가 의존하는 의존성들을 담는 디렉토리

<br><br>

## 서비스 작동원리
![작동원리](/php/image/aritechture.PNG)
1. 사용자가 페이지(특정 url)요청
1. 요청이 웹서버에 도착하고 css/image등 바로 응답할 수 있는 요청은 응답하고 그렇지 않으면 index.php로 요청을 넘긴다.
1. index.php에는 라라벨의 부팅시퀀스가 담겨있어 php에게 작업을 넘긴다.
1. routes/web.php에 정의한 라우팅 테이블에서 요청에 적합한 경로를 찾는다.
    1. 적합한 경로가 없다면 오류를 응답한다.
1. 적합한 경로가 있다면 전역 미들웨어와 해당 경로에 맞는 route에 정의한 라우트 미들웨어가 http요청을 필터링한다.
    1. 미들웨어를 통과하지 못하면 예외가 발생하고 예외는 전역 예외 처리기가 처리한다.
1. 미들웨어를 통과하면 요청을 처리할 컨트롤러에게 작업을 위임하고 컨트롤러가 요청을 처리한다.
    1. 이때, 라라벨 컴포넌트, 외부 컴포넌트, 사용자 정의 컴포넌트등을 이용하여 처리
1. 처리된 결과를 `엘로퀀트(orm)`를 이용해 db와 상호작용하고 응답을 반환한다.

외부 라라벨 프로젝트를 처음 살펴볼때 `composer.json`과 `routes/web.php`를 가장 먼저 봐야 어떤 외부 컴포넌트를 사용했는지와 url와 컨트롤러간 연결을 파악할 수 있다.

<br><br>

## app 환경 설정
- APP_ENV=local : 라라벨 실행 환경
- APP_DEBUG=true : 디버그 옵션 활성화
- APP_KEY=base64:xxxx.. : 암호화 알고리즘의 키 값으로 사용되는 값
    - `php artisan key:generate`명령어로 최초에 암호화 키를 만들 수 있다.
    - 실제 운영중인 서비스에 이 값이 바뀌게 되면 쿠키와 같은 민감정보들을 복호화 할 수 없어 오류가 발생한다.
- APP_URL=htpp://localhost : 콘솔에는 $_SERVER['HTTP_HOST']값이 없어 아티즌 명령줄 인터페이스는 이 설정을 대체값으로 사용한다.

<br><br>

`php artisan serve`명령어로 라라벨 프로젝트를 실행시킬 수 있다.

