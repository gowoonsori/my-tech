# 람다식
`함수형 언어`의 특징에서 나온 것으로 식별자 없이 사용가능한 함수로 익명함수의 형태를 사용한다.
>익명함수? 함수의 이름이 없는 함수로 익명함수들은 일급객체이다.

>일급객체? 변수나 데이터 구조안에 담을 수 있으며 파라미터로 전달하거나 반환값으로 사용할 수 있는 객체

## 메서드와 함수의 차이
어떤 행위를 수행한다는 점에서는 같은 의미이지만 메서드는 특정 클래스에 속해서 해당 클래스의 행위를 표현하는 함수

<br><br>

## 형태
`->`를 이용해서 변수를 body(식)에 전달하는 형태
```
()-> body
() -> {body}
변수 -> body
변수 -> body
(변수) -> { body }
(변수) -> { body }
(자료형 변수) -> body 
(자료형 변수) -> { body }
```
### 1. 인자
- 인자가 없을때 : 무조건 `()`를 사용
- 인자가 한개 : `(변수)` , `변수` 두개 다 사용 가능
- 인자가 여러개 : `(변수1, 변수2)` 형태로 반드시 괄호 사용

인자의 자료형은 컴파일러가 컴파일타임에 추론하여 붙여주기 때문에 `생략`이 가능하고 명시해줄 수 도 있다.

### 2. 바디
- 한 줄 인 경우 : `{}`를 생략가능하며 `return` 키워드도 생략가능하다.
- 여러줄 인 경우 : `{}`를 이용하여 body를 묶어주어야 하며 return도 생략이 불가능하다.


<br><br>



## 특징
1. 간결한 코드
    ```java
    //before
    int max(int a, int b){
        return a > b ? a : b;
    }

    //after
    (int a, int b) -> { return a > b ? a : b; }
    ```

2. 멀티스레드환경에서 용이

    람다식은 순수함수로써 같은 입력이라면 항상 같은 출력을 보장하여 Side Effect가 없으며 외부 상태를 변경하지 않기 때문에 병렬환경에서 용이하다.

3. 지연 연산이 가능하다.
    Streaming/Chaning이라고 부르는 방식으로 변수값 각각 하나에 대하여 체이닝된 함수를 순서대로 실행한다.

    첫 함수에 모든 변수가 실행되고 다음 함수가 실행되는 방식이 아니다. 이런 지연연산을 통해 cpu자원을 아낄 수 있다. 

    ```java
    //홀수인지 체크
    public boolean isOdd(int n){
        System.out.println("isOdd : " + n);
        return n % 2 == 1;
    }

    //곱하기 2
    public int doubleIt(int n){
        System.out.println("doubleIt : " + n);
        return n * 2;
    }

    //6보다 큰지 체크
    public boolean isGreaterThan6(int n){
        System.out.println("is greater than 6 : " + n);
        return n > 6;
    }
    ```
    위와 같은 메서드가 존재할 때 주어진 배열에서 `홀수이면서 곱하기 2했을때 6보다 큰 가장 첫번째 숫자`를 찾는 로직을 구현한다고 하자.

    ```java
    int[] arr = new int[]{1, 2, 3, 4, 5, 6, 7, 8, 9};


    List<Integer> list1 = new ArrayList<>();
    for(int n : arr){
        if(isOdd(n))list1.add(n);
    }

    List<Integer> list2 = new ArrayList<>();
    for(int n : list1){
        list2.add(doubleIt(n));
    }

    for(int n : list2){
        if(isGreaterThan6(n)) {
            System.out.println(list3.get(0));
            break;
        }
    }

    //print
    isOdd : 1
    isOdd : 2
    isOdd : 3
    isOdd : 4
    isOdd : 5
    isOdd : 6
    isOdd : 7
    isOdd : 8
    isOdd : 9
    doubleIt : 1
    doubleIt : 3
    doubleIt : 5
    doubleIt : 7
    doubleIt : 9
    is greater than 6 : 2
    is greater than 6 : 6
    is greater than 6 : 10
    10
    ```
    만일 위와같이 코드를 작성한다면 매 함수마다 특정 변수를 모두 loop돌게 된다.

    ```java
    System.out.println(Arrays.stream(arr)
                .filter(Lambda::isOdd)
                .map(Lambda::doubleIt)
                .filter(Lambda::isGreaterThan6)
                .findFirst().getAsInt());
    //print
    isOdd : 1
    doubleIt : 1
    is greater than 6 : 2
    sOdd : 2
    sOdd : 3
    doublet : 3
    is greater than 6 : 6
    isOdd : 4
    isOdd : 5
    doubleIt : 5
    is greater than 6 : 10
    10
    ```
    하지만 위처럼 람다식을 이용하게 되면 지연연산이 수행되면서 체이닝을 끝내는 함수인 findFirst를 만나 더이상 loop을 돌지 않고 끝내는 걸 볼 수 있다.

    ```java
    for(int n : arr){
        if(isOdd(n) && isGreaterThan6(doubleIt(n))){
            System.out.println("(End) N is " + n);
            break;
        }
    }
    ```
    물론 위와 같이 코드를 작성할 수도 있지만 함수의 조건이 많아질 수록 코드의 가독성은 람다보다 떨어지게 될 것이다.

