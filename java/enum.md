## Enum

기본적으로 c나 c++의 enum과 같은 기능을 수행하는 `클래스`로 `JDK 1.5`이후에 생긴 클래스이다.

c언어의 `C99` 이전에는 `boolean`타입을 제공하지 않았기 때문에 다음과 같이 사용하고는 했었다.

```c
typedef enum _boolean {
    FALSE,
    TRUE
} boolean;

#define FALSE 0
#define TRUE 1
```

### Java에서의 Enum 특징

Enum 비교시에 값이 아닌 `타입까지도 체크`가 가능하고 Enum의 상수값이 재정의 되어도 `다시 컴파일하지 않는다.`

<br><br>

## enum 정의하는 방법

```java
enum Money { DOLLAR, WON, POUND, EURO, YEN, YUAN }
```

enum 키워드를 이용하여 정의를 할 수 있고 정의를 어디에 하느냐에 따라 분류를 해보자면 3가지정도로 분류할 수 있다.

### 1. 별도의 Java 파일로 정의

```java
[Money.java]

public enum Money {
    DOLLAR, WON, POUND, EURO, YEN, YUAN
}

[example.java]

public class example {
    public static void main(String[] args) {
        Money dollar = Money.DOLLAR;
        System.out.println(dollar);
    }
}
```

![enum](/java/image/enum.PNG)

### 2. 클래스 안에 정의

```java
public class example {
    public enum Money {
        DOLLAR, WON, POUND, EURO, YEN, YUAN
    }
    public static void main(String[] args) {
        Money dollar = Money.DOLLAR;
        System.out.println(dollar);
    }
}
```

![in](/java/image/in.PNG)

### 3. 클래스 밖에 정의

```java
enum Money {DOLLAR, WON, POUND, EURO, YEN, YUAN}

public class example {
    public static void main(String[] args) {
        Money dollar = Money.DOLLAR;
        System.out.println(dollar);
    }
}
```

![out](/java/image/out.PNG)

정의 위치에 따라 enum객체가 생성된 위치가 다른 것을 볼 수 있다.

### enum 사용

`Money.DOLLAR`와 같이 `Enum이름.상수명`으로 사용을 할 수 있으며 `Money money = Money.DOLLAR`와 같이 변수에 할당 해줄 수도 있다.

<br>

```c
#include <stdio.h>

enum Money { DOLLAR, WON, POUND, EURO, YEN, YUAN }

int main() {
    enum Money dollar = DOLLAR;
    enum Money won = WON;

    if (dollar == 0) {
        printf("출력1");        //출력
    }
    if (won > dollar) {
        printf("출력2");        //출력
    }
    return 0;
}
```

C의 enum은 각 상수가 int형으로 저장되어 산술연산도 가능하고 아래와 같이 상수리터럴과 비교해도 같게 나오는 문제도 생긴다.

```java
 public class example {
        private final static int DOLLAR = 0;
        private final static int WON = 1;
        private final static int POUND = 2;
        private final static int EURO = 3;
        private final static int YEN = 4;

        public static void main(String[] args) {
            System.out.println(DOLLAR == 0);
        }
    }
```

Enum이 없을 때 Java에서도 이와 비슷하게 class에 `private final static int`를 이용해서 상수값을 정의 할 수 있었다.

하지만 이 방법은 가독성에도 좋지 않고 변수명이 겹칠 수 있거나 상수리터럴과 비교가 된다는 문제점이 있다.

<BR>

```java
public class example {

    public static void main(String[] args) {
        Money dollar = Money.DOLLAR;
        Money won = Money.WON;

        System.out.println(dollar > won);   //error
        System.out.println(dollar == 0);    //error
    }
}
```

Java의 Enum은 각 상수가 상수 그 자체로써 작동을 하고 자료형이 다르기 때문에 아래와 같이 비교하려고 하면 compile error가 뜬다.

### 상수에 다른 값 추가

