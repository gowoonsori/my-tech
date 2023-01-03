# Authorization Filter
## 권한 계층

### 웹 계층

URL요청에 따른 메뉴/화면 단위의 레벨 보안

`/user` ->request -> `ROLE_USER`

### 서비스 계층

메서드와 같은 기능단위의 레벨 보안

`user()` ->invoke-> `ROLE_USER`

### 도메인 계층

객체 단위의 레벨 보안

`user` ->write-> `ROLE_USER`

## 선언적 방식

### URL

```java
http.antMathcers("/user/**").hasRole("USER")
```

`WebSecurityConfigurerAdapter`를 상속받은 클래스에서 configure를 통해서 다음과 같이 선언해 줄 수 있다.

구체적인 범위를 가진 url이 앞에 와야한다.

```java
http
    .antMathcer("/shop/**")
    .authorizeRequest()
        .antMathcers("/shop/login", "/shop/users/**").permitAll()
        .antMathcers("/shop/mypage").hasRole("USER")
        .antMathcers("/shop/admin/pay").access("hasRole('ADMIN') or hasRole('SYS')")
        .anyRequest().authenticated();
```

`/shop`하위 도메인에 대해 그 밑의 인증세팅정보를 사용하겠다는 뜻이다. 상위의 antMathcer이 없다면 모든 경로에 대해 authorizeRequest()를 수행

|                         메서드                         |                               기능                               |
| :----------------------------------------------------: | :--------------------------------------------------------------: |
|                    authenticated()                     |                     인증된 사용자 접근 허용                      |
|                  fullyAuthenticated()                  |           remberMe인증 제외한 인증된 사용자 접근 허용            |
|                      permitAll()                       |                         무조건 접근 허용                         |
|                       denyAll()                        |                        무조건 접근 허용 x                        |
|                      anonymous()                       | 익명 사용자 접근 허용 (인증된 사용자는 익명사용자에 접근 불가능) |
|                      rememberMe()                      |             remberMe를 통해 인증된 사용자 접근 허용              |
| access(String) spEL 표현식의 평가가 true이면 접근 허용 |
|                    hasRole(String)                     |           특정 역할이 있다면 허용 (ROLE\_ prefix생략)            |
|                  hasAuthority(String)                  |          주어진 권한이 있다면 허용 (ROLE\_ prefix 포함)          |
|                 hasAnyRole(String ...)                 |                  주어진 권한이 있다면 접근 허용                  |
|              hasAnyAuthority(String ...)               |             주어진 권한중 하나라도 있다면 접근 허용              |
|                  hasIpAddress(String)                  |                       주어진 IP 접근 허용                        |

<br><br>

### Mehtod

```java
@PreAuthorize("hasRole('USER')")
@Secured("USER")
```

Controller에서 위의 어노테이션을 이용하여 각 메서드별로 역할을 부여해줄 수 있다.

```java
@EnableWebSecurity
@EnableGlobalMethodSecurity(securedEnabled = true, prePostEnabled = true)
public class CustomConfig extends WebSecurityConfigureAdapter{}
```

설정클래스에 `@EnableGlobalMethodSecurity`를 이용해 선언해주어야 한다.

<br>

## 동적 방식

DB 연동 프로그래밍

### URL

### Method

<br><br>

## ExceptionTranslationFilter

FilterSecifityIntercepter가 Filter의 맨 마지막에 위치하고 Exception을 Throw한다. ExceptionTranslationFilter는 이 필터 앞에 위치해서 요청을 try~catch로 Intercepter를 감싸 호출하고 있다.

### AuthenticationException

인증 예외

1. AuthenticationEntryPoint

   인터페이스이며 이를 구현한 구현체를 Security가 제공하고 이는 로그인 페이지로 이동하거나, 오류코드 전달등 수행 (Custom하고자 한다면 이를 구현한 구현체를 만들면 된다.)

2. 인증 예외가 발생하기전의 요청 정보를 저장
   - RequestCache : 사용자의 이전 요청 정보를 세션에 저장하고 이를 꺼내 오는 캐시 매커니즘
     - SavedRequest : 사용자가 요청했던 request 파라미터 값들, 그 당시의 헤더값들 등이 저장

<br><br>

### AccessDeniedException

인가 예외

1. AccessDeniedHandler

Anonymous이거나 RememberMe 인증사용자의 경우 AccessDeniedException이 발생하지만 AccessDeniedHandler로 보내지 않고 AuthenticationException으로 보낸다.

```java
http.exceptionHandling()  //예외처리 기능 설정
        .authenticationEntryPoint(customAuthenticationEntryPoint)  //인증 실패시 처리할 클래스
        .accessDenidedHandler(customAccessDenidedHandler())               //인가 실패시 처리할 클래스
```

<br><br>

### FilterSecurityInterceptor

마지막에 위치한 필터로 인증된 사용자에 대해 특정 요청의 승인/거부 여부를 최종적으로 결정

인증객체 없이 접근을 시도할 경우 `AuthetnicationException`발생을 시키고 접근권한이 없다면 `AccessDeniedException`을 발생시킨다.

권한 처리를 `AccessDecisionManager`에게 맡긴다.

#### 과정

1. 요청이 마지막 필터인 FilterSecurityInterceptor에게 도달
1. 인증 여부 체크 후 인증된 객체라면
1. SecurityMetaDataSource에서 요청 도메인/자원에 필요한 권한/역할 정보 조회
1. 도메인에 필요한 권한이 존재한다면 AccessDecisionManager에게 전달
1. AccessDecisionManager에서 AccessDecisionVoter에게 권한 심의 요청
1. AccessDecisionVoter가 최종 승인 여부 반환
1. 자원 접근 허용

<br><br>

![](/spring/image/autho.PNG)

### AccessDecisionManager

접근, 인가 결정을 내리는 인터페이스로 인증된 사용자의 리소스 접근 여부 판단하고, 접근 승인하는데 정책을 결정

- AffirmativeBased: 접근을 승인하는 voter가 1개 이상
- ConsesusBased: 과반수
- UnanimouseBased: 모든 voter가 승인

  > Voter : 말그래도 투표자로 의사결정을 내리는 객체들. Manager는 여러개의 Voter를 가질 수 있다.

`decide(authentication,object,configAttributes)`를 이용해 Voter에게 권한 판단을 심사

### AccessDecisionVoter

해당 사용자의 인증level이 특정 object 접근level에 만족하는지 확인

#### 권한 판단 자료

- Authentication : 인증 정보(user)
- FilterInvocation : 요청 정보(antMathcer("/user"))
- ConfigAttributes : 권한 정보 (hasRole("USER"))

#### 결정 방식

- ACCESS_GRANTED : 승인
- ACCESS_DENIED : 거절
- ACCESS_ABSTAIN : 보류

#### RoleVoter

AccessDecisionVoter 구현체중 하나로 리소스에 접근하기 위해 권한을 사용자가 지니고있는지 확인

#### WebExpressionVoter

웹 시큐리티에서 사용하는 기본 구현체중 하나로, SpEL표현식에 따른 접근 처리(ROLE\_\* 매치되는지 확인)

<br><br>