4. loan pattern (빌려쓰기 패턴) 적용 가능

    >빌려쓰기 패턴? 람다를 입력으로 받는 메서드가 대신해서 자원을 열고 닫는 패턴

    ```java
    class Resource{
       public Resource(){
           System.out.println("Create resource");
       }

       public void useResource(){
           System.out.println("Use resource");
       }

       public void dispose(){
           System.out.println("Disposing resource");
       }
   }

   public static void main(String[] args) {
        Resource resource = new Resource();
        resource.useResource(); //자원 사용
        resource.dispose();
    }
    ```
    일반적으로 객체를 생성하여 사용하게 되면 그 자원의 관리를 자원을 빌려쓴쪽(사용하는쪽)이 하게되고 만일 Run 타임시에 에러가 발생하여 무조건 자원을 반환해야한다면 자원을 사용하는 코드블럭마다 try~finally로 묶어 dispose해주어야 되기 때문에 코드의 반복이 발생하게 된다.

    이를 아래처럼 람다를 이용하면 자원의 관리를 빌려쓰는쪽이 아닌 빌려주는 쪽(자원의 주체)가 관리할 수 있게 되고 코드의 반복을 피할 수 있다.
    ```java
    public class Resource {
        private Resource() {
            System.out.println("Create resource");
        }

        public void useResource() {
            System.out.println("Use resource");
        }

        public void dispose() {
            System.out.println("Disposing resource");
        }

         public static void withResource(Consumer<Resource> consumer) {
            Resource resource = new Resource();
            try {
                consumer.accept(resource);
            } finally {
                resource.dispose();
            }   
        }
    }

    public class Lambda {
        public static void main(String[] args) {
            Resource.withResource(Resource::useResource);
        }
    }
    ```

<br><br>

## Variable Capture
- 로컬 변수 캡쳐

    람다식에서 식 외부의 변수를 참조할때 `final`이거나 `effective final` 인 경우에만 참조가 가능하다.
    >effective final? 자바8부터 지원하는 기능으로 `사실상` final 변수라는 의미. final 키워드를 사용하지 않아도 해당 변수가 선언이 되고 변경이 되지 않았다면 컴파일러가 final 취급하는 변수

    지역변수는 JVM의 stack에 저장이 되며 스레드끼리 공유가 되지 않고 인스턴스 변수는 heap에 저장이 되어 스레드끼리 공유가 가능한데 특정 영역(클래스나 메서드)안에 존재하는 람다식에서 외부의 값을 참조함에 있어 값을 그대로 참조하는 것이 아니라 값을 복사해 복사된 값을 사용하게 되는데(메서드 실행이 끝나 stack영역의 지역변수가 사라지면 해당 람다는 참조할 값이 사라진다.) 이 값이 변경이 가능하다면 동시성의 문제가 발생할 수 있기 때문에 final의 성격을 가진 변수만 가능하다.

- 람다를 감싸고 있는 scope과 같은 level의 scope

    람다는 로컬/익명 클래스와 달리 다른 scope을 만들지 않는다.

    ```java
    public static void main(String[] args) {
       int number = 1;

       class Local{
           void print(int number){
               number++;
               System.out.println(number);
           }
       }

       Consumer<Integer> anonymous = new Consumer<Integer>() {
           @Override
           public void accept(Integer number) {
               number++;
               System.out.println(number);
           }
       };

       Local local = new Local();
       local.print(number);
       anonymous.accept(number);

       IntConsumer lambda = (number)-> System.out.println(number);      //error
    }
    ```

    ![error](/java/image/error.png)
     
     람다는 현재 main함수와 같은 scope을 가지기 때문에 number라는 변수가 중복된다고 컴파일에러가 뜨는 것을 볼 수 있다.

<br><br>

## Method Reference
- 메소드를 간결하게 사용할 수 있는 방법으로 람다를 간결하게 표현가능하게 해준다.
- 일반 함수를 람다형태로 사용 할 수 있게 해준다.

