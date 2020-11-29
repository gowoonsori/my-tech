# Controller

데이터를 전달한 Mapping 정보가 저장되는 클래스. ( 로직처리를 담당 )

어떻게 처리 할지 알려주는 역할로 일종의 Model과 View의 Proxy역할

jsp나 템플릿을 통해 결과물을 특정 경로로 연결 시켜주거나 api와 같이 특정 데이터를 전달해주는 역할

<br><br>

# 어노테이션

## @Controller

해당 클래스를 controller로 인식하게 해주는 어노테이션

<br>

## @RequestMapping

클라이언트로부터 요청(request)이 들어왔을때 어떤 요청(uri)인지 구분하여 처리하기 위한 어노테이션

주로 클래스 레벨에서 사용

### 속성

- name : Request를 구분하기 위한 기본 값으로 어떻게 보면 value와 같아 보일 수 있으나, name은 큰틀로 선언하고 value로 세부 경로를 지정

  ```java
  @Controller
  @RequestMapping("store")
  public class ItemController {

  @ResponseBody
  @RequestMapping(value = "/item")
      public String getItemName(){

      }
  }
  ```

- value / path : `uri path`을 구분하여 어떤 함수를 실행할지 Mapping시키는 값

  ```java
  @RequestMapping(value = "/api/item");
  ```

- method : `RequestMethod.GET`, `RequestMethod.POST`와 같이 요청 메서드를 구분

- produces : Response의 contentType을 지정할 수 있다.

  ```java
  @RequestMapping(value = "/api/item",produces = "application/json; charset=UTF-8");
  @RequestMapping(value = "/api/item",produces = MediaTypes.HAL_JSON_VALUE);

  ```

- params : Request의 요청 uri 파라미터를 분석하여 변수로 사용

  - @PathVariable : `uri path`로 들어오는 값을 구분하여 변수로 사용하기 위함

          ```java
          @Controller
          @RequestMapping("store")
          public class ItemController {

              @ResponseBody
              @RequestMapping(value = "/item/{name}", method = RequestMethod.GET)
              public String getItemName(
                  @PathVariable("name") String name){
                      return name;
                  }
              }
          ```
          위와 같이 {name}을 변수로 사용하기 위한 어노테이션이지만, `@RequestMapping(value="/{id}")`와 같이 특정 경로 없이 사용하지 말자.

    - @RequestParam : `/store/item?name=pencil`과 같이 들어오는 uri의 `query string`을 이용하기 위한 어노테이션

      ```java
        @Controller
        @RequestMapping("store")
        public class ItemController {

            @ResponseBody
            @RequestMapping(value = "/item", method = RequestMethod.GET)
            public String getItemName(
                @RequestParam("name") String name){
                    return name;
                }
            }
      ```

- consumes : request body에 저장할 타입을 제한

  ```java
      @RequestMapping(value = "/api/item",consumes = "application/json");
  ```

<br>

## GetMapping, PostMapping, DeleteMapping, PutMapping ..

@RequestMapping에 특정 method 고정적으로 선언되어 있는 어노테이션이다.

메서드에 사용되었다면 특졍 경로가 없어도 클래스의 RequestMapping을 주입받는다.

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

<br>

## @ResponseBody, @RequestBody

비동기를 처리 하는 경우 사용 (View를 통해 출력이 되지않고 http body에 데이터를 직접 써서 보내는 것)

HTTP BODY에 직접반환.<br> 템플릿엔진이 아닌 바로 데이터를 전송하라는 어노테이션. viewResolver가 아닌 HttpMessageConverter가 동작하며, String이면 StringConverter가 객체이면 JsonConverter가 동작하여 default는 객체를 json형식으로만들어서 응답.

클라이언트의 HTTP Accept헤더와 서버의 컨트롤러 반환 타입 정보 둘을 조합하여 반환방식 자동으로 결정

메서드의 반환 값이 HTTP Response/Request body에 직접 직렬화 되었음을 Spring에 알린다.

HttpMessageConverter가 존재하여 특정 형태(json,xml..)로 들어온 요청 값을 자바 객체로 변환하고 응답을 특정 형태로 보내기 위해 사용된다.

### HttpMessageConverter

Spring에서 사용하기 위해 기본적으로 @EnableWebMvc를 사용해서 WebMvcConfigurer을 구현해야 한다.

- ByteArrayHttpMessageConverter – 바이트 배열 변환

- StringHttpMessageConverter – 문자열 변환
- ResourceHttpMessageConverter – 모든 유형의 옥텟 스트림에 대해 org.springframework.- core.io.Resource 를 변환 합니다.
- SourceHttpMessageConverter – javax.xml.transform.Source를 변환합니다.
- FormHttpMessageConverter – 양식 데이터를 MultiValueMap <String, String> 로 /에서 변환합니다 .
- Jaxb2RootElementHttpMessageConverter – Java 객체를 XML로 /로부터 변환합니다 (JAXB2가 클래스 경로에있는 경우에만 추가됨).
- MappingJackson2HttpMessageConverter – JSON 변환 (Jackson2가 클래스 경로에있는 경우에만 추가됨)
- MappingJacksonHttpMessageConverter – JSON 변환 (Jackson이 클래스 경로에있는 경우에만 추가됨)
- AtomFeedHttpMessageConverter – Atom 피드를 변환합니다 (Rome이 클래스 경로에있는 경우에만 추가됨).
- RssChannelHttpMessageConverter – RSS 피드를 변환합니다 (Rome이 클래스 경로에있는 경우에만 추가됨).

스프링 부트는 `Jackson2ObjectMapperBuilder`를 `JacksonAutoConfiguration`클래스에서 자동으로 설정하기 때문에 별다른 설정 없이 `ObjectMapper`를 이용해 JSON형태를 변환할 수있다.

> spring-boot-start-web에 jackson-databind가 자동으로 의존성이 잡힌것을 볼 수 있다.

<br>

## RestContoller

@ResponseBody를 모든 메소드에 적용한 것과 동일한 효과

<br>
<br>

# 클래스

## ResponseEntity

Spring framwork는 HttpEntity라는 클래스를 제공하는데 이는 response/request의 HttpHeader와 HttpBody를 포함하는 클래스이다.

HttpEntity를 상속받아 Response에 해당하는 부분을 담당하는 클래스이다.

status, header, body 부분을 수정/삽입하여 응답헤더를 보낼 수 있게 해준다.

<br>
<br>

---

## Reference

https://www.baeldung.com/spring-httpmessageconverter-rest
