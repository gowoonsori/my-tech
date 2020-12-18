# Spring Security

스프링에서 제공하는 애플리케이션 보안(인증,인가 ,권한)등을 담당하고 기능을 제공해주는 하위 프레임워크

## 종류

Spring framework 5.x이후 Webflux가 추가됨에 따라 `Servlet App` ,`Reactive App(Webflux)` 두가지로 나눌 수 있다.

## 특징

- 웹 시큐리티 (Filter 흐름에 따라 처리 ) : url요청이 있을때 흐름에 따라 인증,권한 처리

- 메서드 시큐리티 : url요청에 상관없이 메소드가 호출되었을때 인증,권한을 처리
- 요청시 가장 먼저 url요청을 받는다. ( Dispatcher Servlet으로 가기전에 먼저 적용 )

- Credential 기반 인증 : Principal(접근 주체)를 아이디로, Credential(비밀번호)를 임의로 생성된 비밀번호로 사용

## 큰 구조

![Structure](/spring/image/security-structure.PNG)

인증과 인과 모두 Interceptor를 통해 수행되며 메서드,filter방식으로 동작이 가능하고, 인증에 관한 정보들을 담아 두는곳은 `SecurityContext`에 저장이 되며 `SecurityContextHolder`를 통해 접근이 가능하다.
<br>_(기본설정은 ThreadLocal에 저장 되며 스레드마다 할당되는 데이터 공간이다)_

Servlet App방식에서 Security는 필터방식으로 동작한다.

필터 : 클라이언트 요청이 서블릿으로 가기전에 먼저 처리할 수 있도록 WAS에서 지원해주는 기능

    기본적인 필터는 자동으로 구성되고 커스텀 필터를 추가하고 싶다면 Bean을 추가하거나 web.xml에 추가해주자

    필터 종류

SecurityContextHolder : 인증 정보에 접근하기 위한 인터페이스

- SecurityContext : 인증 정보를 저장하는 저장소로 별다른 설정 없을시 `ThreadLocal`에 저장

  - Authentication : 실제 사용자 인증 정보를 의미하는 인터페이스
    - Principal
    - Credentials
    - Authorities

  생성

  ```java
  SecurityContext context = SecurityContextHolder.createEmptyContext();
  Authentication authentication = new TestingAuthenticationToken("username", "password", "ROLE_USER");
  context.setAuthentication(authentication);

  SecurityContextHolder.setContext(context);
  ```

  get

  ```java
  SecurityContext context = SecurityContextHolder.getContext();
    Authentication authentication = context.getAuthentication();
    String username = authentication.getName();
    Object principal = authentication.getPrincipal();
    Collection<? extends GrantedAuthority> authorities = authentication.getAuthorities();
  ```

인증

- UsernamePasswordAuthenticationFilter : 사용자 인증 요청을 `Authentication` 인터페이스로 추상화하고, `AuthenticationManager`를 호출한다.

  - Authentication :` getPricipal()(인증 아이디)`, `getCredentials()(인증 비밀번호)`, `getAuthorities()(사용자 권한목록)`, `getDetails()(부가정보)`, `isAuthenticated()(인증여부)`와 같은 메서드 제공

  ```java
  UsernamePasswordAuthenticationToken authentication= new UsernamePasswordAuthenticationToken(username, password);
  ```

- AuthenticaitonManager : 사용자 아이디/비밀번호를 인증하기 위해 적절한 `AuthenticationProvider` 찾아 처리를 위임한다.

  spring 보안 인증 프로세스의 핵심으로 방법을 정의하는 api

  ```java
  public interface AuthenticationManager {
      Authentication authenticate(Authentication authentication) throwsAuthenticationException;
  }
  ```

  커스텀 provider를 만들었다면 등록해주어야 한다

  ```java
  @Autowired
  public void configureAuthentication(AuthenticationManagerBuilder builder, JwtAuthenticationProvider jwtAuthenticationProvider) {
      builder.authenticationProvider(jwtAuthenticationProvider);
  }
  ```

