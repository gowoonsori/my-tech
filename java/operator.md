# 연산자
## 산술 연산자

두개의 피연산자를 갖는 `이항 연산자`로써, 기본적인 사칙연산을 다루는 연산자

### 더하기 (+)

왼쪽의 피연산자에 오른쪽 피연산자를 더하는 연산자로 `숫자+숫자`, `문자열+문자열`이 가능하고 `문자열+숫자`를 할 시 숫자를 자동으로 문자열로 변환하여 덧셈이 가능하다.

`문자+숫자`를 할 경우에는 `아스키 코드`를 이용하여 `문자`로 결과가 출력 된다.
<br>문자에 맞는 아스키 코드값과 숫자를 더한 결과값에 해당하는 아스키코드를 return하기 때문이다.

```java
int left = 2020;
int right = 1;
int year = left + right;
char ch = A;

System.out.println(year); //2021
System.out.println("20"+"21"); //2021
System.out.println("Hello "+ year); //Hello 2021

System.out.println(ch + 2); //C
System.out.println( 9 + '0'); //9


```

### 뺄셈 (-)

왼쪽의 피연산자에서 오른쪽 피연산자를 빼는 연산자로 `숫자-숫자`와 같이 사용가능하고 문자열은 불가능하다.

### 곱셈 (\*)

왼쪽의 피연산자에 오른쪽 피연산자를 곱하는 연산자로 `숫자*숫자`와 같이 사용가능하고 문자열은 불가능하다.

### 나눗셈 (/)

왼쪽의 피연산자를 오른쪽 피연산자로 나누는 연산자로 `숫자/숫자`와 같이 사용가능하고 문자열은 불가능하다.

`정수/정수`를 할 시 나머지는 버려진 몫만 구해지며 두 피연산자 중 하나라도 `실수(부동 소수방식)`가 존재한다면 결과는 `실수`가 나온다.

오른쪽 피연산자가 0이 될 수 없다. (0으로 나눌 수 없고 나눈다면 `컴파일 에러`가 난다.)

0이 아닌 정수를 0.0으로 나눈다면 `Infinity`, 0을 0.0으로 나눈다면 `NaN`이 반환된다.

```java
int left = 5;
int right = 2;
System.out.println(left/right); // 2
System.out.println(left/2.0); // 2.5

System.out.println(left/0.0); //Infinity
System.out.println(0/0.0);      //NaN
```

### 나머지 (%)

왼쪽의 피연산자를 오른쪽 피연산자로 나눈 나머지를 구하는 연산자로 `숫자%숫자`와 같이 사용가능하고 문자열은 불가능하다.

왼쪽 피연산자를 0.0이나 0으로 나눈다면 `NaN`이 반환된다. (왼쪽 피연산자가 정수인데 0으로 나눈다면 `컴파일 에러`)

```java
System.out.println(5%0); //컴파일 에러
System.out.println(5.0%0);  //NaN
System.out.println(0.0%0);  //NaN
System.out.println(0%0); //컴파일 에러

System.out.println(5%0.0);  //NaN
System.out.println(5.0%0.0); //NaN
System.out.println(0.0%0.0); //NaN
System.out.println(0%0.0);  //NaN
```

<br><br>

## 단항 연산자

피 연산자를 한개만 갖는 연산자

### 부호 연산 (+/-)

숫자를 입력시 `+`는 형식적으로 제공을 하기 때문에 생략이 가능하다.

`-`는 부호를 바꾸는 연산자로 `2의 보수`를 취하는 연산자이다.

```java
System.out.println(2);//2
System.out.println(+2);//2
System.out.println(-2);// -2


```

### 증감 연산자 (++/--)

증감 연산자 독립적으로 사용하는 경우에는 위치에 상관없이 같은 결과를 갖는다.

```java
int i=1;
int j=1;

i++; // i = 2
++j; // j = 2
i--; // i = 1
--j; // j = 1
```

다른 명령문과 같이 쓰인다면 결과가 달라진다.

- 전위 증감 연산

  피연산자를 참조하기전에 값을 증감 시키고 난 후에 피연산자를 참조한다.

  ```java
  int i=1;
  System.out.println(++i); //2출력
  System.out.println(--i); //1출력
  ```

