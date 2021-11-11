# 요청이 들어왔을때 스프링이 처리하는 방법 ( 내부구조 )
내가 이해하기 위해서 정리하는 스프링 요청 처리 구조

![architecture](/spring/image/spring-architecture.PNG)

<br>

### 1. Tomcat (Servlet Container)

톰캣은 WAS로써 미들웨어역할을 하지만 아파치의 일부분 기능을 서비스(httpd(웹서비스 데몬) native 모듈 포함)하고있어 Web Server역할도 수행할 수 있다.

톰캣의 메인 기능으로 서블릿 컨테이너역할인데 이는 서블릿의 라이플 사이클을 관리하며 DispatcherServlet도 해당 컨테이너에서 수행된다. 또한, 응답을 위한 소켓을 만드는 역할과 요청마다 쓰레드를 생성해 요청을 처리하기 위한 스레드풀을 관리한다.

해당 Tomcat도 결국 자바프로그램이기 때문에 별도의 JVM이 동작한다.

### 2. Servlet

요청에 대한 웹페이지나 결과값을 동적으로 생성 해주기 위한 역할을 수행하는 자바 프로그램

> 생명주기? init->service->destroy

SpringMVC에서는 DispatcherServlet이라는 FrontController 역할을 수행하는 Servlet이 존재하여 요청을 다른 컨트롤러에게 위임하는 방식으로 처리

#### DispatcherServlet

클래스 내부에 핸들러, 어댑터, 리졸버 등을 가지고 있어 요청에대한 응답이 가능하다. 이들을 인터페이스로 가지고 있으며 생성되는 시점에 ApplicationContext에서 빈들을 주입받아 생성된다. Spring이 생성하는 Servlet이다.

- HandlerMapping : 요청을 분석하여 맵핑된 Controller확인
- HandlerAdapter : Controller 에게 요청을 보내는 역할
- ViewResolver : Controller 에서 view를 return시 해당 view를 찾아 리턴해주는 역할

service()를 실행하고 해당 메서드에서 dispatch.doService() -> doDispatch()를 실행한다. (doDispatch는 HandlerMapping에서 핸들러를 가져오는 역할)


### 3. Spring Container

DispatcherServlet 는 Servlet WebApplicationContext와 Root WebApplicationContext가 존재한다. Root WebApplicationContext는 Service, datasource,repositories 들을 포함하고 있는 Context이고 Servlet WebApplicationContext는 RootWebApplicationContext를 상속받아 구현된 Context로 주로 Controller,Intercepter,ViewResolver,HandlerMapping과 같은 빈들이 존재한다.

Servlet을 구현할때 위처럼 상속관계로 나누어 Servlet WebApplicationContext를 구현한 이유는 서블릿 컨테이너 내부에 여러개의 서블릿이 올 수도 있는데 Service,datasource들은 공통적으로 사용될 수 있기 때문이다.

Container가 Bean 생성 시, Service-Locator 패턴으로 의존성을 주입하며 생성한다. 

<br>

#### Application Context

BeanFactory를 상속받고 있는 Context로 서로 다른 Servlet 끼리 공유해서 사용할 수 있는 Bean을 정의하고 해당 빈에서는 Servlet Context를 사용할 수가 없다.

#### Servlet Context

Servlet WebApplicationContext로 서블릿 단위로 생성되는 컨텍스트이다. Application Context와 해당 컨텍트으와 같은 id로 빈이 등록되는 경우 Servlet Context에 선언된 빈을 사용하며, 빈을 찾을 때에는 Servlet Context-> Application Context 순서로 찾기 때문에 해당 컨텍스트에 정의된 빈에서는 Application Context의 빈을 사용할 수 있다.

서블릿의 생명주기를 관리한게 서블릿 컨테이너였다면 스프링 컨테이너는 빈의 라이플 사이클을 관리하며 IOC/DI를 제공해주는 역할을 수행한다.

<br><br>

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

<br><br>

## Spring과 Spring boot의 차이점
기존 Spring은 Apache Tomcat(Servlet Container)에의해 ContextLoaderListener로 ApplicationContext를 생성하고 요청이 들어온다면 이 정보를 가지고 DispatcherServlet을 만드는 것이라면, Spring boot는 Application이 먼저 띄워져 TomcatStarter의 onStartup()메서드로 톰캣이 실행되고 다음 DispatcherServlet 순으로 생성이된다. 한마디로 Tomcat보다 Application이 먼저 실행된다.

<br><br>

## Controller 1개가 어떻게 많은 요청을 처리하는가
Tomcat 내부적으로 스레드풀을 만들어 하나의 요청에 하나의 스레드를 할당하여 응답을 처리하는데 이때 Controller는 스프링 빈이고 빈은 싱글톤패턴으로 1개만 생성이되는데 어떻게 여러 스레드에서 객체를 공유하여 사용이 가능할까

Controller 객체 하나를 생성하면 객체 자체는 Heap에 생성되지만 Class 정보는 Method Area에 저장되고 Controller는 내부적으로 상태가 존재하지 않고 메서드에 대한 정보만 공유해서 사용하면 되기 때문에 동기화에 대한 걱정이 없다. 한마디로 처리로직만 공유되어 사용하는 것이기 때문에 몇개의 요청이 들어오든 상관이 없다.


<br><br>


## 커넥션당 쓰레드를 만드는 것보다 요청당 쓰레드를 만드는것을 사용하는 이유
결론부터 말하면 확장성에 유리하다. 자바 쓰레드의 비용은 비싼데 요청이 오지 않는 connection을 계속 유지하여 스레드를 낭비하고 새로운 스레드를 생성하는 것보다 요청마다 스레드를 할당하고 반환하는 것이 더 비용이 저렴하다. `keep-alive`를 통해 connection 별로 스레드를 유지할 수 도 있다.


<br><br>

## JVM이 Servlet을 실행하는 것과, 일반 자바 클래스를 실행하는 것의 차이
호출 방식은 같으나 서블릿은 main()함수로 호출되지 않고 Container에 의해 실행되는 것.


----

## Reference

https://medium.com/@jypthemiracle/servletcontainer%EC%99%80-springcontainer%EB%8A%94-%EB%AC%B4%EC%97%87%EC%9D%B4-%EB%8B%A4%EB%A5%B8%EA%B0%80-626d27a80fe5