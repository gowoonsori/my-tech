# lombok (롬복)

Java 라이브러리중 하나로 도메인을 만들때마다 반복되는 getter/setter와 같은 메서드 작성 코드를 줄여주는 기능을 한다.

Lombok이 여러가지 `어노테이션`을 제공하기 때문에 어노테이션을 가지고 컴파일과정에서 해당 기능의 메서드를 생성해 주는 방식으로 동작한다.

build된 폴더에 가보면 `.class`파일이 생성된것을 볼 수 있다

<br>

## 어노테이션

- Builder : `빌더 패턴`을 사용할 수 있도록 코드를 생성해준다.

  장점 : 인자가 많을 경우 쉽고 안전하게 객체 생성 가능 / 인자 순서 상관없이 생성가능 /

  - AllargsConstructor 효과와 비슥하여 모든 멤버필드에 기본 생성자를 만들기 때문에 객체 생성시 받지 않아야 할 데이터들도 생성자가 존재해 오류에 소지가 있다.
    따라서 매개변수가 적은 클래스일때 사용하거나, 따로 받아야 하는 생성자를 조건에 따라 지정하고 그위에 @Builder를 붙이자

        ```java
        public class Member{
            @Builder
            public Member(string name){
                this.name = name;
            }
        }
        ```

- AllargsConstructor : 모든 속성에 대해 생성자를 생성
- NoArgsConstructor : 파라미터를 받지 않는 생성자 생성

  - 접근 권한을 최소화 하자 (JAP에서 프록시를 위해 기본 생성자를 하나 무조건 생성해야 하는 일이 발생하는데, Not null이어야 하는 값도 public으로 객체 생성시 null일 수 밖에 없으므로, 접근 권한을 protected이상으로 주어 null일 수 있는 것을 방지하자)

    ```java
    @NoArgsConstructor(access = AccessLevel.PROTECTED)
    ```

  - @NoArgsconstructor(AccessLevel.PROTECTED)과 @Builder를 함께 사용하면 에러가 날 것이다.

    @NoArgsconstructor로 인해 기본 생성자가 protected로 존재하여 Builder가 모든 파라미터를 받는 생성자 생성시 public의 기본생성자를 찾지 못해 에러가 발생한다.

    => 해결방법 : 1. AllArgsConstroctor를 붙여주어 public의 모든 멤버 변수를 받는 생성자를 만들어준다.

        2. 생성자 별로 멤버 변수 내용을 정의하고 생성자에 @Builder를 붙여준다.

- Getter/Setter : Getter와 Setter 생성

  - 안전성을 위해 무분별한 Setter는 남용하지 말자

- EqualsAndHashCode : 객체의 equals()와 hashcode()메소드를 생성

  - (of = "변수"|{"변수1","변수2"})와 같이 특정 변수로 비교

    : 많은 변수로 비교를 할 시 stackoverflow가 일어날 수 잇다.

- NonUll : null이 될 수 없다
- Value : 불변 클래스 생성
- ToString : toString() 메소드 생성

  - (exlude={"제외할 변수"})로 제외하여 생성 가능

- @Data : ToString, EqualsAndHashCode, Getter, Setter, RequiredArgsConstructor 어노테이션을 묶어놓은 어노테이션으로 잘 사용하지 않는다 => 순환 참조 문제로 인해 `stack overflow`가 발생할 수 있기 때문이다.

<br>

## 많이 붙은 어노테이션을 줄일 수 없을까?

커스텀 에노테이션을 아직까지는 롬복 어노테이션에서는 사용이 불가능 하다.

<br>

---

## Reference

https://cheese10yun.github.io/lombok/

백기선 님 - Spring Rest-api
