## 제어문

### 조건문

#### Switch

특정 데이터의 값에 따라 수행할 작업을 선택하는 구문으로 `switch`를 사용한다.

일반적인 사용법은 C/C++와 다르지 않다.

```java
public class example {
    public static void main(String[] args) {
        String select = "ORANGE";
        String fruit;

        switch(select){
            case "APPLE" :
                fruit = "apple";
                System.out.println("사과");
                break;
            case "BANANA" :
                fruit = "banana";
                System.out.println("바나나");
                break;
            case "ORANGE" :
                fruit = "orange";
                System.out.println("오렌지");
                break;
            default:
                fruit = "default";
                System.out.println("default");
                break;
        }
        System.out.println(fruit);
    }
}
```

`switch()` 매개변수에 `데이터 값`을 입력하고 `case : `를 이용해 값에 따라 구문을 구분하면 된다.

- String이나 ,Integer과 같은 Wrapper타입이 올 수 있다.

- case의 값에는 리터럴 이나 상수가 와야 하고 중복해서는 안된다.

Java 12버전 이후에 `case ->`를 이용하여 작업할 구문을 작성할 수 있게 되었고 break를 생략이 가능해졌다.

또한, `->`와 `yield`를 사용하여 `Switch`도 값을 반환할 수 있게 되었다.
<br>case에 따라 특정 변수의 값을 바꾸는 경우에는 위의 코드와 같이 외부의 변수에 값을 할당해주는 방법으로 비슷한 코드를 반복작성해야하는 단점이 존재했는데 쉽게 값을 바꿀 수 있게 되었다.

```java
public class example {
    public static void main(String[] args) {
        String select = "ORANGE";
        String fruit;

        fruit = switch(select){
            case "APPLE" -> {
                System.out.println("사과");
                yield "apple";
            }
            case "BANANA" -> {
                System.out.println("바나나");
                yield "banana";
            }
            case "ORANGE" -> {
                System.out.println("오렌지");
                yield "orange";
            }
            default -> {
                System.out.println("없음");
                yield "default";
            }
        };
        System.out.println(fruit); //orange
    }
}
```

`yield`는 `case`문에서 키워드로 사용되지만 `변수 명`으로 사용이 가능하다.

```java
int yield = 10; //error가 나지 않는다.
```

#### if문

`if()` 괄호안의 오는 데이터(구문의 반환 값)은 boolean형으로 `true`일 때 수행하는 문법

```java
int i = 10;
if(i == 1){
    System.out.println("1");
} else if( i > 1 && i < 7) {
    System.out.println("2이상 6이하");
}
else {
    System.out.println("7이상");
}
```

### 반복문

#### for

```java
for(int i=0; i < 10; i++){
    System.out.print(i+ " ");
}

//0 1 2 3 4 5 6 7 8 9
```

기본 `for`문은 괄호 안에 구문은 `3가지`가 올 수 있으며 `초기식`, `조건 식`, `증감 식` 으로 제어가 가능하다.

#### for-each문

```java
for(int i : new int[]{0,1,2,3,4,5,6,7,8,9}){
            System.out.print(i+ " ");
}

//0 1 2 3 4 5 6 7 8 9
```

조건식이 아닌 `변수타입 변수명 : 배열/컬렉션`을 입력하면 해당 레퍼런스 데이터의 값을 처음부터 끝까지 조회가 가능하다. (컬렉션에 저장되어있는 요소들을 읽어오기 위한 `Iterator`를 통해 조회를 한다.)

#### Iterator

반복문과는 밀접한 관련은 없는 내용일 수 있지만 나온김에 정리하려고 한다.

Collection을 기반으로 각 자료구조들을 조회 하는 데 있어 데이터를 읽는 방법을 동일한 방식으로 가능하게 제공해준다. (`다형성`)

**메서드**

- hasNext() : 다음 요소가 있는지 체크 (있다면 true)

- next() : 다음 데이터 반환
- remove() : next()로 읽은 요소를 삭제

배열/컬렉션에 데이터 타입이 명시되어있기 때문에 앞의 변수타입을 `var`키워드를 사용하여 타입추론도 가능하다.

C++의 `for(auto : )`구문과 비슷하다.

#### while

C/C++과 while문은 동일하고 `while()`괄호안의 조건식이 true이면 반복문을 돌게된다.

### 분기문

#### break

기본 `switch`문에서 쓰인다면 각 `case` 구문을 중단하기 위한 구문으로 `break`가 없다면 다음 case가 이어서 실행이된다.

반복문에서 쓰인다면 `현재 코드 블럭( {} )`에 해당하는 반복문을 탈출한다.

#### continue

`while`에서 사용하면 다음 구문을 실행하지 않고 다시 처음부터 반복문을 실행하게 되며 `for`문에서 사용하면 마찬가지로 다음 구문은 실행하지 않고 처음부터 반복하게 되는데 `증감 식`을 한번 수행 후 시작한다.

설명이 애매한데 한마디로 반복문 중 conitnue를 만나면 반복문의 가장 끝으로 가는 느낌이다.

#### return

메서드 안에서 사용하며 메서드의 결과를 반환하는 구문

<br><br>

## Junit5

[/spring/Junit5.md]

<br><br>

## live-study 대시보드 만들기
https://gist.github.com/gowoonsori/409d7f2b3d79f75bbe566d760502e9db

<br>

## LinkedList

- 정수 저장하는 ListNode 클래스만들기
- add
- remove
- contains

https://gist.github.com/gowoonsori/e27cfc11b677f7936b6f55aac1500420

<br>

## Stack 구현

### int 배열 사용 정수 저장

- push
- pop
  https://gist.github.com/gowoonsori/bb28b83d36ab4ef3b07ce22c172e29fc

### ListNode사용해서 Stack구현

- push
- pop
  https://gist.github.com/gowoonsori/f897564560148ce4cb11ccacee28f6dc

<br><br>

## Queue구현

### 배열 사용
- 미구현
### ListNode사용
- 미구현