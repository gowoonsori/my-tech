# Spring HATEOAS

Hypermedia As The Engine Of Application State의 약자로 하이퍼 링크를 통해 상태 이동이 일어나야 한다는 조건을 만족하기 위해 제공하는 라이브러리

response body에 링크를 제공하여 client가 참고 할 수 있도록 하는 것

## 주요 기능

- 링크를 만드는 기능

  - 문자열 가지고 만들기
  - 컨트롤러와 메서드로 만들기

- 리소스를 만드는 기능

  - 리소스 : 데이터 + 링크

- 링크 찾아주는 기능

  - [Traverson](https://docs.spring.io/spring-hateoas/docs/current/api/org/springframework/hateoas/client/Traverson.html) : HAL 스타일의 링크는 연쇄적으로 링킹하여 자원을 찾을 수 있찌만 단계가 많아 번거롭기 때문에, 자동으로 링크따라 순회하며 최종 결과를 반환해주는 기능을 한다.

    - 원래는 nodejs와 브라우저에서 동작하는 [js라이브러리](https://github.com/traverson/traverson)로 이를 영감받아 spring에서 제작하여 지원

  - [LinkDiscoverers](https://docs.spring.io/spring-hateoas/docs/0.25.3.BUILD-SNAPSHOT/api/org/springframework/hateoas/LinkDiscoverers.html) : spring HATEOAS프레임워크에서 제공하는 클래스로 링크를 순회하며 적절한 링크가 있는지 찾기 위해 미디어 유형이 부합한지 등 체크하는 메서드들이 존재한다.

## 링크 구조

- href (주소)
- rel (관계)
  - self
  - profile
  - ...([IANA](https://www.iana.org/assignments/link-relations/link-relations.xhtml)에 미리 정의된 링크 관계가 존재,다양하며 개인적 정의 가능 => restful한 api는 표준이 존재하지 않기때문에 정의하여 사용가능)
    - udpate-event
    - query-events

## Links

```java
Link link = Link.of("http://localhost:8080/somothing");
Link link = new Link("http://localhost:8080/somothing");
assertThat(link.getHref()).isEqualTo("http://localhost:8080/somothing");
assertThat(link.getRel()).isEqualTo(IanaLinkRelations.SELF);
```

링크는 `Link`를 통해 생성이 가능하며 href와 rel등을 재설저이 가능하고 링크 관계(rel)은 기본적으로는 `self`로 자기자신을 참조한다.

## 메서드

- linkTo : 컨트롤러 `클래스`의 매핑 어노테이션을 검사하여 메서드에 매핑된 URI를 빌드하는 함수

  ```java
  @Controller
  @RequestMapping(value = "/api/events", produces = "application/hal+json; charset=UTF-8")
  public class EventController {

      @PostMapping
      public ResponseEntity createEvent(@RequestBody Event event){
          URI createdUri = linkTo(EventController.class).slash("{id}").toUri();
          event.setId(10);
          return ResponseEntity.created(createdUri).body(event);
      }
  }
  ```

  - methodOn : 클래스가 아닌 메서드에 매핑된 URI를 검사하여 빌드 (메서드를 클래스로 wrap)

  ```java
  @Controller
  public class EventController {

      @PostMapping(value = "/api/events", produces = "application/hal+json; charset=UTF-8")
      public ResponseEntity createEvent(@RequestBody Event event){
          URI createdUri = linkTo(methodOn(EventContoller.class).createEvent(null)).slash("{id}").toUri();
          event.setId(10);
          return ResponseEntity.created(createdUri).body(event);
      }
  }
  ```

  위와 같이 클래스의 매핑된 URI가 아닌 클래스 내의 메서드의 URI을 매핑하여 사용하기 위해 `methodOn()`안에 클래스를 주고 해당 클래스 내의 메서드의 어노테이션 정보로 `linkTo`를 수행한다.

- slash : `/`, `#`과 같은 slash와 뒤에 파라미터를 uri에 붙여주는 함수
