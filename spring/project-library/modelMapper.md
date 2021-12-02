# Model Mapper

쉽게 객체의 필드 값을 다른 클래스(객체)로 복사(mapping)을 해주는 라이브러리이다.

Entity를 통해 DB에서 받아온 값 중 요청에 넘겨주기 싫은 파라미터라던지, 요청의 파라미터 중 Entity로 넘겨주지 않을 파라미터를 제거하고 넘겨주기 위해 JackSon Json 어노테이션 내부에서 제공하는 메서드로 특정 프로퍼티를 제거하여 보내줄 수 있고, DTO를 따로 만들어 DTO객체로 convert 시킨 후에 넘겨 줄 수도 있다.

그런데 이때, DTO를 만들어 보내려고 한다면, 파라미터를 일일히 복사 해줘야 하는 노가다가 발생을 하게 되어 이를 map함수를 통해 손쉽게 맵핑 시킬 수 있게 해준다.

## 사용법

1. 의존성 추가

   maven이나 gradle에 의존성을 추가해준다.

1. @bean으로 ModelMapper을 만들어 설정한다

1. Controller에서 의존성을 주입받아 modelMapper를 사용한다.

```java
Event event = modelMapper.map(eventDto,Event.class);
```

## 단점

리플렉션이 발생해 직접 매핑하는 것보단 느려질 수 있다.

> 리플렉션
> 구체적인 클래스 타입을 알지 못해도, 그 클래스의 메소드/타입/변수들에 접근 할 수 있도록 해주는 자바 API
>
> 대표적으로 DI,Proxy,ModelMapper,Hibernate,JackSon에서 사용한다.
> 컴파일한 클래스 정보를 활용해 동적으로 프로그래밍이 가능하도록 지원하는 API
