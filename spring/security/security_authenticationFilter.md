# Authentication Filter
## WebSecurityConfigurerAdapter

WebSecurityCongigurer(SecurityCongigurer)의 구현체로 `스프링 시큐리티의 웹 보안 기능 초기화, 설정`을 정의하는 추상클래스이다.

Custom으로 보안설정을 할때 이를 상속받아 정의하면된다.

이 추상 클래스에서는 세부 보안기능을 설정할 수 있는 API인 `HttpSecuriy`를 통해 `인증/인가 API`를 사용할 수 있다.

이 클래스를 상속한 클래스가 여러개라면 보안기능은 각각 동작하고 설정 클래스 별로 필터가 각각 생성한다. FilterChainProxy가 각 필터들도 따로 관리하며 가지고 있고 요청에 대한 url에 매칭되는 RequestMathcer와 매칭되는 필터가 작동한다.

### 인증 API

- http.formLogin()
- http.logout()
- http.csrf()
- http.SesseionManagement()
- http.RememberMe()
- http.ExceptionHandling()
- http.addFilter()

### 인가 API

- http.authorizeRequests()
- http.andtMathcers(/domain)
- http.hasRole(ADMIN)
- http.permitAll()
- http.authenticated()
- http.fullyAuthentication()
- http.access(hasRole(USER))
- http.denyAll()

```java
@EnableWebSecurity
public class CustomConfig extends WebSecurityConfigurerAdapter {
    @Override
    protected void configure(HttpSecurity http) throws Exception {
        http
                .authorizeRequests()
                .anyRequest().authenticated();
        http
                .formLogin();
    }
}

//application.properties
spring.security.user.name=gowoo
spring.security.user.password=1234
```

`application.properties`파일을 통해 초기 생성되는 계정의 name과 password를 변경이 가능하다.

### Form Login 인증

HttpSecurity의 API를 이용해 로그인페이지/성공,실패에 따른 페이지 등 핸들링할 수 있는 api를 제공한다.

- http.loginPage("/login") : 사용자 정의 로그인 페이지
- http.defaultSuccessUrl("/home") : 성공후 이동 페이지
- http.failureUrl("/login") : 실패 이동 페이지
- http.usernameParameter("username") : 아이디 파라미터 설정 (기본 제공하는 폼의 파라미터도 자동 설정)
- http.passwordParameter("passwd") : pw 파라미터 설정 (기본 제공하는 폼의 파라미터도 자동 설정)
- http.loginProcessUrl("/login") : 로그인 폼
- http.successHandler() : 로그인 성공 후 핸들러
- http.failureHandler() : 로그인 실패 후 핸들러

```java
@Override
protected void configure(HttpSecurity http) throws Exception {
    http
        .authorizeRequests()
        .anyRequest().authenticated();
    http
        .formLogin()
        .loginPage("/loginPage")
        .defaultSuccessUrl("/")
        .failureUrl("/loginPage")
        .usernameParameter("id")
        .passwordParameter("pw")
        .loginProcessingUrl("/login_proc")
        .successHandler((request, response, authentication) -> {
            System.out.println("authentication : " + authentication.getName());
            response.sendRedirect("/");
        })
        .failureHandler((request, response, exception) -> {
            System.out.println("exception : " + exception.getMessage());
            response.sendRedirect("/login");
        });
}
```

<br><Br>

## UsernamePasswordAuthenticationFilter

LoginForm인증은 해당 filter를 거치게 되고 해당 filter에 의해 요청 정보가 `AntPathRequestMatcher(/login)`에 매칭되는지 확인하고 매칭이 되지 않는다면 다른 filter를 수행한다. 매칭이 된다면 id와 password를 담은 Authentication객체를 이용해서 AuthenticationManager가 AuthenticationProvider를 에게 인증을 위임해서 인증을 처리하고 성공한다면 Authentication에 접근권한을 부여해 SecurityContext에 저장하게 된다.

