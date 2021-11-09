# Spring Framework

자바 플랫폼을 위한 오픈소스 애플리케이션 프레임워크로써 MVC모듈을 제공하여 웹을 효과적으로 개발하기 위한 다양한 서비스를 제공한다.

개발에 필요한 모든 기술을 제공하고 처리를 전담하여 개발자는 비즈니스 로직 개발 업무에 집중 할 수 있게 설계된 프레임워크

<br>

## 장점

- 단순화 된 단위 테스트
- 복잡한 코드의 감소
- 아키텍처의 유연성



<br>

## 특징

1.  크기와 부하 측면에서 경량화 ( 경량 컨테이너 )

1.  제어 역행 (IoC, Inversion of Control)

    - 결합도를 느슨하게 하기 위함
    - `control`의 제어권이 사용자가 아닌 프레임워크에 있다.

1.  의존성 주입 (DI, Dependency Injection)

    - 각각의 계층이나 서비스들 간의 의존성이 존재할 경우 프레임워크가 연결시켜준다.

    - 방법

      - 필드 주입 : 가장 간단한 방법으로 사용하려고 하는 클래스에 선언 후 `@Autowired`키워드를 붙여주면 자동으로 주입이된다.

        - 문제점 :

          1. 단일 책임의 원칙 위반
          1. 불변성 : final을 선언할 수없어 객체가 변할 수 있다.

      - setter 주입 : setter기능의 메서드에 @Autowired를 붙여 구현하는 방식

        - 문제점 :
          1. 불변성 : 이 방법또한 객체가 변할 수 있는 문제가 있다.

      - 생성자 주입 : 조립 시접에 주입

        의존성 주입시 생성자를 인자로 넘기는 방식

        spring4.3이후부터는 @Autowired생략 가능

        final을 붙여 불변성 문제도 해결가능하다.

1.  관점지향 프로그래밍 (AOP, Aspect-Oriented Programing)

    - 트랜잭션이나, 로깅, 보안같은 여러 모듈에서 공통적으로 사용하는 기능의 경우 해당 기능을 분리하여 관리.
      <br>이처럼 모든 모듈에서 적용되어야 하는 기능들을 횡단 관심(공통 관심사항,cross-cutting concerns)라고 한다.

      ex) 모든 메소드의 실행 시간을 측정하고싶어! 할때, 모든 메소드에 코드를 집어넣기엔 유지 보수가 힘들고 공통 로직을 구현이 힘들때 사용
      `@Around("execution(* 패키지 명..*(..))")`과 같이 관심 파일들 적용
      `SpringConfig`에 `@Bean`으로 AOP파일 등록해서 사용 가능

      controller가 해당 service를 실행시 프록시(가짜 스프링빈)을 만들어 AOP를 실행후 joinPoint.proceed()를 호출하여 실제 service를 호출. controller는 proxy와 작용하는 셈

1.  애플리케이션 객체의 생명주기와 설정을 관리한다는 점에서 일종의 컨테이너

1.  PSA(Portable Service Abstraction)
    - 다른 여러 모듈을 사용함에 있어서 별도의 추상화 레이어를 제공

<br>

## 모듈

![modules](/spring/image/modules.png)

- Core Container : 스프링 프레임워크의 기본 모듈
  - Beans : 스프링 Ioc컨테이너에 의해 관리되며 애플리케이션의 핵심을 이루는 객체들. 의존성 주입 재공
  - Core : 스프링 모듈이 사용하는 유틸
  - Context : 빈 팩토리를 상속하는 애플리케이션 콘텍스트를 구현하고, 리소스 로드 및 국제화 지원
  - SpEL : EL(JSP표현 언어)를 확장하고 빈 속성 접근 처리를 위한 언어 제공
- AOP / Instrumentation : AOP 및 class Instrumentation을 지원하는 모듈

- Messaging : 스프링 MVC 어노테이션처럼 메세지를 메소드에 맵핑시키는 어노테이션의 세트

- Data Access / Integration : DB 및 메시징 공급자와의 상호작용을 간소화하는 모듈

  - JDBC : 여러곳에서 사용되는 상용구 코드를 방지하기 위해 추상화
  - ORM : ORM, JPA, HIBERNATE등 제공
  - OXM : XML매핑 통합 객체 제공
  - Transactions : POJO 및 다른 클래스에 대한 선언적 트랜개션 관리를 제공
    <br> _(POJO는 사용자가 만들어낸 객체로서, 이또한 스프링이 라이프사이클 관리를 위임해서 수행)_

- Web : 웹 밑 포틀릿 앱 개발을 간소화하는 모듈

- Test : 단위 및 통합 테스트 생성을 간소화하는 모듈

<br>

## 모듈간 의존성

![모듈간 의존성](/spring/image/module_dependency.png)

<br>
<br>

### 도메인 : 소프트웨어를 개발하는 대상 영역. 개발대상과 범위

<br><br>

---

## Reference

위키 백과 - https://ko.wikipedia.org/wiki/%EC%8A%A4%ED%94%84%EB%A7%81_%ED%94%84%EB%A0%88%EC%9E%84%EC%9B%8C%ED%81%AC

crosscutting concerns - https://winmargo.tistory.com/89

특징 설명 - https://opentutorials.org/course/2428/13594

spring mvc 동작 순서 - https://devpad.tistory.com/24

DispatcherServlet 동작원리 - https://galid1.tistory.com/526
