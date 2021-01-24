# Mock Object

해석하면 `모의 객체`라는 의미로 프로그램을 테스트 할 때 실제 사용하는 모듈(객체)을 사용하지 않고 실제 모듈을 흉내내는 가짜 모듈을 작성하여 테스트 효용성을 높이는 객체

## Stub과의 차이점

> Stub은 `상태 검증`에 사용하고 Mock Object는 `행위 검증`에 사용하는 것이라고 `마틴 파울러`는 설명하고 있다.
>
> 출처 : http://martinfowler.com/articles/mocksArentStubs.html

# Spring 단위 테스트

## @SpringBootTest

일반적인 테스트로 slicing을 사용하지 않고 전체 프로그램 컨텍스트를 시작하기 때문에 모든 파일을 로드하고 bean을 주입하기 때문에 속도가 느리다.

SpringBootTest에서 `MockMVC`를 사용하기 위해 @AutoConfigureMockMvc를 붙여주면 사용할 수 있다. (내부에 webEnvirment의 기본값이 mock으로 되어있어 사용 가능)

## @WebMvcTest

MVC를 위한 테스트로 계층별로 나누어서 웹과 관련된 부분만 테스트하기 때문에 빠르게 테스트가 가능하다.(슬라이스 테스트)

Contoller 계층만 등록 (서비스 등록 x)
<br>_(@Controller, @ControlloerAdvice, @JsonComponent, @Conveter, @GenericConverter, @Filter, @handlerInterceptor,@WebMvcConfigurer 만 스캔 )_

`MockMvc`,`MockBean`을 자동 설정을 자동으로 설정 해주고 `Spring Security`의 테스트도 지원한다.

- MockMvc : 스프링 MVC 테스트 핵심 클래스
  웹 서버를 뜨위지 않고도 스프링 MVC(DisapatcherServlet)이 요청을 처리하는 과정을 확인할 수 있어 컨트롤러 테스트용으로 자주 쓴다. (단위테스트보다는 객체를 더 많이 만들기 때문에 빠르지는 않다.)

  - perform : 실제 요청을 수행하는 함수
    내부에 파라미터들로 RequestBuilder를 이용해 contentType, accept,content등 다양한 메서드들로 요청 헤더에 값을 set할 수 있다.

    - MockMvcRequestBuilder에 올 수 있는 메서드 : post, get, delete,put,patch,options,head,request

  - andDo : perform 수행후 내부 파라미터 메서드를 실행
  - andExpect : 응답으로 기대하는 값들을 setting
  - andReturn

  **Mock 객체는 return 값이 null**

- MockBean
  스프링 부트 테스트 패키지 내부에 존재하고 테스트 하려는 기존 객체내의 Bean이 아닌 MockBean을 주입해 사용한다

  Mock과 마찬가지로 mock객체의 행위를 지정해 줄 수 있다.

### 웹 관련 Bean만 등록을 하여 사용하기 때문에 Repository같은 Bean을 등록하지 않기 때문에 이도 등록하려면 MockBean(Spring Boot Test 내부에 존재) 을 이용하여 테스트를 진행해야 한다.

## Mockito

Mock 객체를 직접 만들어 테스트 코드 작성하는 것은 번거롭기도하고 Mock클래스 관리도 부담스럽기 때문에 시간을 상대적으로 절약하기 위한 라이브러리

- Mock
  Mockito 라이브러리 내부에 위치해 mock객체가 특정 메서드를 호출 했을 때 동작하는 방식을 설정한다.

  ```java
  Mockito.when(eventRepository.save(event)).thenReturn(event);
  ```
