# 빌더 패턴

객체의 생성과정과 표현 방법을 분리하는 패턴으로 다음과 같은 문제를 해결할 수 있다.

1. 불필요한 생성자를 제거
1. 데이터의 순서에 상관없이 객체 생성
1. 사용자입장에서 이해하기 쉬워야한다.

## 장점

1. 필요한 데이터만 가지고 객체를 생성할때 편하다.

```java
class Person{
    private String firstName;
    private String lastName;
    private int age;
    private int height;
    private String hobby;

    public Person(String firstName) {
        this.firstName = firstName;
    }

    public Person(String firstName, String lastName) {
        this.firstName = firstName;
        this.lastName = lastName;
    }
}

public static void main(String[] args){
    //Constructor
    Person onlyFirstName = new Person("길동");
    Person onlyName = new Person("길동","홍");
    Person onlyLastName = new Person("홍"); //불가능

    //Builder
    Person onlyFirstName = Person.createBuilder()
                                    .firstName("길동")
                                    .build();
    Person onlyName = Person.createBuilder()
                                    .firstName("길동")
                                    .lastName("홍")
                                    .build();
    Person onlyLastName = Person.createBuilder()
                                    .lastName("홍")
                                    .build();
}
```

특정 필드만 포함하는 객체를 생성하려고할때 해당 생성자를 계속 만들어주어야 하며, 생성자의 파라미터 개수당 한개의 생성자만 생성이 가능하기 때문에 위 코드와 같은 방식은 불가능하지만 builder는 가능하다.

2. 유연성
   1번에서 설명한 내용과 비슷하게 로직상 특정 필드의 데이터만 가지고있는 객체를 생성하려고 할때 클래스를 수정(새로운 생성자 생성)하지 않고도 객체를 생성이 가능하다.

3. 가독성 증대

```java
//생성자
Person person = new Person("길동","홍",25,180,"음악");

//빌더
Person person = new PersonBuilder()
    .firstName("길동")
    .lastName("홍")
    .age(25)
    .height(180)
    .hobby("음악")
    .build();
```

4. 불변성을 갖는 객체를 만들기 쉽다.

```java
class Person{
    private String firstName;
    private String lastName;
    private int age;
    private int height;
    private String hobby;

    public Person() {}
    public Person(String firstName, String lastName, int age, int height, String hobby) {
        this.firstName = firstName;
        this.lastName = lastName;
        this.age = age;
        this.height = height;
        this.hobby = hobby;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public void setHobby(String hobby) {
        this.hobby = hobby;
    }
}
```

위와 같은 클래스가 있을때 객체를 생성하는 과정에서 빌더패턴과 비슷하게 아래와같이 사용할 수 있다. 아래와 같은 패턴을 `자바빈 패턴`이라고 불린다.

```java
Person person = new Person();
person.setAge(25);
person.setHeight(180);
person.setHobby("음악");
```

하지만 서비스가 멀티스레드 환경에 공유하는 객체가 필요하다라고 하면 객체가 변할수있는 상태라고 한다면 큰 문제가 될 수 있기 때문에 불변성을 만족해야 한다.

하지만 setter들로 인해 해당 객체는 언제든지 변경이 될 수 있는 상태이기때문에 클래스에서 setter는 외부에 열어두지 않는 것이 좋다. 이러한 이유로 builder패턴을 사용하면 불변성을 만족하는 객체를 생성할 수 있다.

## 단점

1. 약간의 성능이슈
   Builder를 생성하는 것도 하나의 객체를 생성하는 것이고 해당 객체가 다른 객체를 생성하는 것이기 때문에 약간의 메모리를 소비하게 된다.

1. 코드의 유지보수
   이는 대부분의 디자인패턴들의 공통적인 단점으로 관리하는 클래스들이 많아질 수 있으며 빌더를 inner 클래스에 정의해도 클래스가 길어져 가독성이 떨어질 수 있다. 또한 php와 같은 언어에서는 inner 클래스를 지원해주지 않기 때문에 사용이 불가능하다.

## @Builder

Lombok 라이브러리의 @Builder 어노테이션을 사용하면 별도의 클래스 생성없이 컴파일러가 내부클래스로 Builder를 생성해준다.

```java
class Person{
    private String firstName;
    private String lastName;
    private int age;
    private int height;
    private String hobby;

    public static Person.PersonBuilder builder() {
        return new Person.PersonBuilder();
    }

    public static class PersonBuilder{
        private String firstName;
        private String lastName;
        private int age;
        private int height;
        private String hobby;

        PersonBuilder() {
        }

        public Person.PersonBuilder firstName(final String firstName) {
            this.firstName = firstName;
            return this;
        }

        public Person.PersonBuilder lastName(final String lastName) {
            this.lastName = lastName;
            return this;
        }

        public Person.PersonBuilder age(final int age) {
            this.age = age;
            return this;
        }

        public Person.PersonBuilder height(final int height) {
            this.height = height;
            return this;
        }

        public Person.PersonBuilder hobby(final String hobby) {
            this.hobby = hobby;
            return this;
        }

        public Person build() {
            return new Person(this.firstName, this.lastName, this.age, this.height, this.hobby);
        }

        public String toString() {
            return "Person.PersonBuilder(firstName=" + this.firstName + ", lastName=" + this.lastName + ", age=" + this.age + ", height=" + this.height + ", hobby=" + this.hobby + ")";
        }
    }
}
```

다만 build()를 정의하면서 AllargumentsConstructor를 필요로 하기 때문에 원본클래스의 해당 생성자는 필수로 있어야 컴파일에러가 발생하지 않는다.

```java
public static void main(String[] args) {
    Person.Builder personBuilder = Person.builder()
                .lastName("홍")
                .firstName("길동")
                .age(25)
                .hobby("음악")
                .height(180);

    Person person1 = personBuilder.build();
    Person person2 = personBuilder.build();

    System.out.println(person1.equals(person2));    //false
}
```

## 팩토리패턴과 비교해보자

딱 봐도 사용하는 방식이 다르긴 하지만 굳이 비교를 해보자.

팩토리 메서드 패턴 : 객체를 생성하는 패턴에 있어 추상화를 적용할 수 있는 가작 간단한 패턴으로 단일 메서드를 사용하여 간단한 객체를 생성

추상 팩토리 패턴 : 여러 팩토리 메서드를 사용하여 객체 생성하며 각 메서드들은 하위 객체를 바로 리턴한다.

빌더 패턴 : 단계별로 복잡한 객체를 생성이 가능하며 각 중간단계에서의 상태를 유지하고 최종적으로 하위 객체들을 합친 최종 객체를 반환한다.

한마디로 빌더패턴은 사용자가 최종결과물을 받고 팩토리 패턴은 최종 결과물에 필요한 재료들을 받게 된다.
