# Spring HATEOAS

Hypermedia As The Engine Of Application State의 약자로 하이퍼 링크를 통해 상태 이동이 일어나야 한다는 조건을 만족하기 위해 제공하는 라이브러리

response body에 링크를 제공하여 client가 참고 할 수 있도록 하는 것

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

- slash : `/`, `#`과 같은 slash와 뒤에 파라미터를 uri에 붙여주는 함수
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

  위와 같이 클래스의 매핑된 URI가 아닌 클래스 내의 메서드의 URI을 매핑하여 사용하기 위해 methodOn()안에 클래스를 주고 해당 클래스 내의 메서드의 어노테이션 정보로 linkTo를 수행한다.
