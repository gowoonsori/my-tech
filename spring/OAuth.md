# Spring OAuth2.0

OAuth의 기본 설명은 [여기](/web/OAuth.md)를 참고하자

Spring에서 OAuth를 적용

## Password Grant Type?

계정정보를 가지고있는 앱에서 사용할 수 있는 방식으로 비밀번호,아이디,grant type을 request의 파라미터로, client_id와 client_Secret은 header에 넣어 줄 수 있다.

패스워드를 직접 요구하기 때문에 서드파티한테 넘겨주는 것이 아닌 계정정보를 가지고있는 그 앱에서만 사용가능한 방식.
<br>(서비스 오너가 만든 클라이언트에서 사용하는 Grant Type)

1홉만에 Access Token을 받아올 수 있다.

https://developer.okta.com/blog/2018/06/29/what-is-the-oauth2-password-grant

## AuthorizationServer 설정 (인증 서버)

@EnableAuthorizationServer 과 extends AuthorizationServerConfigurerAdapter을 이용해 configure 세개 매서드 override

- configure(AuthorizationServerSecurityConfigurer security)

  - passwordEncode 설정

- configure(ClientDetailsServiceConfigurer clients)

  - 토큰 저장방식
  - 클라이언트 설정 (clinet id)
  - grantType
  - scopes
  - secret
  - acccessToken시간
  - refreshToken시간

- configure(AuthorizationServerEndpointsConfigurer

  - tokenSore
  - authenticationManager
  - userDatailSErvice

- httpBasic메서드를 사용하기 위해 dependency 추가

## ResourceServer 설정

@EnableResourceServer 과 extends ResourceServerConfigurerAdapter을 이용해 configure 두개 매서드 override

- configure(ResourceServerSecurityConfigurer resources)

  - 리소스 ID

- configure(HttpSecurity http)

  - 접근 권한 (annoymous, authenticated)
  - 메서드와 url에 대한 접근 권한

    ex.

    - GET /api/\*\* : permit all
    - POST /api/\*\* : authenticated
    - PUT /api/\*\* : authenticated

  - 에러 처리
    - accessDeniedHandler(OAuth2AccessDeniedHandler())
