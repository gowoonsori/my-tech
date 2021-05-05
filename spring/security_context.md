## SecurityContext

Authentication 객체가 저장되는 저장소로 ThreadLocal에 저장되어 아무곳에서나 참조가 가능하도록 설계되어있고, 쓰레드마다 각각의 Context가 생기기때문에 Thread Safe하다.

인증이 완료되면 HttpSession에 저장되어 전역적으로 참조가 가능하다.

<br><br>

## SecurityContextHolder

SecurityContext들을 담고있는 저장소

### 저장 방식

1. MODE_THREADLOCAL : 스레드당 SecurityContext 객체를 할당 (default)

1. MODE_INHERITABLETHREADLOCAL : 메인스레드와 자식스레드가 동일한 Context 할당(자식스레드가 메인스레드의 Context를 공유)
1. MODE_GLOBAL : 한개의 앱에서 하나의 context를 할당

<br>

#### 생성

```java
SecurityContext context = SecurityContextHolder.createEmptyContext();
Authentication authentication = new TestingAuthenticationToken("username", "password", "ROLE_USER");
context.setAuthentication(authentication);

SecurityContextHolder.setContext(context);
```

#### 조회

```java
SecurityContext context = SecurityContextHolder.getContext();
Authentication authentication = context.getAuthentication();
String username = authentication.getName();
Object principal = authentication.getPrincipal();
Collection<? extends GrantedAuthority> authorities = authentication.getAuthorities();
```

<br><br>

### SecurityContextPersistenceFilter

SecurityContext 객체의 생성, 저장, 조회를 수행

- 익명 사용자

  - 새로운 SecurityContext 객체를 생성해 SecurityContextHolder에 저장
  - AnonymousAuthenticationFilter에서 AnonymousAuthenticationToken객체를 SecurityContext에 저장

- 인증 시도

  - 새로운 ScurityContext객체를 생성해 SecurityContextHolder 에 저장
  - UsernamePasswordAuthenticationFilter에서 인증 성공 후 SecurityContext에 UsernamePasswordAuthentication객체를 SecurityContext에 저장
  - 인증이 최종 완료되면(보통 Provider에서 최종 인증을 수행) Session에 SecurityContext를 저장

- 인증 후

  - Session에서 SecurityContext를 꺼내 SecurityContextHolder에서 저장
  - SecurityContext안에 Authentication객체가 존재하면 인증 유지

- 최종 응답 후
  - SecurityContextHolder.clearContext() : 매 요청마다 token, session등을 들고 요청하기 때문에 응답후에는 context를 비운다.
