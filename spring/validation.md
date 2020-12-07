# 도메인 입력값 검증

## @Valid와 BindingResult (Errors)이용한 자동 검증

BindingResult는 항상 @Valid 바로 다음 인자로 사용해야 한다. (spring MVC)

Bean Validator (@NotNull, @NotEmpty, @Min, @Max, @Null, @Size(min="", max=""), @UniqueElements, @Range(min=i,max=j), @Digit, @Email, @SafeHtml, @CreditCardNumber, @URL, @Pattern(regexp=""), @AssertTrue/False) 을 사용해서 입력값 바인딩 할때 에러를 확인 할 수있다.

Controller에 `@Valid` 와 Entity의 파라미터에 `@NotEmpty`, `@NotNull`과 같은 어노테이션 사용하면 error발생 시 Erorrs 객체에 값이 담긴다.

spring boot 2.3버전 이상부터는 아래의 dependency를 추가해야 사용이 가능하다

```xml
<dependency>
   <groupId>org.springframework.boot</groupId>
   <artifactId>spring-boot-starter-validation</artifactId>
</dependency>
```

### @NotNull, @NotEmpty, @NotBlank 차이

- @NotNull : Null을 허용 x

- @NotEmpty : Null과 ""(empty)를 허용 x
- @NotBlank : Null과 ""(empty)와 " "(공백)을 허용 x

<br>
<Br>

## 도메인 Validator만들기 (Custome 검증)

단순한 값 검증이 아닌 복잡한 로직으로 값 검증을 할때 사용할 수 있는 방법 중 하나

```java
@Component
public class EventValidator {

    public void validate(EventDto eventDto, Errors errors){
        if(eventDto.getBasePrice() > eventDto.getMaxPrice() && eventDto.getMaxPrice() > 0){
            errors.rejectValue("basePrice","wrongValue","BasePrice is wrong");
            errors.rejectValue("maxPrice","wrongValue","maxPrice is wrong");
        }
    }
}
```

위와 같이 클래스를 하나 생성하고 `@Component`로 bean으로 등록한 후 controller에 주입해서 사용

```java
@Controller
@RequestMapping(value = "/api/events", produces = "application/hal+json; charset=UTF-8")
public class EventController {

    private final EventRepository eventRepository;
    private final EventValidator eventValidater;

    public EventController(EventRepository eventRepository,ModelMapper modelMapper,EventValidator eventValidater) {
        this.eventRepository = eventRepository;
        this.eventValidater = eventValidater;
    }
}
```

<br>
<br>

## Error

> Errors는 다른 객체랄 달리 json으로 바꿀수 없다.
>
> 자바 빈 스펙을 준수한 객체는 기본 beanSerializer을 사용해서 변환이 가능했다. (model mapper내부에 있는)
>
> 하지만 Errors는 자바 빈 스펙을 준수한 객체가 아니라 json으로 변환이 불가능하므로 Error Serializer를 생성하여 사용