```java
enum Money {
    DOLLAR("달러"),
    WON("원"),
    POUND("파운드"),
    EURO("유로"),
    YEN("엔"),
    YUAN("위안");

    private String hanguelName;

    private Money(){}
    private Money(String hanguelName){this.hanguelName = hanguelName;}

    public String getHanguelName(){
        return hanguelName;
    }
}

public class example {

    public static void main(String[] args) {
        Money dollar = Money.DOLLAR;
        Money won = Money.WON;

        System.out.println(dollar.getHanguelName());
        System.out.println(won.getHanguelName());

    }
}
```

클래스의 `생성자`와 같은 방법으로 값을 할당 해줄 수 있으며, getter를 정의해서 값을 참조 할 수도 있다.

**이때 생성자는 PRIVATE 속성으로 생성해주어야 한다.**

enum타입은 고정된 상수들의 집합이므로 `컴파일 타임`에 모든 값을 알고 있어야하기 때문에 다른 클래스에서 동적으로 값을 정해줄 수 없기 때문에 생성자를 private로 설정해야 하고 `final`과 다름이 없어진다.

<br><br>

## enum이 제공하는 메소드

### values()

Enum의 모든 상수를 배열로 만들어 반환해주는 함수

```java
 public class example {
    public static void main(String[] args) {
        for(Money money : Money.values()){
            System.out.println(money);      //차례대로 출력
        }
        System.out.println(Money.values()[1]); //WON 출력
        System.out.println(Money.values() instanceof Object); //true
    }
 }
```

`Money[]`형태의 타입으로 반환이 된다.

### valuesOf()

매개변수로 `String`형이 오며 이 매개변수와 동일한 이름의 상수를 찾아 상수를 반환 하고 없다면 `IllegalArgumentException` 예외를 발생시킨다.

```java
 public class example {
    public static void main(String[] args) {
        System.out.println(Money.valueOf("WON"));   //WON 출력
        System.out.println(Money.valueOf("Rupee")); //IllegalArgumentException error
    }
 }

```

### ordianal()

enum 상수가 0부터 시작하여 정의된 순서를 반환(int)하는 함수

```java
public class example {
    public static void main(String[] args) {
        Money dollar = Money.DOLLAR;

        System.out.println(dollar.ordinal()); //0
    }
 }
```

<br><br>

## java.lang.Enum

enum 클래는 기본적으로 `java.lang.Enum`라는 부모 클래스를 상속 받고 있고 이는 `Object`를 상속받고 `Comparable`과 `Serializable`를 implements하고 있다.

```java
protected Enum(String name, int ordinal) {
        this.name = name;
        this.ordinal = ordinal;
}
```

`protected`형으로 생성자를 하나 가지고 있는데 이는 개발자가 호출할 수 없고 컴파일러에 의해 `enum 키워드`에 반응하여 생성하기 위함이다.

```java
public String toString() {
    return name;
}
```

이 클래스 내에 있는 `public` 메소드 중 `Override`해서 사용할만한 메서드로 기본은 `상수 이름`을 반환하지만, `enum`을 생성시 `추가 값`을 지정하여 생성했다면 이를 `Override`해줄 수 있다.

### 컴파일 시의 객체 생성

```java
final class Money extends Enum<Money> {
	private Money(String name, int ordinal) {
		super(name, ordinal);
	}

	public static final Status DOLLAR = new Status("DOLLAR", 0);
	public static final Status WON = new Status("WON", 1);
	public static final Status POUND = new Status("POUND", 2);
    public static final Status EURO = new Status("EURO", 3);
    public static final Status YEN = new Status("YEN", 4);


	private static final Status ENUM$VALUES[] = { DOLLAR, WON, POUND, EURO, YEN };
}
```

enum 키워드를 사용하여 열거형을 생성하면 컴파일 시에 위와 같이 정의가 된다.

<br><br>

## EnumSet

Set 인터페이스를 구현

EnumSet은 `abstract`키워드가 앞에 붙어 객체 생성이 불가능하고 `of()`와 같은 추상 팩토리 메서드에서 사용하는 `noneOf(class<E> elementType)` 메서드가 존재하여 이를 통해 `구현 객체`를 받을 수 있다.

