# 스프링 빈

Spring IoC 컨테이너가 관리하는 자바 객체

Spring에서 ApplicationContext가 알고 있는 객체이다.

스프링은 스르핑 컨테이너에 스프링 빈을 등록할 때 기본으로 싱글톤으로 등록한다. _(유일하게 하나만 등록해서 공유 = 같은 스프링빈이면 모두 같은 인스턴스)_

<br>

## Spring IoC 컨테이너에 빈 등록 방법

1. 컴포넌트 스캔과 자동 의존관계 설정
   `@ComponentScan` 과 `@Component` 를 사용해서 빈을 등록

   `@Autowired`를 통해 Bean을 자동으로 주입 (의존성 주입, DI)

   - `@ComponentScan` : 컴포넌트를 찾는 지점을 알려주는 역할

     mainApplication 에 있는 `@SpringBootApplication`의 내부에 선언이 되어있다.

   - `@Component` : 실제로 빈으로 등록할 클래스

     `@Controller`, `@Service`, `@Repository`등은 내부에 선언이 되어있다.

     - `@Controller` : 서비스와 뷰의 중재자 역할

     - `@Service` : MVC패턴중에서 Model부분에 속하며 DAO와 DTO를 통해 비지니스 로직이 돌아가는 부분

     - `@Repository` : DB에 접근하는 클래스임을 명시 (인터페이스)

       `DAO`와 비슷하나 DAO는 DB에서 값을 꺼내와 도메인 오브젝트로 반환해주거나 적절한 값으로 반환해주는 계층이고 `Repository`는 한 도메인 오브젝트에 대해 객체의 값을 보증해주기 위해 도메인 내부에서 DB와 소통하는 객체

     - `@Entity` : DB테이블과 1:1로 맵핑

1. 자바코드로 직접 스프링 빈 등록
   빈 설정파일을 `xml`이나 `java`설정파일로 작성하여 직접 빈을 정의

   정형화 되지 않거나, 상황에 따라 구현 클래스를 변경해야 할때 이용

   - 자바 설정파일 작성

     `이름Configuration`이라는 클래스를 생성하여 클래스에 `@Configuration`을 붙인 후 그 안에 `@Bean`으로 직접 빈 정의

     Configuration 은 Component를 갖고있다

<br><br>

---

## Reference

https://www.inflearn.com/course/%EC%8A%A4%ED%94%84%EB%A7%81-%EC%9E%85%EB%AC%B8-%EC%8A%A4%ED%94%84%EB%A7%81%EB%B6%80%ED%8A%B8#description