- 후위 증감 연산

  피연산자를 먼저 참조하고난 후 증감 시킨다.

  ```java
  int i = 1;
  System.out.println(i++); //1 출력 후 i=2
  System.out.println(i--); //2 출력 후 i=1
  ```

<br><br>

## 비트 연산자

피연산자를 이진수로 생각하고 각 자리수(bit)단위로 계산하는 연산자

### 비트 NOT (~)

1의 보수를 구하는 연산자로 각 bit를 반전 시키는 연산자

```java

```

### AND (비트곱) (&)

두 피연산자의 각 bit들을 AND 연산

- 1 & 1 = 1

- 1 & 0 = 0
- 0 & 1 = 0
- 0 & 0 = 0

```java
byte num1 = 10;  //bit로 00001010
byte num2 = 20;  //bit로 00010100

byte num3 = num1 & num2;
System.out.println(num3); //비트 곱하면 00000000로 0이 나온다.
```

### OR (비트합) (|)

두 피연산자의 각 bit를 OR 연산

- 1 | 1 = 1

- 1 | 0 = 1
- 0 | 1 = 1
- 0 | 0 = 0

```java
byte num1 = 10;  //bit로 00001010
byte num2 = 20;  //bit로 00010100

byte num3 = num1 | num2;
System.out.println(num3); //비트 곱하면 00011110로 30이 나온다.
```

### XOR (^)

두 피연산자의 각 bit를 XOR 연산

- 1 ^ 1 = 0

- 1 ^ 0 = 1
- 0 ^ 1 = 1
- 0 ^ 0 = 0

```java
byte num1 = 10;  //bit로 00001010
byte num2 = 20;  //bit로 00010100

byte num3 = num1 ^ num2;
System.out.println(num3); //비트 XOR하면 00011110로 30이 나온다.
```

### 오른쪽 Shift 연산자 (>>)

왼쪽의 피연산자의 bit를 오른쪽 피연산자의 수만큼 `오른쪽`으로 이동시키고 밀린 오른쪽 끝의 비트는 삭제되며 새로 오는 가장 왼쪽의 bit는 원래 부호에 따라 `0(양수)` or `1(음수)`로 채워진다.

```java
byte num1 = 10; //00001010
byte num2 = -10; //11110110

System.out.println(num1 >> 1); //00000101
System.out.println(num2 >> 1); //11111011
```

### unsigned 오른쪽 Shift 연산자 ( >>> )

왼쪽의 피연산자의 bit를 오른쪽 피연산자의 수만큼 `오른쪽`으로 이동시키고 밀린 오른쪽 끝의 비트는 삭제되며 새로 오는 가장 왼쪽의 bit는 부호에 상관없이 `0`으로 채워진다.

```java
byte num1 = 10; //00001010
byte num2 = -10; //11110110

System.out.println(num1 >> 1); //00000101
System.out.println(num2 >> 1); //01111011
```

### 왼쪽 Shift 연산자 (<<)

왼쪽의 피연산자의 bit를 오른쪽 피연산자의 수만큼 `왼쪽`으로 이동시키고 밀린 왼쪽 끝의 비트는 삭제되며 새로 오는 가장 오른쪽의 bit는 `0`으로 채워진다.

```java
byte num1 = 10; //00001010
byte num2 = -10; //11110110

System.out.println(num1 << 1); //00010100
System.out.println(num2 << 1); //11101100
```

<br><br>

## 관계 연산자

두 피연산자간에 값을 비교하기 위한 연산자

### 동치 연산자 ( == / != )

두 피연산자 값이 같은지 비교하는 연산자로 `원시형 타입`끼리 비교할때는 값을 비교하고 데이터 크기가 다른 데이터타입끼리의 비교라면` 큰 데이터 타입으로 변환`되어 비교한다.

`참조 타입 (String, Array, Class...)`끼리의 비교라면 `동일한` 원본 데이터(`객체`)인지 비교한다.

- == : 두 피연산자 값이 같으면 `false`, 아니면 `false` 반환

- != : 두 피연산자 값이 같지 않으면 `false`, 같으면 `false` 반환

### < , <=

왼쪽 피연산자가 오른쪽 피연산자보다 작은지(작거나 같은지) 판단하여 맞다면 true, 아니라면 false반환

### >, >=

