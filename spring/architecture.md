# 요청이 들어왔을때 스프링이 처리하는 방법 ( 내부구조 )

## 사전지식

### 1. Tomcat

톰캣은 WAS로써 미들웨어역할을 하지만 아파치의 일부분 기능을 서비스(httpd(웹서비스 데몬) native 모듈 포함)하고있어 Web Server역할도 수행할 수 있다.

### 2. Servlet

요청에 대한 웹페이지나 결과값을 동적으로 생성 해주기 위한 역할을 수행하는 자바 프로그램

> 생명주기? init->service->destroy

SpringMVC에서는 DispatcherServlet이라는 FrontController 역할을 수행하는 Servlet이 존재하여 요청을 다른 컨트롤러에게 위임하는 방식으로 처리

#### DispatcherServlet

클래스 내부에 핸들러, 어댑터, 리졸버 등을 가지고 있어 요청에대한 응답이 가능하다.

- HandlerMapping : 요청을 분석하여 맵핑된 Controller확인
- HandlerAdapter : Controller 에게 요청을 보내는 역할
- ViewResolver : Controller 에서 view를 return시 해당 view를 찾아 리턴해주는 역할

### 3. Servlet Container

톰캣의 메인 기능으로 서블릿의 라이플 사이클을 관리하며 DispatcherServlet도 해당 컨테이너에서 수행된다. 또한, 응답을 위한 소켓을 만드는 역할과 요청마다 쓰레드를 생성해 요청을 처리하기 위한 스레드풀을 관리한다.

### 4. Spring Container

DispatcherServlet 내부에 Servlet WebApplicationContext와 Root WebApplicationContext가 존재한다. Root WebApplicationContext는 Service, datasource,repositories 들을 포함하고 있는 Context이고 Servlet WebApplicationContext는 RootWebApplicationContext를 상속받아 구현된 Context로 주로 Controller,Intercepter,ViewResolver,HandlerMapping과 같은 빈들이 존재한다.

Servlet을 구현할때 위처럼 상속관계로 나누어 Servlet WebApplicationContext를 구현한 이유는 서블릿 컨테이너 내부에 여러개의 서블릿이 올 수도 있는데 Service,datasource들은 공통적으로 사용될 수 있기 때문이다.

#### Application Context

BeanFactory를 상속받고 있는 Context로 서로 다른 Servlet 끼리 공유해서 사용할 수 있는 Bean을 정의하고 해당 빈에서는 Servlet Context를 사용할 수가 없다.

#### Servlet Context

Servlet WebApplicationContext로 서블릿 단위로 생성되는 컨텍스트이다. Application Context와 해당 컨텍트으와 같은 id로 빈이 등록되는 경우 Servlet Context에 선언된 빈을 사용하며, 빈을 찾을 때에는 Servlet Context-> Application Context 순서로 찾기 때문에 해당 컨텍스트에 정의된 빈에서는 Application Context의 빈을 사용할 수 있다.

서블릿의 생명주기를 관리한게 서블릿 컨테이너였다면 스프링 컨테이너는 빈의 라이플 사이클을 관리하며 IOC/DI를 제공해주는 역할을 수행한다.

## 서버 시작과 요청까지의 단계

1. Web server init
1. Root WebApplicationContext 로딩
1. Web server start
1. Client가 Web server로 Request
1. Web Server가 Servlet Container로 전달
1. Servlet 스레드 생성
1. 서블릿이 생성안되어있다면 DispatcherServlet init
1. 생성된 스레드에서 DisapatcherServlet의 service() 메서드 호출
1. HandlerMapping을 통해 컨트롤러 조회
1. HandlerAdapter를 통해 컨트롤러에게 전달
1. Contrller -> Service-> 동작 후 응답
