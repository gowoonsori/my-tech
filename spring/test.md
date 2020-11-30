# Test

## Spring 단위 테스트

## SpringBootTest

일반적인 테스트로 slicing을 사용하지 않고 전체 프로그램 컨텍스트를 시작하기 때문에 모든 파일을 로드하고 bean을 주입하기 때문에 속도가 느리다.

SpringBootTest에서 MockMVC를 사용하기 위해 @AutoConfigureMockMvc를 붙여주면 사용할 수 있다. (내부에 webEnvirment의 기본값이 mock으로 되어있어 사용 가능)

## WebMvcTest

계층별로 나누어서 웹과 관련된 부분만 테스트하기 때문에 빠르게 테스트가 가능하다.(슬라이스 테스트)

Contoller 계층만 등록 (서비스 등록 x)

MockMvc 빈을 자동 설정을 자동으로 설정 해준다.

- MockMvc : 스프링 MVC 테스트 핵심 클래스

  웹 서버를 뜨위지 않고도 스프링 MVC(DisapatcherServlet)이 요청을 처리하는 과정을 확인할 수 있어 컨트롤러 테스트용으로 자주 쓴다. (단위테스트보다는 객체를 더 많이 만들기 때문에 빠르지는 않다.)

  - perform
  - andDo
  - andExpect
  - andReturn

- MockMvcRequestBuilder
  - post, get, delete,put,patch,options,head,request

### 웹 관련 Bean만 등록을 하여 사용하기 때문에 Repository같은 Bean을 등록하지 않기 때문에 MockBean을 이용하여 테스트를 진행해야 한다.

## Mockito

Mock 객체는 return 값이 null

웹 관련 Bean만 등록을 하여 사용하기 때문에 Repository같은 Bean을 등록하지 않기 때문에 MockBean을 이용하여 테스트를 진행해야 한다.

- Mock
  Mockito 라이브러리 내부에 위치해 mock객체가 특정 메서드를 호출 했을 때 동작하는 방식을 설정한다.

- MockBean

  스프링 부트 테스트 패키지 내부에 존재하고 테스트 하려는 기존 객체내의 Bean이 아닌 MockBean을 주입해 사용한다

  @SpringBootTest나 @WebMVCTest와 함께 사용하고, Mock과 마찬가지로 mock객체의 행위를 지정해 줄 수 있다.

  ```

  ```
