자바에서 데이터 타입은 크게 원시(Primitive) 타입과 참조(Reference) 타입이 있다.

<br>

# Primitive Type

정수, 실수, 문자, 논리 리터럴과 같은 실제 데이터 값을 저장하는 타입

|  종류  | 데이터 타입 | 크기(byte) | 기본 값 |               범위                |
| :----: | :---------: | :--------: | :-----: | :-------------------------------: |
| 논리형 |   boolean   |   1byte    |  false  |            true, false            |
| 문자형 |    char     |   2byte    | \u0000  |            0 ~ 65,535             |
| 정수형 |    byte     |   1byte    |    0    |             -128~ 127             |
| 정수형 |    short    |   2byte    |    0    |         -2^15 ~ 2^15 - 1          |
| 정수형 |     int     |   4byte    |    0    |         -2^31 ~ 2^31 - 1          |
| 정수형 |    long     |   8byte    |   0L    |         -2^63 ~ 2^63 - 1          |
| 실수형 |    float    |   4byte    |  0.0F   |      1.4E-45 ~ 3.4028235E38       |
| 실수형 |   double    |   8byte    |   0.0   | 4.9E-324 ~ 1.7976931348623157E308 |

- boolean : c와 같이 true와 false를 표현하는데 1bit만 있으면 될 것 같지만 Java는 데이터 최소범위가 1Byte이기 때문에 boolean도 1byte의 크기를 갖는다.

- char : c의 경우 1byte의 크기를 같지만 Java는 `유니코드`를 표현하기 위해 기본 2byte를 갖으며, Java의 원시 데이터타입중 유일하게 unsigned형태이다.

- 정수형 : JVM의 스택이 기본적으로 피연산자를 4byte 단위로 저장하기 때문에 int보다 작은 자료형의 값을 계산할때 int형으로 형변환되어서 연산이 수행되기 때문에 굳이 byte와 short형을 사용할 필요는 없어 보인다.

  JVM은 int형을 정수형의 기본 데이터 타입으로 사용하기 때문에 long을 사용하고자 한다면 뒤에 `l`,`L`을 붙여야 한다.

  > Java8 이후부터는 Integer와 Long의 Wrapper클래스에 unsigned 관련 메소드가 추가되어 unsigned 형태도 이용이 가능하다.

- 실수형 : double형이 기본 데이터 타입으로 float형을 사용하고자 한다면 뒤에 `f`,`F`를 붙여 주어야 한다.

  메모리 크기는 int,long과 같지만 실수형은 `부동소수점` 방식으로 저장하여 더 많은 범위를 저장 할 수 있다.

  float의 경우 부호(1bit)+지수(8bit)+가수(23bit), double의 경우 부호(1bit)+지수(11bit)+가수(52bit)로 나누어 저장하게 되어 표현범위가 고정 소수점방식보다 넓지만 실수 표현에 있어 근사치를 표현하기 때문에 오차가 존재하는 단점을 갖고있다.

  _(0.1을 1000번 더하게 되면 100이 되어야 하지만 100.09999... 와 같은 근사값이 출력된다.)_

  float의 경우 소수점 아래 9자리, double의 경우 18자리까지 표현이 가능하다.

  같은 데이터 타입에서도 int,long / float,double형으로 나눈 이유는 메모리를 효율적으로 사용하기 위해서 이다.

  > 닭 잡는데 소 잡는 칼을 사용하는 것은 낭비이기 때문이다.

<br><br>

# Refrerence Type

영어 의미 그대로 참조 타입으로 저장되는 값이 원시데이터와 다르게 실제 값이 아닌 `메모리 주소값`이 저장되는 타입으로 `문자열`,`배열`,`enum`,`class`,`interface`등이 있다.

JVM의 Runtime Data Area중 `참조 타입 변수`는 `런타임 스택 영역`에 `실제 객체`는 `힙 영역`에 저장되어 객체를 사용할때 마다 참조 변수에 저장된 객체의 주소를 불러와 사용한다.

위에서 말한것과 같이 실제 데이터는 `힙 영역`에 저장되며 데이터 크기는 정해져있지 않고 동적으로 할당되며 참조하는 변수가 없다면 `Garbage Collector`가 제거하여 메모리를 관리한다.

