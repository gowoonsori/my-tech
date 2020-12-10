# JunitParams

https://www.petrikainulainen.net/programming/testing/junit-5-tutorial-writing-parameterized-tests/

테스트에서 중복 코드를 제거하는 방법으로

```java
   @Test
    public void testOffline(){
        //Given
        Event event = Event.builder()
                .location("강남역")
                .build();
        //When
        event.update();
        //Then
        assertThat(event.isOffline()).isTrue();

        //Given
        event = Event.builder()
                .build();
        //When
        event.update();
        //Then
        assertThat(event.isOffline()).isFalse();
    }
}
```

와 같이 매개변수만 바뀌는 상황에서 코드 중복을 피하기 위해 사용가능하다.

원래 JUnit메서드는 파라미터를 갖지 못하는데 파라미터를 갖을수 있게 해준다.

## dependency 추가

```xml
<dependency>
  <groupId>pl.pragmatists</groupId>
  <artifactId>JUnitParams</artifactId>
  <version>1.1.1</version>
  <scope>test</scope>
</dependency>
```

## 사용법

Test할 class에 `@RunWith(JUnitParamsRunner.class)`을 추가후 테스트할 메서드에 `@CsvSource({})`을 이용해 파라미터 이용

```java
@RunWith(JunitParamsRunner.class)
class EventTest{
    @ParameterizedTest(name="{index}번째 실행 : basePrice={0},maxPrice={1},isFree={2}")
    @CsvSource({
            "0,0, true",
            "100, 0 ,false",
            "0,100,false"
    })
    public void testFree(int basePrice, int maxPrice, boolean isFree){
        //Given
        Event event = Event.builder()
                .basePrice(basePrice)
                .maxPrice(maxPrice)
                .build();
        //When
        event.update();
        //Then
        assertThat(event.isFree()).isEqualTo(isFree);
    }
}
```

`@CsvSource`어노테이션 파라미터 안의 배열수 만큼 테스트가 진행되고 `@Test`어노테이션이 아닌 `@ParameterizedTest` 어노테이션을 사용하고 안의 파라미터로 name을 주어 테스트 이름을 지정할 수 있다.

### 테스트 파라미터를 문자열로 입력해 Type Safe하지 않아 걱정될때

객체 배열을 return하는 메서드를 통해 파라미터로 넘겨주어 사용

```java
    //static이 있어야 동작한다.
    private static Object[] parametersForTestOffline(){
        return new Object[]{
                new Object[] {"강남역",true},
                new Object[] {"",false},
                new Object[] {"  ",false},
                new Object[] {null,false}
        };
    }

   //Type Safe하게 Method이용해서 파리미터 전달
    @ParameterizedTest(name="{index}번째 실행 : location={0}, isOffline ={1}")
    @MethodSource("parametersForTestOffline")
    public void testOffline(String location,boolean isOffline){
        //Given
        Event event = Event.builder()
                .location(location)
                .build();
        //When
        event.update();
        //Then
        assertThat(event.isOffline()).isEqualTo(isOffline);
    }
```

이때 `@MethodSource`어노테이션을 이용하여 메서드를 맵핑시켜주면된다.

외국에선 객체 배열보다는 Stream을 주로 이용

```java
 private static Stream<Arguments> TestOffline(){
        return Stream.of(
                Arguments.of("강남역",true),
                Arguments.of("",false),
                Arguments.of("  ",false),
                Arguments.of(null,false)
        );
    }
```
