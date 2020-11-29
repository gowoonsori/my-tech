# OAuth

다른 웹사이트의 사용자 정보(아이디)를 이용하여 다른 웹의 접근 권한을 부여하는 방법으로 `공개 표준`이다.

> 기술 표준 문서가 공개 되어 있어 사용이 자유롭고 상황에 따라 다른 정의가 존재 가능하다.

`인증`이 아닌 `인가` 프로토콜

<br>

## 관련 용어

- user : 계정을 가지고 있는 개개인

- consumer : OAuth를 이용하여 service provider에 접근하는 웹앱
- service provider : OAuth접근을 지원하는 웹앱
- consumer secret : 서비스 제공자가 consumer를 구분하고 인증하기 위한 key
- request token : consumer가 user에게 접근권한을 인증받기 위한 정보로 access token으로 변환
- access token : 인증 후에 consumer가 user 정보에 접근하기 위한 key

<br>

## 과정

1. 소비자가 서비스 제공자에게 요청 토큰 요청
1. 서비스 제공자가 요청토큰 발급
1. 요청토큰을 가지고 사용자를 서비스제공자로 이동 (Redirect)(서비스 제공자가 사용자 인증 수행)
1. 서비스 제공자가 사용자를 소비자로 이동
1. 소비자가 접근 토큰 요청
1. 인증이 완료 되었다면 서비스제공자가 소비자에게 접근 토큰 제공
1. 소비자는 발급된 접근 토큰으로 사용자 정보 접근

<br>

## 개인정보에 대한 고찰

다른 사이트의 정보를 가져와 사용하면 개인정보 유출에 더 문제 되는 것이 아니냐하고 걱정할 수 있으나 OAuth를 제공하는 기업들은 대부분 거대한 기업들이고, 작은 기업에서 제공하는 회원가입,로그인보다 안전할 수 있다.

<br><br>

---

## Reference

https://ko.wikipedia.org/wiki/OAuth

https://ko.wikipedia.org/wiki/%EA%B0%9C%EB%B0%A9%ED%98%95_%ED%91%9C%EC%A4%80
