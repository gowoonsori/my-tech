# HTTP통신 기반 인증

http 프로토콜은 한번 통신후 연락을 끊고 상태 저장을 하지 않는 `stateless`한 프로토콜

상태를 저장하지 않는 게 원칙인데 이렇게 웹 서비스를 운영하면, 사용자는 매번 로그인을 해야하는 등 사용자 경험이 매우 떨어질 수 있어 사용자의 정보를 저장하고 구분하여 데이터 처리를 위해 `사용자 인증`은 필요 요소이다.

<br>

## 필수 개념

### 인증 (Authentication)

클라이언트의 사용자를 누구인지 확인(인증)하는 과정

서비스를 사용하는 사용자를 추적,관리하여 사용자 경험을 높이고, 사용자의 정보를 보호하기 위함

<br>

### 인가 (Authorization)

사용자가 하려는 행동이 허가된 작업인지 확인하는 과정 ( 특정 자원에 대해 접근 권한이 있는 지 확인하고 허락하는 것)

<br>
<br>

## 인증 방식

### http 헤더에 정보를 추가하는 방식

매번 계정 정보를 요청 헤더에 넣는 방식

가장 보안이 낮은 방식으로, 패킷을 가로채기만 하면 사용자의 정보를 쉽게 알 수 있다.

<br>

### 쿠키와 세션 (서버 기반 인증)

- 쿠키 :

  클라이언트에 저장되는 `텍스트`형식의 데이터로 사용자 정보를 저장하고 유효기간을 명시하여, 브라우저를 끄더라도 인증이 유지가능하다.

- 세션 :

  사용자 정보를 서버측에서 관리하며 브라우저를 종료하거나 특정 기간까지 인증상태 유지 (별도의 세션 저장소에 세션 정보를 저장하고 관리)

쿠키는 세션 저장소에 담긴 유저 정보를 얻기 위한 열쇠로 사용 ( 쿠키를 탈취당해도 쿠키 자체는 유의미한 값을 가지고 있지 않다. (세션 ID))

사용자마다 고유의 ID값을 발급 받기 때문에 서버의 자원에 접근하기 용이하다.

<br>

#### 문제점

- 세션 하이재킹 : 탈취한 쿠키를 이용하여 요청하여 정보를 빼내는 방법.
  -> https를 이용하여 패킷 데이터자체를 암호화하거나 세션에 유효기간을 설정
- 세션을 서버에 저장하기 때문에 서버의 부하가 올라간다.

- CORS : 쿠키는 단일/서브 도메인에서만 작동하도록 설계되어 있어 여러 도메인에서 관리하는 것이 번거롭다.

<br>

### 토큰 기반 인증 방식

인증받은 사용자들에게 토큰을 발급하고, 서버에 요청을 할 때 헤더에 토큰을 함께 보내도록 하여 유효성 검사를 하는 방식

<br>

#### 특징

- stateless : 토큰은 클라이언트 측에서 저장되기 대문에 서버는 상태를 저장하지 않는다.

- 확장성

  - 시스템 확장성 (Scalability) : 서버를 분산처리 하게 될 경우 세션방식은 서버에 따로 저장소가 존재하기 때문에, 처음 로그인한 서버에만 요청하도록 하거나 해야하는데 토큰 방식은 복호화만 하면 되기때문에 시스템 확장에 자유롭다.

  - 서비스 분야 확장 (Extensibility) : 토큰에 선택적인 권한만 부여하여 발급 할 수 있어 OAuth의 경우 소셜 계정을 이용해 다른 웹 서비스에서 로그인이 가능하다.

- CORS 문제 해결 : 여러 장치를 호환시키고 많은 서비스를 제공하게 될 때, 어떤 도메인에서도 토큰의 유효성 검사가 가능하여, 서버측에서는 API만 다루도록 설계가 가능하다.

일반적으로 요청 헤더의 `Authorization 필드`에 담아져서 전송된다.

> Authorization 구조 : <type> <credentials>

#### 인증 타입

- Basic : 사용자 아이디와 암호를 Base64로 인코딩한 값을 토큰으로 사용
- Bearer : JWT / OAuth의 토큰
- Digest : 서버에서 난수 문자열(nonce)을 이용하고, 클라이언트는 사용자 정보와 `nonce`를 포함하는 해시값을 사용해 응답

  > nonce : 한번만 사용할 수 있는 임의의 숫자(암호)

- HOBA : 전자 서명 기반 인증
- Mutual : 암호를 이용해 클라이언트와 서버 상호 인증
- AWS4-HMAC-SHA256 : AWS 전자 서명 기반 인증