왼쪽 피연산자가 오른쪽 피연산자보다 큰지(크거나 같은지) 판단하여 맞다면 true, 아니라면 false 반환

## 논리 연산자

`boolean 형(true/false)`를 비교하는 연산자로 두 피연산자가 boolean형일때만 사용가능 하다.

### 논리 NOT (!)

한개의 피연산자의 값을 바꾸는 연산자

```java
boolean t = true;
System.out.println(!t); //false;
```

### 논리 AND (&&)

두 피연산자가 모두 `true`이면 `true` 아니면 `false`를 반환한다.

```java
boolean t = true;
boolean f = false;

System.out.println(t && t); //true
System.out.println(t && f); //false
System.out.println(f && t); //false
System.out.println(f && f); //false
```

### 논리 OR (||)

두 피연산자중 하나라도 `true`이면 `true` 아니면 `false`를 반환한다.

```java
boolean t = true;
boolean f = false;

System.out.println(t || t); //true
System.out.println(t || f); //true
System.out.println(f || t); //true
System.out.println(f || f); //false
```

### 단락 회로 평가 (Short Circuit Evaluation)

논리 연산자를 수행 중 true나 false조건이 만족된다면 오른쪽 피연산자는 참조안하고 바로 true 리턴하는 것

```java
System.out.println(f && t); //왼쪽이 피연산자가 이미 false이므로 오른쪽 피연산자인 t 는 참조하지 않고 바로 false return
System.out.println(t && f); //왼쪽이 true이기 때문에 오른쪽피연산자 값에 따라 return값이 다르므로 오른쪽 피연산자 참조후 false return

System.out.println(t || f); //왼쪽이 피연산자가 이미 true이므로 오른쪽 피연산자인 t 는 참조하지 않고 바로 truereturn
System.out.println(f || f); //왼쪽이 false이기 때문에 오른쪽피연산자 값에 따라 return값이 다르므로 오른쪽 피연산자 참조후 false return
```

### &,|,^

비트 연산자를 논리형(boolean)에도 사용할 수 있으며 결과값은 동일하지만 `단락 회로 평가`가 되지 않는다.
<br>_(양쪽 피연산자를 모두 참조후 결과 값 반환)_

```java
boolean t = true;
boolean f = false;

System.out.println(t & t); //true
System.out.println(t & f); //false
System.out.println(f & t); //false
System.out.println(f & f); //false

System.out.println(t | t); //true
System.out.println(t | f); //true
System.out.println(f | t); //true
System.out.println(f | f); //false

System.out.println(t ^ t); //false
System.out.println(t ^ f); //true
System.out.println(f ^ t); //true
System.out.println(f ^ f); //false
```

<br><br>

## instanceof

`참조 타입`의 변수가 특정 타입인지 검사하는 연산자로 `같다면 true`, `아니라면 false`가 반환되고 `null`을 검사하려고한다면 `false`가 반환된다.

`참조 타입` 변수가 초기화가 되지 않았다면 검사할 변수의 참조 값이 없으므로 `컴파일 에러`가 뜬다.

자바의 모든 객체는 암시적으로 `Object`를 상속받고 있기 때문에 Object로 비교해도 true가 나오며 왼쪽 피연산자로 `원시타입`은 올 수 없다.

```java
int[] i;
System.out.println(i instanceof int[]); //컴파일 에러

int[] i = new int[5];
System.out.println(i instanceof Object); //true
System.out.println(i instanceof int[]); //true

Object j = new int[5];
System.out.println(i instanceof int[]); //true
System.out.println(j instanceof Object);//true

System.out.println(null instanceof Object);//false

System.out.println("hello" instanceof Object);//true
System.out.println("hello" instanceof String);//true

ArrayList arrayList= new ArrayList();
System.out.println(arrayList instanceof ArrayList); //true
System.out.println(arrayList instanceof Object);  //true
```

<br><br>

## assignment(=) 연산자

우리가 일반적으로 변수에 값을 할당하거나 참조할 데이터 주소를 할당할때 쓰는 연산자이다.

### 복합 대입 연산자

연산을 실행 후 대입하는 연산자로 `산술 연산자` or `비트 연산자` or `시프트 연산자`와 `대입연산자`를 합친 형태이다.

