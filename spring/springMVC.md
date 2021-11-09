# MVC 패턴

- Model : 비지니스 로직 처리를 하는 역할

  - DTO : Data Transfer Object로 데이터를 처리하기 위해 객체로 전환하는 setter와 데이터를 읽기위한 getter로 구성. front의 데이터가 처음저장 되는 Object로 유효성 검사또한 수행한다.

  - DAO : Data Access Object : 데이터 접근을 처리하는 객체로 DB에 접근하는 오브젝트.

  - VO : DTO와 동일한 개념이나 읽기 권한만 갖는다.

- Controller : 데이터를 전달한 Mapping 정보가 저장되는 클래스.
  <br>어떻게 처리 할지 알려주는 역할로 일종의 Model과 View의 Proxy역할

- View : 클라이언트와 상호작용하며 데이터를 입력받거나 처리된 데이터를 사용자에게 보여주는 부분

<br>

## Spring MVC 전체적인 동작 순서

![동작 사이클](/spring/image/run-cycle2.png)

1. 요청이 들어오면 DispatcherServlet이 web.xml에 등록된 내용만 요청을 가로챈다.

   - 요청이들어오면 doService()실행 -> doDispatch()호출 doDisapatch에게 위임 (모든 요청을 각각의 알맞은 Handler에게 전달하는 역할)

1. 가로챈 요청을 HandlerMapping에게 보내 요청을 처리할 Controller를 찾는다.

   - doDispatch에서 HandlerMapping을 통해 요청에 맞는 HandlerMethod를 찾는다.

1. 찾은 Controller정보를 HanlderAdapter에게 넘긴다.

1. 찾은 컨트롤러(@RequestMapping)에게 가서 로직 처리를 전달한다.

   - handlerMethod 실행

1. 로직 처리 (Controller -> Service -> DAO -> DB -> DAO -> Service -> Controller) 후 보여줄 view정보와 데이터를 넘긴다.

   - handlerMethod에서 RetrunValueHanler에 의해 handleReturnValue()를 호출하여 handlerMethod의 실행결과값을 적절한 Response를 생성

1. DispathcerServlet은 ViewResolver에게 view정보를 넘기면 ViewResolver가 view를 찾는다.

1. 찾은 view에게 찾은 데이터를 보내 완성한 page(render)를 DispatcherServlet이 클라이언트에게 최종적으로 보낸다.

<br>

## 파일 구조 (Maven)

```
project
    └ src/main/java
    │   └패키지명
    │       └contoller.java
    └ src/main/resources
    │   └META-INF
    │   └log4j.xml
    └ src/test/java
    └ src/test/resources
    └ JRE System Library
    └ Maven Dependencies
    └ src
    │   └main
    │       └webapp
    │           └resouces
    │           └WEB-INF
    │               └classes
    │               └spring
    │               │   └appServlet
    │               │   │   └servlet-context.xml
    │               │   └root-context.xml
    │               └views
    │               │   └home.jsp
    │               └web.xml
    └ target
    └ pom.xml
```

- src/main/java : java파일. 스프링 구조에 맞춰 클래스 파일들 작성

- src/main/resources : 자바 클래스에서 사용하는 리소스들. DB연결을 위한 파일, 의존성 주입을 위한 xml등 모든 파일

- src/test/java : 테스트를 위한 자바 코드

- src/test/resources : 테스트를 위한 리소스 파일들

- Maven Dependencies : Maven에서 자동으로 관리해주는 라이브러리들. <br>pom.xml에 작성된 라이브러리들을 자동으로 다운, 관리

- src : Web에 관련된 데이터들이 있는 루트 폴더

  - main/webapp/resources : 웹에 필요한 데이터들<br>css,js,img와 같이 클라이언트가 직접 접근할 수 있는 공간. (controller가 요청을 가로채지않고 바로 접근할 수 있도록 설정하여 사용하는 곳.)

  - main/webapp/WEB-INF : 웹에 필요한 코드파일과 컴파일된 파일, 환경설정 파일들<br> 컨트롤러를 통해서만 접근 가능
    - classes : 컴파일된 파일 보관
    - spring : 스프링 환경설정 파일(context) 보관
    - views : jsp, html파일 보관 <br>이 폴더가 `'/'`의 기준점
    - web.xml : 웹 설정 파일

- pom.xml : Maven 설정 파일

<br>

## web.xml

WAS가 최초 구동될때 웹 애플리케이션 설정을 위한 파일

- \<servlet> : DipatcherServlet을 구현하기 위해 사용할 클래스와 초기 파라미터 정보 포함

- \<servlet-name> : 이 이름을 가지고 다른 설정파일에서 서블릿 정보 참조

- \<servlet-class> : 어떤 클래스를 사용할지 명시

- \<init-param> : 초기 파라미터 정보로써 기술하지 않으면 스프링이 자동적으로 appServlet-context.xml을 이용하여 스프링 컨테이너 생성

- \<laod-on-startup> : 서블릿이 로딩될때 로딩 순서를 결정하는 값
- \<servlet-mapping> : \<url-pattern>의 패턴으로 요청이 들어오면 해당 servlet에게 요청을 전달하는 정보 기술

<br>

## servelet-context.xml

서블릿 관련 설정 파일로 `prefix`와 `suffix`를 붙여주는 역할을 해 일일이 전체경로와 파일확장자를 붙이지 않아도 되도록 해준다.

스프링에서 사용하는 bean을 일일이 선언하지 않고도 어노테이션을 자동적으로 인식하게 하는 역할

- \<annotation-driven> : @Controller 어노테이션을 감지하여 Controller로 등록

- \<resources> : 정적인 웹 리소스들의 정보를 기술
- \<beans:bean class="org.springframework.web.servlet.view.InternalResourceBiewResolver"> : Controller가 Model을 리턴하고 DisaptcherServelt이 jsp파일을 찾을때 쓰이는 정보를 기술
- \<context:component-scan> : @Component로 등록된 Bean객체를 찾게 도와주는 역할

<br>

## Controller 파일

- 클래스내 메서드들 : return은 문자열로 servlet-context.xml의 설정을 참조하여 view파일에 대한 정보를 제공.
