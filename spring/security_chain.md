요청을 Servlet으로 보내기전에 중간에 위치한 Servlet Filter는 `서블릿 스펙`에 정의된 기술로 서블릿 컨테이너에서 실행되고 생성되기 때문에 `스프링`에서 만든 Bean이나 기술을 사용할 수 가 없다.

하지만, Spring Security는 Filter 기반으로 Servlet으로 요청전에 Filter에서 보안처리를 진행하기 때문에 스프링 기술을 사용할 수 있게끔 해야하는 요구사항이 생겼다.

## DelegatingFilterProxy

Servlet Container 영역

`DelegatingFilterProxy`를 이용해서 서블릿에서 관리하는 ServletFilter이고 이것이 스프링이 관리하는 Filter(Spring Bean)에게 요청을 위임하고 이 Bean이 구현한 Servlet Filter에서 Security보안처리를 하고 응답하는 방식이다.
한마디로 `DelegatingFilterProxy`는 ApplicationContext에서 `springSecurityFilterChain`이라는 이름으로 생선된 빈을 찾아 이 빈에게 요청을 위임하는 proxy역할을 한다.

## FilterChainProxy

스프링 빈으로 생성되는 클래스로 ServletFilter를 구현한 필터 클래스(Spring Container의 영역)

스프링 시큐리티 초기화 시 생성되는 필터들을 관리하고 제어하며 요청을 위임받아 실제로 보안을 처리하는 클래스

사용자의 요청을 필터 Chain순서대로 호출해서 전달하고 마지막 필터까지 예외가 발생하지 않았을때 보안이 통과되고 DispathcerServlet에게 요청을 전달한다.
