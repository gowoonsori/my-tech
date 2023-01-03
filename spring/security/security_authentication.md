# Authentication

인증 정보로 사용자의 인증정보를 저장하는 토큰같은 개념

인증시 id/password를 담고 인증 검증을 위해 이를 전달/사용한다.

인증 후에는 최종 결과(인증 주체/객체/비밀번호/권한정보 등)를 담고 SecurityContext에 저장되어 전역으로 참조 가능하다.

### 구조

1. principal : 인증 주체(id나 User객체와 같이 사용자를 식별)
1. credentials : 비밀번호
1. authorities : 권한, 역할
1. details : 부가 정보
1. Authenticated : 인증 여부(T/F)

### 과정

1. Id/Pw를 서버에 전달
1. UsernamePasswordAuthenticationFilter에서 이를 필터링
1. 요청한 Id/PW를 담은 Authentication 객체 생성
1. AuthenticationManager에게 이 인증 객체 전달(수신)
1. Manager는 적합한 인증객체 Provider에게 인증객체 전달
1. Provider는 요청 정보를 이용해 인증과정 수행
1. 인증이 성공한다면 권한과 인증 여부를 셋팅한 인증객체를 SecurityContext에 저장

<br>
<br>

### UsernamePasswordAuthenticationFilter

사용자 인증 요청을 `Authentication` 인터페이스로 추상화하고, `AuthenticationManager`를 호출한다.

<br>

### Authentication

실제 사용자 인증 정보를 의미하는 인터페이스

- Principal : 사용자를 구분(일종의 id) -> 접근 주체
- Credentials : 접근 주체의 비밀번호
- Authorities : 사용자의 ROLE

` getPricipal()(인증 아이디)`, `getCredentials()(인증 비밀번호)`, `getAuthorities()(사용자 권한목록)`, `getDetails()(부가정보)`, `isAuthenticated()(인증여부)`와 같은 메서드 제공

```java
UsernamePasswordAuthenticationToken authentication= new UsernamePasswordAuthenticationToken(username, password);
```

<br>

### AuthenticaitonManager

사용자 아이디/비밀번호를 인증하기 위해 적절한 `AuthenticationProvider` 찾아 처리를 위임한다. 구현객체로 ProviderManager를 제공한다.

(기본 ProviderMansger에서 Form인증(`DaoAuthenticationProvider`)은 , RememberMe인증(`RememberMeAuthenticationProvider`)을 제공 )

기본적으로 제공하는 Provider가 없는 JWT, OAuth와 같은 별도의 인증을 추가 하고자 하면 부모ProviderManager를 탐색해서 처리할 수 있는 provider를 찾는다.

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

<br>

### AuthenticationProvider

실질적으로 사용자 인증을 처리하고, 인증 결과를 Authentication 인터페이스로 반환한다.

커스텀 provider를 만들고자 한다면 이를 implements하여 구현

`authenticate()`에서 실제 인증을 처리하고 `supports()`는 AuthenticationManager에서 요청인증객체에 적합함 Provider를 찾기 위한 메서드이다.

```java
public interface AuthenticationProvider {
    Authentication authenticate(Authentication authentication) throws AuthenticationException;
    boolean supports(Class<?> authentication);
}
```

<br>

### UserDetails

사용자의 정보를 담는 인터페이스로 VO역할

- getAuthorities() : 계정이 갖고있는 권한 목록을 리턴

- getPassword() : 계정의 비밀번호를 리턴

- getUsername() : 계정의 이름을 리턴

- isAccountNonExpired() : 계정이 만료되지 않았는 지 리턴 (true: 만료안됨)

- isAccountNonLocked() : 계정이 잠겨있지 않았는 지 리턴 (true: 잠기지 않음)

- isCredentialNonExpired() : 비밀번호가 만료되지 않았는 지 리턴 (true: 만료안됨)

- isEnabled() : 계정이 활성화(사용가능)인 지 리턴 (true: 활성화)

- UserDetailsService : DAO로 사용되며 사용자 정보를 로드하기 위한 인터페이스로 `UserDetails`를 반환하는 하나의 메서드를 갖고있다.