- AuthenticationProvider : 실질적으로 사용자 인증을 처리하고, 인증 결과를 Authentication 인터페이스로 반환한다.

  커스텀 provider를 만들고자 한다면 이를 implements하여 구현

  ```java
  public interface AuthenticationProvider {
      Authentication authenticate(Authentication authentication) throws AuthenticationException;
      boolean supports(Class<?> authentication);
  }
  ```

- UserDetails : 사용자의 정보를 담는 인터페이스로 VO역할

  - getAuthorities() : 계정이 갖고있는 권한 목록을 리턴

  - getPassword() : 계정의 비밀번호를 리턴

  - getUsername() : 계정의 이름을 리턴

  - isAccountNonExpired() : 계정이 만료되지 않았는 지 리턴 (true: 만료안됨)

  - isAccountNonLocked() : 계정이 잠겨있지 않았는 지 리턴 (true: 잠기지 않음)

  - isCredentialNonExpired() : 비밀번호가 만료되지 않았는 지 리턴 (true: 만료안됨)

  - isEnabled() : 계정이 활성화(사용가능)인 지 리턴 (true: 활성화)

- UserDetailsService : DAO로 사용되며 사용자 정보를 로드하기 위한 인터페이스

인가

![](/spring/image/autho.PNG)

- AccessDecisionManager : 접근, 인가 결정을 내리는 인터페이스로 인증된 사용자의 리소스 접근 여부 판단하고, 접근 승인하는데 정책을 결정

  - AffirmativeBased: 접근을 승인하는 voter가 1개 이상
  - ConsesusBased: 과반수
  - UnanimouseBased: 모든 voter가 승인

    > Voter : 말그래도 투표자로 의사결정을 내리는 객체들. Manager는 여러개의 Voter를 가질 수 있다.

- AccessDecisionVoter : 해당 사용자의 인증level이 특정 object 접근level에 만족하는지 확인

  - ACCESS_GRANTED : 승인
  - ACCESS_DENIED : 거절
  - ACCESS_ABSTAIN : 보류

  - RoleVoter : 리소스에 접근하기 위해 권한을 사용자가 지니고있는지 확인
    - WebExpressionVoter : 웹 시큐리티에서 사용하는 기본 구현체로, SpEL표현식에 따른 접근 처리(ROLE\_\* 매치되는지 확인)

## 동작 흐름

![](/spring/image/security.png)

1. WAS가 필터 정보 수집 (이때, filter에는 encoding filter와 `delegating filter proxy`존재 하는데 이들은 최초로 등록되는 filter들이고 `delegating filter proxy`가 spring security filter chain에서 제공하는 fiter들을 받아 chian에 추가해주는 역할을 수행한다. _(그래서 proxy의 이름이 붙은 것 같다.)_ )

2. WAS에서 필터 클래스의 객체 생성후 doFilter()메서드 호출

   WAS는 완성된 `filterChain`의 필터들을 객체화해서 내부 저장하고 `Filter` 인터페이스를 상속 받고 몇개의 메서드를 구현하는데 그 중 `doFilter()`메서드는 `FilterChain`객체를 넘겨 받아야 한다.

   각 클래스의 doFilter는 반환형이 void로 데이터 전달은 request,session,Context를 통해 이루어지며 필터간 상호 의존 관계는 존재하지 않는다.

   `FilterChain`에도 doFilter()가 존재하는데 이는 자신을 실행하는 기능의 다른 필터들과는 다르게 FilterChain에 등록된 다음 Filter를 수행하는 메서드이다.

   이 메서드를 통해 FilterChain의 끝까지 필터를 실행한다.

3. 모든 필터 정상 수행시 doGet 메서드호출로 servlet 호출

<br><br>

---

## Reference

https://nomsblog.chakans.com/2016/10/spring-security-filter-chain.html

https://www.javadevjournal.com/spring-security/spring-security-authentication/

https://docs.spring.io/spring-security/site/docs/5.3.6.RELEASE/reference/html5/#servlet-authorization
