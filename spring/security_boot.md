## WebSecurityConfigurerAdapter

WebSecurityCongigurer(SecurityCongigurer)의 구현체로 `스프링 시큐리티의 웹 보안 기능 초기화, 설정`을 정의하는 추상클래스이다.

Custom으로 보안설정을 할때 이를 상속받아 정의하면된다.

이 추상 클래스에서는 세부 보안기능을 설정할 수 있는 API인 `HttpSecuriy`를 통해 `인증/인가 API`를 사용할 수 있다.

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

<br><br><br>

---

## Refernece

인프런 - Spring Security(정수원)