```java
public static <E extends Enum<E>> EnumSet<E> noneOf(Class<E> elementType) {
        Enum<?>[] universe = getUniverse(elementType);
        if (universe == null)
            throw new ClassCastException(elementType + " not an enum");

        if (universe.length <= 64)
            return new RegularEnumSet<>(elementType, universe);
        else
            return new JumboEnumSet<>(elementType, universe);
    }
```

`noneOf() 메서드`를 보면 알겠지만 `EnumSet` 객체를 반환하는 것이 아닌 이를 상속받은 `클래스들`을 반환하고 있다.

이 둘 클래스 모두 `private`속성이므로 직접 사용할 수 없다.

- 사용할 크기에 맞게 적합한 구현 객체를 골라 준다.

- Enum의 상수들을 하나하나 Set에 담는 행위를 피할 수 있다.

- EnumSet 내부 표현은 `비트 벡터`로 표현된다. (상수 개수가 64개 이하라면 `long`변수 하나로 표현한다.)
- Enum 상수가 선언된 순서, 즉 ordinal() 메서드의 반환된 순서로 순회한다.
- EnumSet iterator는 약한 일관성을 유지하여 `ConcurrentModificationException`을 발생시키지 않는다.
- null 요소는 삽입이 되지 않는다.
- `동기화`가 되지 않는다.

### 메서드

- EnumSet.allOf(Class<E> elementType) : 매개변수의 타입의 모든 요소를 포함한 `EnumSet`을 반환
- EnumSet.noneOf(Class<E> elementType) : 매개변수의 타입의 비어있는 `EnumSet`반환
- EnumSet.of(E e1, E e2 ...) : 지정한 매개변수를 포함한 `EnumSet`을 반환

- 그 외 `java.util.AbstractSet`, `java.util.AbstractCollection`, `java.lang.Object`, `java.util.Set`으로 부터 메서드들을 상속받고 있다.
  - 중복 검사를 위한 `equals()`,`hashCode()` ,`add()`,`remove()`,`size()`, `toArray() => Object[] 반환`, `iterator()`등 사용 가능

<br><br>

## EnumMap

Map 인터페이스를 구현

- Enum을 Key로 이용하는 Map이다.

- Enum 상수로 null을 갖을 수 없기 때문에 null을 key로 갖지 못한다.
- Enum은 정해진 상수를 사용하고 단일 객체이기 때문에 해싱하지 않고 이미 순서가 정해져있어 성능이 좋다.
- key와 value가 배열로 구성되어있다.
- EnumMap의 key는 `ordianl`로 관리 되기 때문에 iterator는 약한 일관성을 유지하여 `ConcurrentModificationException`을 발생시키지 않는다.
- `동기화`가 되지 않는다.

### 메서드

- 생성자 : `new`키워드를 이용해 생성할 수 있고 일반 Map들과 다르게 `enum 타입`을 파라미터로 넘겨주어야 한다.

  - `Map<Money,Integer> map = new EnumMap<>(Money.class);`

- clear() : 모든 요소 삭제
- get(Object key) : key에 해당하는 value 리턴
- put(K key, V value) : map에 데이터 입력
- remove(Object key) : 해당하는 key가 있다면 삭제
- equals(Object object) : 기준 Map과 같은지 비교
- containsKey(Object key) / containsValue(Object value) : 해당하는 key와 value 가 있다면 true 반환
- size() : Map의 요소 개수 반환
- keySet() : Map에 있는 모든 key들의 Set view를 반환한다. (모든 key들을 보여준다.)
- values() : Map에 있는 value들의 Collection view를 반환한다. (모든 값들을 보여준다.)

<br><br><br>

---

### Reference

https://www.nextree.co.kr/p11686/

http://cris.joongbu.ac.kr/course/java/api/java/lang/Enum.html

https://javarevisited.blogspot.com/2014/03/how-to-use-enumset-in-java-with-example.html#axzz6kSbFjAwM