<br>

### JWT

JWT는 Json Web Token의 약자로 인증에 필요한 정보들을 암호화 시킨 토큰

쿠키/세션과 유사하게 Access Token을 http헤더에 실어 서버로 보낸다.

<br>

#### 구조

**XXX.YYY.ZZZ**
|||
|:---:|:---:|
|XXX|header(json)|
|YYY|payload(json)|
|ZZZ| signature|

- header : 암호화할 방식(알고리즘), 타입

- payload : 서버에서 보낼 데이터 ( 일반적으로 사용자 고유 id, 유효기간 등)
- veryfi signature : Base64방식으로 인코딩한 header, payload , SECRET KEY를 더해 서명

header와 payload는 그저 인코딩한 값이므로 `해커`가 임의의 토큰을 가지고 접근을 시도해도 `SECRET KEY`를 모른다면 veryfi signature를 제대로 복화 할 수 없어 제대로 된 데이터 응답을 하지 못한다 (차단)

세션/쿠키는 세션저장소에 저장하나 토큰방식은 별도의 저장소가 없이 헤더의 토큰을 암호화/복호화 하는 과정을 거친다. (쿠키는 로컬 스토리지)

#### 저장 장소

- 웹 스토리지 : XSS 공격에 위험이 있다.

  > 웹 스토리지는 클라이언트에 데이터를 저장할 수 있도록 지원하는 HTML5 기능
  >
  > 로컬 스토리지와 세션스토리지로 나누어지고 로컬 스토리지는 창이 꺼져도 데이터가 유지 되고 도메인이 다른 경우 로컬 스토리지에 접근이 불가능하다.
  >
  > 세션스토리지는 창이 꺼지면 데이터가 지워지고 세션마다 개별적 저장되며 같은 도메인이더라도 세션이 다르면 데이터 접근 불가능

- 쿠키 : 쿠키 역시 브라우저가 토큰을 기억하다가 서버에 전달해주는 측면에서 웹 스토리지와 비슷

  > 웹 스토리지는 5MB, 쿠키는 4KB로 훨씬 많은 데이터 저장 가능

- 서버 : refresh token같이 중요한 토큰은 서버 db에 저장하기도 한다. 하지만 토큰이라는 것이 휘발성 데이터이므로 주의

<br>

#### 문제점

1. JWT저장을 위해 웹스토리지를 사용할때 웹 스토리지는 js로 제어가 가능해 `XSS 공격`에 위험이 있다. (JWT가 쿠키에 없으므로 CSRF에 비교적 안전)

-> 스크립트등으로 해킹할 수 있는 모든 입출력 값을 검증하고 무효화 시켜야 한다.

1. 쿠키에 저장하는 방식도 탈취가 가능하지만 옵션설정으로 공격을 어느정도 무력화 시킬 수 있다. (`XSS (Cross Site Scripting)`공격에 안전한 대신 `CSRF`에 비교적 취약하다)

-> 쿠키 발급시 `httpOnly`(js로 접근이 불가능), `Secure`(https로만 쿠키 전송)등을 넣어주는 게 좋다.

로그인 했을 때 위치나 기기 고유값, ip를 저장해두고 너무 다른 위치에서 접근시도시 차단을 하는 방법을 이용할 수도 있다. (`CSRF`공격에 대비해 `Refer`, `Origin`이용)

1. 세션/쿠키에서 쿠키가 탈취되었다면 세션을 지우기만 하면 되지만, 토큰 방식은 한 번 발급 되면 유효기간이 완료될 때까지 사용이 가능하기 때문에 보안에 취약할 수 있다.

-> Access Token과 Refresh Token 두개를 두어 Acess Token의 유효기간을 짧게 설정하고 Refresh Token을 통해 새롭게 Acess Token을 재발급 하는 방식을 이용
<br>(결국 Refresh Token을 서버에 저장할 경우 서버의 부담증가와 refresh token도 만료기간이 있는 토큰이기에 휘발성 데이터를 db에 저장시키는 것은 안좋을 수도 있다.)

결국 개발자의 선택!!

<br>
<br>

---

## Reference

https://velog.io/@cada/%ED%86%A0%EA%B7%BC-%EA%B8%B0%EB%B0%98-%EC%9D%B8%EC%A6%9D%EC%97%90%EC%84%9C-bearer%EB%8A%94-%EB%AC%B4%EC%97%87%EC%9D%BC%EA%B9%8C