- Boxing : 원시 타입을 참조 타입으로 변환시키는 것
- Unboxing : 참조 타입을 원시 타입으로 변환 시키는 것

  Auto Boxing기능으로 명시적으로 작성하지 않아도 자동으로 Boxing 을 해준다.

  ```java
  int i= 1;
  Integer integer = i; //Auto Boxing
  ```

## 특징

- `null`을 포함할 수 있다.

  ```java
  int example = null; //error
  Integer integer = null;
  ```

- `제네릭 타입`에서 사용할 수 있다

  ```java
  List<int> list; //error
  List<Integer> list;
  ```

- 데이터 접근 속도가 원시타입에 비해 느리다

  원시타입은 `스택`에서 바로 사용이가능하나 참조타입은 `스택`에서 메모리주소를 갖고 `힙`에 접근하는 방법으로 값을 필요할때마다 `Unboxing`을 거쳐야하기 때문에 접근속도가 느려지게 된다.

  하지만, 큰 크기의 데이터 접근이 아닌 전달,복사의 경우에는 원시타입보다는 참조타입이 좋을 수도 있다.

<br><br>

# 리터럴

메모리에 저장되어 변하지 않는 값을 뜻하며 `컴파일 타임`에 `정의`되어 그대로 사용하는 값

대입 연산에서 모든 우항의 값들을 보통 리터럴이라고 부른다.

```java
boolean isTrue = true;
char c = 'C';
int i = 1001;
long il = 1001L;
float f = 1.1234F;
double d = 1.1234;
String str = "hello";
```

와 같이 우항에 있는 내가 정의한 값들로 변하지 않는 값들을 의미한다.

<br><br>

# 변수 선언 및 초기화 방법

## 변수 선언

```
(데이터 타입) (변수명1),(변수명 2)... ;

--Example --
int i;
int j,k,l;
```

위와 같이 하나의 변수를 선언이 가능하고 동시에 여러개도 가능하다.

## 변수 초기화

- 선언 후 초기화

  ```java
  int i;
  i =10;
  ```

- 선언과 동시에 초기화

  ```java
  int i=10;
  ```

<br><br>

# 변수의 스코프와 라이프타임

`변수의 스코프`란 해당 변수에 접근할 수 있는 범위를 나타내는 것으로 `중괄호 {}`를 통해 스코프를 나누는 `블록 스코프`이고 해당 변수가 언제까지 존재하는지가 라이프 타임이다.

지역변수의 `라이프타임`과 `스코프`는 `코드 블럭`에 국한된다.

```java
public class example {
    public static void main(String[] args){
        int i =1;
        if(true){
            int j=2;
            System.out.println(i);
        }
        System.out.println(j); //error
    }
}
```

위의 코드에서 if내에서 i를 접근할때 if의 코드 블럭에서 i를 찾고 없으면 그보다 상위 블럭인 class 블럭에서 i를 찾아 접근이 가능하지만 j는 if내에 선언되어 if의 `블럭({})`에 국한되기 때문에 if밖에 나와서는 접근이 불가능하고 if의 블럭이 끝나면서 if에 국한되어있던 `지역 변수`들은 스택영역에서 소멸된다.

`레퍼런스 타입`저장시에 저장되는 `힙 영역`데이터의 라이프 타임은 `가비지 컬렉터`가 관리한다.

```java
public class example {
    public static void main(String[] args){
        String str = "Test";
        System.out.println(str);
        str = null;
        System.out.println(str);
    }
}
```

str은 `Test`라는 `힙영역`에 저장된 데이터를 참조하는 변수인데, `str=null;`부분을 통해 `Test`를 가리키는 변수는 더이상 존재하지 않게 되어 `가비지 컬렉터가` 힙영역에서 Test라는 데이터를 제거하게 된다.

이처럼 `참조 타입`의 힙 영역에 저장되는 데이터는 아무도 참조하지 않게 되었을때 소멸된다.

<br><br>

# 타입 변환, 캐스팅 , 타입 프로모션

특정 데이터 타입의 값을 다른 데이터 타입의 값을 변환 하는 것