```java
int i = 10;

i += 1; // i = i + 1
i -= 2; // i = i - 2
i *= 3; // i = i * 3
i /= 4; // i = i / 4
i %= 5; // i = i % 5

i &= 1; // i = i & 1
i |= 2; // i = i | 2
i ^= 3; // i = i ^ 3

i <<= 1; // i = i << 1
i >>= 2; // i = i >> 2
i >>>= 3; // i = i >>> 3

```

<br><br>

## 화살표(->) 연산자

람다를 사용하기 위해 도입된 `람다 표현식`으로 `익명 컬렉션`이다.

핵심은 **간단하게 표현**이다.

컴파일러의 추론을 통해 지울수 있는 것은 모두 지우거나(생략하여) 표현하는 방법

```java
interface User{
    void printUserName(String name);
}

User user = new User() {
    @Override
    public void printUserName(String name) {
        System.out.println("User name is " + name);
    }
};
```

위의 코드와 같이 setUserName메서드 하나만을 갖고있는 User 인터페이스에서 이 메서드를 override하려고 한다고 하자

여기서 컴파일러는 `User user`를 통해 데이터 타입을 명시 했기 때문에 `new User`부분은 생략이가능할 것이고 메서드는 하나만 갖고있기때문에 메서드를 명시하지 않아도 될 것이다.

이런 점을 이용하여 람다식으로 표현한다면 아래와 같이 표현할 수 있따.

```java
User user = (name) -> {
    System.out.println("User name is " + name);
}
```

파라미터 인자가 한개라면 `()`는 생략이 가능하고 `{}`안의 코드가 한줄이라면 `{}`또한 생략이 가능하다.

<br><br>

## 3항 연산자 (?:)

말그대로 3개의 피연산자를 사용하는 연산자이다.

`조건문 (if/else)`처럼 사용이 가능하다.

`조건문 ? 값1 : 값2`와 같은 형태로 조건문이 참이라면 값1을 조건문이 거짓이라면 값2를 반환한다.

```java
boolean isTrue1 = (10 > 1) ? true : false;  //10 > 1은 true이기 때문에 true를 isTrue에 반환한다.

(10 > 1) ? true : false; //3항 연산자는 식으로써 값을 만들어내기 때문에 참조나 대입이 없다면 `Not a Statment`라는 컴파일 에러를 띄운다.
```

### if/else와 3항 연산자 차이

- if/else는 `statement`로써 값을 만들어내지 못한다.

- 3항 연산자는 `expression`으로써 값을 만들어 낸다.