UsernamePasswordAuthentication에서의 Authentication 추상 객체는 `UsernamePasswordAuthenticationToken`라는 구현체를 통해 구현을 하고 있고, AuthenticationMager의 구현체로는 `ProviderManger`가 된다. `Provider`객체의 `authenticate()`메서드내부의 `while()/provider.supports()`를 통해 적합한 Provider를 찾고 `result = provider.authenticate(authentication);`부분에서 Provider에게 인증을 위임한다.

<br><br>

## RememberMe

세션이 만료되고 웹 브라우저가 종료되어도 사용자를 기억하거나 `Remember-Me`쿠키에 대한 요청을 확인한 후 토큰 기반 인증을 사용해 유효성을 검사해 로그인 시키는 기능

SecurityContextHolder에 Authentication이 null일때 이 필터를 거쳐 기록된 인증정보가 있는지 판별

```java
@Autowired
UserDetailsService userDetailsService

@Override
protected void configure(HttpSecurity http) throws Exception {
    http
        .authorizeRequests()
        .anyRequest().authenticated();
    http
        .formLogin()
        .loginPage("/loginPage")
        .defaultSuccessUrl("/")
        .failureUrl("/loginPage")
        .usernameParameter("id")
        .passwordParameter("pw")
        .loginProcessingUrl("/login_proc")
        .successHandler((request, response, authentication) -> {
            System.out.println("authentication : " + authentication.getName());
            response.sendRedirect("/");
        })
        .failureHandler((request, response, exception) -> {
            System.out.println("exception : " + exception.getMessage());
            response.sendRedirect("/login");
        })
        .and()
        .rememberMe()
        .rememberMeParameter("remember")
        .tokenValidateSeconds(3600)     //default는 14일이다.
        .userDetailsService(userDetailsService)
}
```

<br><br>

## Session

```java
http.sessionManageMent()    //session기능 설정
    .maximumSession(1)      //최대 허용 가능 세션
    .maxSessionsPreventsLogin(true) //동시 로그인 차단
    .invalidSessionUrl()
    .expiredUrl()
    .sessionFixation().changeSessionId()  //이 값이 기본값으로 Session을 새로발급받기때문에 고정Session문제 해결
    .sessionCreateionPolicy(SessionCreationPolicy.Stateless) //Session 생성하지도않고 사용하지도 않음
                                //Always(항상 생성) / IfRequired(기본 값으로 필요시 생성) / Never(생성하지 않고 존재하면 사용)
```

### 동시 접속 예

1. UsernamePasswordAuthenticationFilter -> ConcurrentSessionControleAuthenticationStrategy 를 통해 Session Count 증가
1. ChangeSessionIdAuthenticationStrategy에서 session.changeSessionId()를 이용해 Session 생성
1. ResiterSessionAuthenticationStrategy에 세선정보 등록
1. 인증 성공
1. 다른 브라우저 에서 동일 아이디 접속
1. ConcurrentSessionControlAuthenticaionStrategy에서 session count를 증가 시키고 maxSession수와 비교
1. 틀릴 경우
   1. 인증 실패 전략일 경우 SessionAuthenticationException
      1. 인증 실패
   1. 세션 만료 전략인 경우 session.expireNow():첫번째 세션
      1. 인증 성공
      1. ChangeSessionIdAuthenticationStrategy에서 session.changeSessionId()수행
      1. ResiterSessionAuthenticationStrategy에서 sessino정보 등록
1. 첫번째 브라우저에서 접속시 ConcurrentSessionFilter에 접속
1. session 만료로 접속 실패

`ConcurrentSessionControleAuthenticationStrategy / ChangeSessionIdAuthenticationStrategy / ResiterSessionAuthenticationStrategy`는 SessionManagementFilter에서 의존하는 class

<br><br><br>

---

## Refernece

인프런 - Spring Security(정수원)
