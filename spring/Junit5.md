# JUnit5

자바 프로그래밍용 Unit 테스트 프레임워크

런타임시 Java 8이상이 필요하며 컴파일 타임시에 JAR로서 링크된다.

Spring Boot를 이용하면 내부에 dependency가 포함되어 있다.

## 구조

- JUnit Platform : 테스트를 발견하고 계획을 생성하는 `TestEngine`인터페이스를 갖고 있다.

  이를 통해 테스트를 발견,실행,보고한다.

- JUnit Jupiter : TestEngine의 실제 구현체는 별도 모듈중 하나로 `Juptier-API`를 이용한 테스트 코드를 발견하고 실행

  > Jupiter API는 JUnit5에 새롭게 추가된 테스트 코드용 API

- JUnit Vintage : 기존 버전으로 작성한 테스트 코드를 실행할때 이 모듈을 이용

## 어노테이션

### @Ignore

테스트로 안쓰이는 클래스

테스트내 중복 코드제거를 위해 클래스 상속을 이용하여 만들때 사용해주어야한다.

### @Test

테스트 메서드 임을 알리는 어노테이션

### @Parameterized Test

매개 변수화 된 테스트임을 알림

### @Repeated Test

반복 테스트를 위한 테스트 템플릿임을 알림

### TestFactory

동적 테스트를 위한 테스트 팩토리임을 알림

### DisplayName

해당 테스트 클래스 or 메서드의 console에 보여지는 이름을 정의

### DisplayNameGenration

테스트 클래스에 대해 사용자 정의 이름을 선언

### @BeforeEach

@Test, @RepeatedTest, @Parameterized, @TestFactory가 붙은 메서드 전에 실행되는 테스트

### @AfterEach

@Test, @RepeatedTest, @Parameterized, @TestFactory가 붙은 메서드 후에 실행되는 테스트

### @Disabled

테스트 클래스 or 메서드를 비활성화