[Statement와 Expression란? (if/else와 삼항연산자의 차이)](https://manorgass.tistory.com/68)

때문에 `?`뒤에 오는 `2개의 값`에는 값만 넣고 코드를 넣지 말자!!

`가독성`도 안좋아지고 엄연히 `목적이 다르다.`

<br><br>

## 연산자 우선 순위

| 우선순위 |                                 연산자                                 |   연산 방향    |                     동작 내용                      |
| :------: | :--------------------------------------------------------------------: | :------------: | :------------------------------------------------: | -------------- | ------- |
|    1     |                                  `.`                                   | 왼쪽 -> 오른쪽 |                   객체 멤버 접근                   |
|          |                                `[`, `]`                                | 왼쪽 -> 오른쪽 |                   배열 요소 접근                   |
|          |                                `(args)`                                | 왼쪽 -> 오른쪽 |                    메소드 호출                     |
|          |                              `i++`, `i--`                              | 왼쪽 -> 오른쪽 |                     후위 증감                      |
|    2     |                              `++i`, `--i`                              | 왼쪽 <- 오른쪽 |                     전위 증감                      |
|          |                                `+`, `-`                                | 왼쪽 <- 오른쪽 |                     단항 증감                      |
|          |                                `~`, `!`                                | 왼쪽 <- 오른쪽 |                비트 보수, 부정 연산                |
|    3     |                                 `new`                                  | 왼쪽 <- 오른쪽 |                     객체 생성                      |
|          |                              `(datatype)`                              | 왼쪽 <- 오른쪽 |                  캐스팅(형 변환)                   |
|    4     |                             `*`, `/`, `%`                              | 왼쪽 -> 오른쪽 |               곱하기, 나누기, 나머지               |
|    5     |                                `+`,`-`                                 | 왼쪽 -> 오른쪽 |                    더하기, 빼기                    |
|    6     |                           `<<`, `>>`, `>>>`                            | 왼쪽 -> 오른쪽 | 왼쪽 시프트, 오른쪽 시프트, 부호없는 오른쪽 시프트 |
|    7     |                          `<`, `<=`, `>`, `>=`                          | 왼쪽 -> 오른쪽 |         작음, 작거나 같음, 큼, 크거나 같음         |
|          |                              `instanceof`                              | 왼쪽 -> 오른쪽 |                     타입 비교                      |
|    8     |                               `==`, `!=`                               | 왼쪽 -> 오른쪽 |                  같음, 같지 않음                   |
|    9     |                                  `&`                                   | 왼쪽 -> 오른쪽 |                        AND                         |
|    10    |                                  `^`                                   | 왼쪽 -> 오른쪽 |                        XOR                         |
|    11    |                                   `                                    |       `        |                   왼쪽 -> 오른쪽                   | OR             |
|    12    |                                  `&&`                                  | 왼쪽 -> 오른쪽 |                      논리 AND                      |
|    13    |                                   `                                    |                |                         `                          | 왼쪽 -> 오른쪽 | 논리 OR |
|    14    |                                  `?:`                                  | 왼쪽 <- 오른쪽 |                     3항 연산자                     |
|    15    | `=`, `*=`, `/=`, `%=`, `+=`, `-=`, `<<=`, `>>=`, `>>>=`, `&=`, `^=`, ` |       =`       |                   왼쪽 <- 오른쪽                   | 대입 연산자    |
|    16    |                                  `->`                                  | 왼쪽 -> 오른쪽 |                    람다 표현식                     |

<br><br>

## switch 연산자

```java
  //Java 12 이전
        int num = 1;
        int result = 0;
        switch(num){
            case 1:
                result = 1;
                System.out.println("1");
                break;
            case 2:
                result = 2;
                System.out.println("2");
                break;
            case 3:
                result = 3;
                System.out.println("3");
                break;
        }

        //Java 12
        var result2 = switch(num){
            case 1 -> 1;
            case 2 -> System.out.println("2"); //compile error
            case 3 -> 3;
            case 4 :            //compile error
                System.out.println("4");
                break;
            default -> throw new IllegalStateException("default");
        };


        //Java13
        var result3 = switch(num){
            case 1 : {
                System.out.println("1");
                yield 1;
            }
            case 2 : yield 2;
            case 3 : yield 3;
            default :
                throw new IllegalStateException("default");

        };

        var result4 = switch(num){
            case 1 -> {
                System.out.println("1");
                yield 1;
            }
            case 2 -> 2;
            case 3 -> {
                yield 3;
                System.out.println("2");  //compile error
            }
            default ->
                throw new IllegalStateException("default");

        };

```

기존의 switch문에서 외부 변수에 값을 대입하기 위해서는 위의 코드와 같이 `result = 1`과 같은 식으로 매 case마다 추가해주어야 했었다.

Java 8이후에 `람다식`이 생기고 나서 Java에 많은 변화가 있었고 `Java 12`에는 case마다 결과값을 반환하는 switch문에 경우 `람다 표현식(->)`을 사용 할 수 있게 되었다.

`Java 12`의 람다 표현식의 경우 바로 대입값을 우항에 표현해주어야 했기 때문에 추가 작업을 못한다는 단점이 있어

`Java 13`에 `yield`가 추가 되었다.

`yield`를 사용하면 해당 값을 return하고 case문을 종료하기 때문에 `yield`다음 줄에 다른 구문이 온다면 `compile error`가 난다.

### 특징

- 각 case마다 반환타입을 컴파일시에 추론이 가능하기 때문에 추론형 데이터 타입인 `var`이 가능하다.

- 모든 case에 대해 반환 값이 있어야 error가 안나기 때문에 `default`문도 반드시 있어야 한다.
- `람다 표현식(->)`과 `기존 표현식 (:)`은 혼용해서 사용이 불가능하다.
- `break;`구문 없이도 다음 case로 넘어가지 않는다.

<br><br><br>

---

### Refernece

https://blog.baesangwoo.dev/posts/java-livestudy-3week/#%EB%B9%84%ED%8A%B8-%EC%97%B0%EC%82%B0%EC%9E%90

https://multifrontgarden.tistory.com/124