### 방법
1. 생성자 참조
```java
Supplier<String> supplier = () -> new String();
 Supplier<String> supplier2 = String::new;
 String str = supplier.get();
 
 //사용예
 List<List<Integer>> list = new ArrayList<>();
 int[][] arr = list.stream()
        .map(l -> l.stream()
            .mapToInt(Integer::intValue)
            .toArray())
        .toArray(int[][]::new);
```
이때 생성자 참조는 실제 생성자를 이용해 객체를 만든 것이 아니라 말그대로 `참조`이기 때문에 Supplier의 `get()`, Function의 `apply()`, 위 예시의 Stream의 `toArray()`와 같이 실제로 실행하는 부분에서 생성자를 이용하게 된다.

2. Static Method 참조
Static 메서드 또한 참조가 가능하며 이도 직접적으로 실행하는 메서드를 통해 실행이 가능하다.
```java
static class MethodReference{
    public MethodReference() {
        System.out.println("hi");
    }

    public static void print(String name){
        System.out.println("hi " + name);
    }

}

public static void main(String[] args) {
    String name = "홍";

    MethodReference.print(name);        //일반적인 static 메서드 사용

    Consumer<String> consumer = MethodReference::print; //static 메서드 참조
    consumer.accept(name);
}
```

3. 특정 객체의 Instance Method 참조
특정 객체(인스턴스)의 일반 메서드도 참조할 수 있는데 이때는 static method와 달리 `클래스명::static 메서드명`이 아니라 `인스턴스명::메서드명`과 같은 형태로 참조가 가능하다.
```java
static class MethodReference{
    public MethodReference() {
        System.out.println("hi");
    }

    public void print(String name){
        System.out.println("hi " + name);
    }

}

public static void main(String[] args) {
    String name = "홍";

    MethodReference object = new MethodReference();     //일반적인 객체 메서드 사용
    object.print(name);

    Consumer<String> consumer = object::print;      //instance 메서드 참조
    consumer.accept(name);
}
```

4. 임의 객체의 Instance Method 참조
정렬에 이용되는 Comparator가 대표적으로 이때는 static 메서드 참조와 동일하게 `클래스명::메서드명`으로 사용된다.
```java
String[] names = {"a", "B", "c"};
Arrays.sort(names, String::compareToIgnoreCase);
```

<br><br>

## byte 코드 비교
```java
//일반적인 함수형 인터페이스 구현
public class Lambda {
    @FunctionalInterface
    public interface Functional {
        public int cal(int a, int b);
    }
    public static void main(String[] args) {
        Functional functional = new Functional() {
            @Override
            public int cal(int a, int b) {
                return a+b;
            }
        };
    }
}

//byte 코드
public class ex/Lambda {

  // compiled from: Lambda.java
  NESTMEMBER ex/Lambda$Functional
  NESTMEMBER ex/Lambda$1
  // access flags 0x609
  public static abstract INNERCLASS ex/Lambda$Functional ex/Lambda Functional
  // access flags 0x0
  INNERCLASS ex/Lambda$1 null null

  // access flags 0x1
  public <init>()V
   L0
    LINENUMBER 11 L0
    ALOAD 0
    INVOKESPECIAL java/lang/Object.<init> ()V       
    RETURN
   L1
    LOCALVARIABLE this Lex/Lambda; L0 L1 0
    MAXSTACK = 1
    MAXLOCALS = 1

  // access flags 0x9
  public static main([Ljava/lang/String;)V
   L0
    LINENUMBER 17 L0
    NEW ex/Lambda$1
    DUP
    INVOKESPECIAL ex/Lambda$1.<init> ()V            //Lambda$1의 메서드 호출
    ASTORE 1
   L1
    LINENUMBER 23 L1
    RETURN
   L2
    LOCALVARIABLE args [Ljava/lang/String; L0 L2 0
    LOCALVARIABLE functional Lex/Lambda$Functional; L1 L2 1
    MAXSTACK = 2
    MAXLOCALS = 2
}

//컴파일러가 생성한 익명 클래스 Lambda$1
class Lambda$1 implements Functional {
    Lambda$1() {
    }

    public int cal(int a, int b) {
        return a + b;
    }
}
```
메서드내에서 함수형인터페이스를 override하여 직접 구현하는 방식은 build 했을때 Functional이라는 인터페이스를 이용하여 `Lambda$1`이라는 익명 클래스를 만들어내어 호출부에서느 Lamda$1의 메서드를 호출하는 것을 볼 수 있다. 내부적으로 익명클래스로 컴파일하여 사용하지 않는 이유는 java8이전의 람다를 사용하기 위한 라이브러리나, 코틀린같은 언어에서 람다를 이와 가티 단순히 익명클래스로 치환하여 사용하기 때문에 이처럼 구현이 되어있다.

이렇게 익명클래스로 사용할 경우의 문제점은 람다식마다 클래스가 하나씩 생겨나고 항상 새로운 인스턴스로 할당되는 문제가 있을수 있다.


