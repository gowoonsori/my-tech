# Spring Security

스프링에서 제공하는 애플리케이션 보안(인증,인가 ,권한)등을 담당하고 기능을 제공해주는 하위 프레임워크

## Spring Security 의존성 추가시 일어나는 일

1. 의존성만 추가해도 기본적인 웹 보안설정이 이루어 진다.
1. 모든 요청은 인증이 되어야 접근이 가능하다.
1. 인증 방식은 폼 로그인 방식과 httpBasic 로그인 방식 제공
1. 기본 로그인 페이지 제공
1. 기본 계정 한개 제공 ( user:console창에 입력되는 random 문자열 )

## 종류

Spring framework 5.x이후 Webflux가 추가됨에 따라 `Servlet App` ,`Reactive App(Webflux)` 두가지로 나눌 수 있다.

## 특징

- 웹 시큐리티 (Filter 흐름에 따라 처리 ) : url요청이 있을때 흐름에 따라 인증,권한 처리

- 메서드 시큐리티 : url요청에 상관없이 메소드가 호출되었을때 인증,권한을 처리
- 요청시 가장 먼저 url요청을 받는다. ( Dispatcher Servlet으로 가기전에 먼저 적용 )

- Credential 기반 인증 : Principal(접근 주체)를 아이디로, Credential(비밀번호)를 임의로 생성된 비밀번호로 사용

<br><br>

## 큰 구조

![Structure](/spring/image/security-structure.PNG)

인증과 인가 모두 Interceptor를 통해 수행되며 메서드,filter방식으로 동작이 가능하고, 인증에 관한 정보들을 담아 두는곳은 `SecurityContext`에 저장이 되며 `SecurityContextHolder`를 통해 접근이 가능하다.
<br>_(기본설정은 ThreadLocal에 저장 되며 스레드마다 할당되는 데이터 공간이다)_

SecurityContextHolder : 인증 정보에 접근하기 위한 인터페이스

<br><br>

## 동작 흐름

![](/spring/image/security.png)

1. WAS가 필터 정보 수집 (이때, filter에는 encoding filter와 `delegating filter proxy`등 Servlet Filter가 존재 하는데 이들은 최초로 등록되는 filter들이다.

   `delegating filter proxy`는 Servlet Container 영역으로 spring security filter를 사용하기 위해 `springSecurityFilterChain`이라는 이름의 `FilterChainProxy`에게 요청에 대한 인증을 위임한다. (WebSecurity가 Filter들을 포함한 FilterChainProxy를 생성)

2. FilterChainProxy는 doFilter()메서드 호출하여 내부의 Filter들을 수행

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
