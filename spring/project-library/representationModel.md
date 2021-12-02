# Representation Model

ResourceSupport의 바뀐 클래스로 객체에 링크정보를 추가해주기 위해 지원하는 클래스

## 사용법

```java
public class EventResource extends RepresentationModel<EventResource> {
    private Event event;

    public EventResource(Event event) {
        this.event = event;
    }

    public Event getEvent() {
        return event;
    }
}
```

와 같이 `RepresentaionModel`클래스를 상속받는 클래스를 하나 만들고 controller에서 새로만든 클래스에 링크를 추가하여 사용

```java
//controller안의 어느 메서드 안의 코드

EventResource eventResource = new EventResource(event);
eventResource.add(linkTo(EventController.class).withRel("query-events"));

```

이렇게 만 사용하게 된다면 return할때 EventResource를 return하고 이를 `Object Mapper`가 `Serialization`을 할때 `Bean Serialize`를 쓰기 때문에 기본적으로 객체내의 필드이름을 사용하는데 그 필드(Event)는 `compose 객체`이기 때문에 여러필드들읗 하나의 객체로 묶고 링크를 따로 분리하여 response한다.

```json
{
  "event": {
    "id": 1,
    "name": "Spring",
    "description": "rest api practice",
    "beginEnrollmentDateTime": "2020-10-28T17:24:00",
    "closeEnrollmentDateTime": "2020-11-28T17:33:00",
    "beginEventDateTime": "2020-11-20T17:53:00",
    "endEventDateTime": "2020-12-20T17:01:00",
    "location": "강남역",
    "basePrice": 100,
    "maxPrice": 200,
    "limitOfEnrollment": 100,
    "offline": true,
    "free": false,
    "eventStatus": null
  },
  "_links": {
    "query-events": {
      "href": "http://localhost/api/events"
    },
    "self": {
      "href": "http://localhost/api/events/1"
    },
    "update-event": {
      "href": "http://localhost/api/events/1"
    }
  }
}
```

## 해결방법

- 필드(도메인)에 `@JsonUnwrapped`어노테이션을 붙여 준다.

```java
public class EventResource extends RepresentationModel<EventResource> {

    @JsonUnwrapped
    private Event event;

    public EventResource(Event event) {
        this.event = event;
        add(linkTo(EventController.class).slash(event.getId()).withSelfRel()); //self link
    }

    public Event getEvent() {
        return event;
    }
}
```

- RepresentationModel<T>가 아닌 EntityModel<T>를 상속

  내부적으로 RepresentationModel을 상속 받고 있으며 `@JsonUnwrapped` 또한 선언이 되어있다.

```java
public class EventResource extends EntityModel<Event> {

    public EventResource(Event event, Link... links){
        super(event,links);
        add(linkTo(EventController.class).slash(event.getId()).withSelfRel()); //self link
    }
}
```

그러면 아래처럼 한 객체 안에 표시가 되는 것을 볼 수 있다.

```json
{
  "id": 1,
  "name": "Spring",
  "description": "rest api practice",
  "beginEnrollmentDateTime": "2020-10-28T17:24:00",
  "closeEnrollmentDateTime": "2020-11-28T17:33:00",
  "beginEventDateTime": "2020-11-20T17:53:00",
  "endEventDateTime": "2020-12-20T17:01:00",
  "location": "강남역",
  "basePrice": 100,
  "maxPrice": 200,
  "limitOfEnrollment": 100,
  "offline": true,
  "free": false,
  "eventStatus": null,
  "_links": {
    "query-events": {
      "href": "http://localhost/api/events"
    },
    "self": {
      "href": "http://localhost/api/events/1"
    },
    "update-event": {
      "href": "http://localhost/api/events/1"
    }
  }
}
```