```java
//람다이용한 함수형 인터페이스 구현
// class version 55.0 (55)
// access flags 0x21
public class ex/Lambda2 {

  // compiled from: Lambda2.java
  NESTMEMBER ex/Lambda2$Functional
  // access flags 0x609
  public static abstract INNERCLASS ex/Lambda2$Functional ex/Lambda2 Functional
  // access flags 0x19
  public final static INNERCLASS java/lang/invoke/MethodHandles$Lookup java/lang/invoke/MethodHandles Lookup

  // access flags 0x1
  public <init>()V
   L0
    LINENUMBER 3 L0
    ALOAD 0
    INVOKESPECIAL java/lang/Object.<init> ()V
    RETURN
   L1
    LOCALVARIABLE this Lex/Lambda2; L0 L1 0
    MAXSTACK = 1
    MAXLOCALS = 1

  // access flags 0x9
  public static main([Ljava/lang/String;)V
   L0
    LINENUMBER 9 L0
    INVOKEDYNAMIC cal()Lex/Lambda2$Functional; [
      // handle kind 0x6 : INVOKESTATIC
      java/lang/invoke/LambdaMetafactory.metafactory(Ljava/lang/invoke/MethodHandles$Lookup;Ljava/lang/String;Ljava/lang/invoke/MethodType;Ljava/lang/invoke/MethodType;Ljava/lang/invoke/MethodHandle;Ljava/lang/invoke/MethodType;)Ljava/lang/invoke/CallSite;
      // arguments:
      (II)I, 
      // handle kind 0x6 : INVOKESTATIC
      ex/Lambda2.lambda$main$0(II)I, 
      (II)I
    ]
    ASTORE 1
   L1
    LINENUMBER 10 L1
    RETURN
   L2
    LOCALVARIABLE args [Ljava/lang/String; L0 L2 0
    LOCALVARIABLE functional Lex/Lambda2$Functional; L1 L2 1
    MAXSTACK = 1
    MAXLOCALS = 2

  // access flags 0x100A
  private static synthetic lambda$main$0(II)I
   L0
    LINENUMBER 9 L0
    ILOAD 0
    ILOAD 1
    IADD
    IRETURN
   L1
    LOCALVARIABLE a I L0 L1 0
    LOCALVARIABLE b I L0 L1 1
    MAXSTACK = 2
    MAXLOCALS = 2
}
```
람다를 이용한 방식은 새로운 익명클래스를 생성시키지는 않고 람다를 사용한 메서드를 새롭게 static으로 생성(lambda$main$0)해서 이를 실행하는 것을 볼 수 있다.

>INVOKEDYNAMIC? bootstrap영역의 lambdafactory.metafactory()를 호출하는데 이는 Java runtime library의 표준화 메서드로 객체를 어떤방법으로 생성할지 동적으로 결정한다는 의미 (새로, 재사용, 프록시, 래퍼클래스 등). 후에 `java/lang/invoke/CallSite`를 통해서 객체를 return 
>
>한마디로 람다가 변환되는 인터페이스의 인스턴스를 반환하는 코드로 한번만 생성되고 재 호출시에는 재사용이 가능하다.

<br><br>


## Functional Interface
단 1개의 추상메서드만을 갖는 인터페이스

```java
@FunctionalInterface
public interface Functional {
        public int cal(int a, int b);       //abstract 키워드 생략가능
        
        public static void staticMethod(){
            System.out.println("static");
        }
        
        default void defaultMethod(){
            System.out.println("default");
        }
    }
```
위와 같이 static/default 메서드를 여러개를 가져도 추상클래스가 한개뿐이라면 함수형 인터페이스라고 부를 수 있다. 어노테이션(@FunctionalInterface)를 이용하면 컴파일 타임에 함수형인터페이스인지를 검사하여 에러를 발생시킬 수 있다.

![functional interface error](/java/image/functionalInterfaceError.png)

### Java에서 제공하는 기본 함수형 인터페이스
1. Consumer<T> : 하나의 T 타입 input을 갖고 return이 없는 함수를 갖는 인터페이스
    1. BiConsumer<T,U> : 두개의 T,U 타입 input을 갖고 return이 없는 함수를 갖는 인터페이스
1. Supplier<T> : 인자를 받지 않고 T타입의 객체를 return하는 함수를 갖는 인터페이스
1. Functional<T,R> : T타입의 input을 갖고 R타입 객체를 return 하는 함수를 갖는 인터페이스
    1. BiFunctional<T,U,R> : 두개의 T,U 타입 input을 갖고  R타입 객체를 return 하는 함수를 갖는 인터페이스
1. Predicate<T>  : T타입 input을 갖고 boolean타입을 return하는 함수를 갖는 인터페이스
    1. BiPredicate<T,U> : 두개의 T,U 타입 input을 갖고 boolean타입을 return하는 함수를 갖는 인터페이스