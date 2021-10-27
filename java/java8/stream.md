`람다`를 활용할 수 있는 기술 중 하나로 일종의 `무한한 데이터의 흐름` 


## 메서드 종류
### 1. 생성
스트림 인스턴스 생성하는 메서드

- Arrays.stream(배열타입 변수) : 배열을 Stream 타입 객체로 생성
- Collection
    - Collection 타입 변수명.stream() : Collection타입의 객체(Collection, List, Set)를 Stream 타입 객체로 생성
- Stream.empty() : 비어있는 Stream() 객체
- Stream.builder().add()...build() 
- Stream.generate(() -> {}).limit() : 람다를 이용하여 생성하는 방식으로 람다의 return값이 들어있는 Stream을 생성한다. 이때 무한히 생성하기 때문에 limit메서드로 제한을 주어야 한다.
- Stream.iterate(startValue, () -> {}).limit() : 초기값부터 해당 값을 input으로 하는 람다를 반복하여 나온 값으로 Stream을 생성
- IntStream.reange(1,5) / IntStream.rangeClosed(1,5).boxed();
- Random().doubles() : DoubleStream을 반환값
- "String".chars() : IntStream을 반환값
- list.parallelStream() : 병렬 스트림
- Arrays.stream(arr).paraller();
- intStream.sequential() : 다시 시퀀셜 모드

### 2. 가공 
필터링, 맵핑과 같이 어떠한 결과를 만들어가는 중간 작업들의 메서드 ( Intermediate operations )

- filtering : .filter(Predicate)
- distinct : distinct()
- mapping 
    - .map(Function<T,R>)
    - .flatMap(Function<T, Stream>) : 중첩구조를 제거하고 단일 컬렉션으로 만듬 (flattening)
- sorting : .sorted(Comparator)
- iterating(순환) : .peek(Consumer) : 중간에 결과 확인할때 사용할 수 있다.

### 3. 종료
최종적으로 결과를 만들고 반환함으로써 chaining을 끝내는 메서드 ( terminal operations )

- calculating 
    - count()
    - sum()
    - min()
    - max()
    - avarage()
- reduction
    - reduce() : 계산 후 결과 반환
        - reduce(BinaryOperator) : 각 요소를 처리하는 로직
        - reduce(T,BinaryOperator) : 계산을 위한 초기값 T를 가지고 각 요소를 처리
        - reduce()
- collecting()
- matching
    - anyMatch
    - allMAtch
    - noneMatch
- iterating : forEach()