- 타입 프로모션 : 자신의 표현범위를 모두 포함한 데이터 타입으로 변환

  `byte -> int, int-> long`와 같이 더 큰 범위를 갖는 데이터 타입으로 변환의 경우가 속하거나 `int -> float`와 같이 같은 크기여도 표현범위를 모두 포함할 수 있다면 프로모션이다.

  `float -> long` 의 경우 데이터 크기로만 보면 프로모션이라고 생각할 수 있지만, long은 실수를 저장할 수 없기 때문에 데이터 손실이 일어나 프로모션이라고 할 수 없고 `캐스팅`이라고 볼 수 있다.

  ```java
  long l = 1234L;
  float f = l;
  ```

  위의 코드와 같이 `프로모션`의 경우 데이터 손실이 발생하지 않고 자동으로 형변환을 시켜준다.

- 타입 캐스팅 : 자신의 포현 범위를 모두 포함하지 못한 데이터 타입으로 변환

  `int->byte, long -> int`와 같이 큰 데이터크기에서 작은 크기의 데이터 타입으로 변환할때나 `float -> long`과 같이 데이터 표현범위가 달라지는 경우에 속하며 데이터 손실이 일어 난다.

  ```java
  float f = 1.234f;
  long l = f;
  ```

  위의 코드와 같이 자동으로 캐스팅을 하려고한다면 데이터 손실이 발생할 수 있기 때문에 `컴파일타임에 오류를 발생 시킨다.`

  그래도 형변환을 하고 싶다면 `강제형변환`을 사용할 수 있지만 데이터 손실이 발생하게 된다.

  ```java
  float f = 1.234f;
  long l = (long)f;
  System.out.println(l); // 1
  ```

<br><br>

# 1차, 2차 배열 선언

배열 변수 선언과 동시에 초기화를 통해 선언 하는 방식과 `new`를 이용하는 방식이 있다.

```java
class ArrayExample {
	public static void main(String[] args) {
        //1차원 배열
        int[] array1 = {1, 2, 3, 4, 5};
        int[] array2;
        array2 = new int[5];
        array2[0]=1;
        array2[1]=2;
        array2[2]=3;
        array2[3]=4;
        array2[4]=5;

        //2차원 배열
        int[][] array3 = {{1, 2}, {3, 4}};
        int[][] array4;
        array4 = new int[2][2];
        array4[0][0] = 1;
        array4[0][1] = 2;
        array4[1][0] = 3;
        array4[1][1] = 4;

    }
}
```

## 1차원 배열

![array1](/java/image/array1.PNG)

[사진 참조](https://www.notion.so/2-38b5d67c7f5a48238529bb8f1617ea0d)

1차원 배열의 변수(array1,array2)는 스택영역에 존재하며 `힙 영역`의 `주소값`을 갖는다.

`힙 영역`에는 데이터 타입 크기와 요소 개수에 맞게 할당되어 사용이된다.

## 2차원 배열

![array2](/java/image/array2.PNG)

[사진 참조](https://www.notion.so/2-38b5d67c7f5a48238529bb8f1617ea0d)

2차원 배열의 변수(array3,array4)는 스택영역에 존재하며 `힙 영역`의 `주소값`을 갖는다.

`힙 영역`에는 실제 데이터값들과 2차원배열의 각 행의 시작주소를 갖는 주소값들이 존재한다.

<br><br>

# 타입 추론

Java 10 이후부터 생겨난 기능으로 컴파일러가 값을 보고 데이터 타입이 무엇인지 추론하는 것으로 `Js`의 `var`,`let`와 비슷하다.

## 제네릭

```java
public class example{
    public static void main(String[] args){
        HashMap<String,Integer> hashMap = new HashMap<>();
    }
}
```

위와 같이 우항의 `<>`안에 값을 입력하지 않아도 좌항의 값을 보고 타입을 추론하여 생성하는 경우

## var

`JS`의 `var`,`let`과 같이 추론형 데이터 타입으로 생각할 수 있는데, 다른점으로 `지역 변수`와 `선언과 동시에 값이 할당 되어야 한다는 점`에서 `let과 const`를 합친 느낌이다.

```java
public class example{
    var i = 10; //error
    public static void main(String[] args){
        var j; //error
    }
}
```

<br><br><br>

---

## Reference

https://velog.io/@gillog/%EC%9B%90%EC%8B%9C%ED%83%80%EC%9E%85-%EC%B0%B8%EC%A1%B0%ED%83%80%EC%9E%85Primitive-Type-Reference-Type

https://wikidocs.net/81917

https://www.notion.so/2-38b5d67c7f5a48238529bb8f1617ea0d

https://blog.naver.com/hsm622/222144931396
