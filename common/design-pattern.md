# 디자인 패턴

[위키백과](https://ko.wikipedia.org/wiki/%EC%86%8C%ED%94%84%ED%8A%B8%EC%9B%A8%EC%96%B4_%EB%94%94%EC%9E%90%EC%9D%B8_%ED%8C%A8%ED%84%B4)에 따르면 소프트웨어 공학에서 s/w 디자인에서 특정 문맥에서 공통적으로 발생하는 문제애 대해 재사용 가능한 해결책이라고 한다.

즉, 좋은 코드를 설계하기 위한 설계 디자인 방법론

> 좋은 코드란?
>
> 확장과 수정에 용이하여 유지보수 비용이 적게들어가는 코드로 객체간의 응집도는 높고 결합도는 낮은 코드

<br><br>

## SOLID 원칙

객체지향 방법론에서의 좋은 코드 설계를 위한 원칙

- Single Responsibility Principle : 단일 책임 원칙

  - 클래스나 함수는 하나의 기능(책임)만 가져야 한다.

- Open-Closed Priniple : 개방 폐쇄 원칙

  - 변경에는 닫혀있고, 추가나 확장에는 열려있어야 한다.

- Liskov Substitution Principle : 리스코프 치환 원칙

  - 자식 클래스는 부모클래스에서 가능한 행위를 수행가능해야 한다. ( 파생클래스를 만들때, 올바른 상속 관계인가? )

- Dependency Iversion Principle : 의존 역전 원칙

  - 자신보다 변화하기 쉬운것에 의존하지 않고 어려운것에 의존해야 한다. (추상 클래스나, 인터페이스에 의존)

- Interface Segreation Principle : 인터페이스 분리 원칙
  - 클라이언트가 자신이 이용하지 않는 메서드에 의존하지 않아야 한다. (필요한 메서드만 이용)

<br><br>

## GoF(Gang of Four) 디자인 패턴

|                   생성 패턴                   |     구조 패턴     |               행동 패턴               |
| :-------------------------------------------: | :---------------: | :-----------------------------------: |
|            [Singleton](#Singleton)            |      Adapter      |               Strategy                |
|      [Factory Methods](#Factory-Method)       |      Bridge       | [Template Methods](#Template-Methods) |
| [Abstract Factory Methods](#Abstract-Factory) |     Composite     |               Observer                |
|              [Builder](#Builder)              |     Decorator     |                 State                 |
|            [Prototype](#Prototype)            | [Facade](#Facade) |                Command                |
|                                               |     Flyweight     |                Visitor                |
|                                               |  [Proxy](#Proxy)  |              Interpreter              |
|                                               |                   |         [Iterator](#Iterator)         |
|                                               |                   |               Mediator                |
|                                               |                   |                Memento                |
|                                               |                   |        Chain of Responsibiltiy        |

<br><br>

## 생성 패턴

### Abstract-Factory

추상 팩토리

많은 수의 연관된 서브 클래스를 특정 그룹으로 묶어 한번에 교체 할 수 있도록 만드는 것

<br>

### Factory-Method

객체를 만들어 반환하는 함수를 제공하여 초기화 과정을 외부에서 보지 못하게 숨기고 반환 타입을 제어하는 방법 (단일 책임 원칙을 위반할 쉬 있다.)

방법

- 아예 다른 객체를 직접 만들어 넘겨주는 객체를 따로 만드는 방법
- 팩토리 기능을 수행하는 함수가 자기 자신에 포함되어 있고, 생성자 대신 사용하는 방법

<br>

### Builder

인스턴스를 생성자를 통해 직접 생성하지 않고 빌더라는 내부 클래스를 통해 간접적으로 생성하게 하는 패턴

목적

- 클래스와 사용대상의 결합도를 낮추기 위해
- 생성자에 전달하는 인수에 의미 부여를 위해

<br>

### Prototype

원본을 만들어 놓고 원본 객체를 복사하여 사용하는 방식

<br>

### Singleton

클래스의 객체를 하나만 만들어야 하는 경우에 사용 (하나의 인스턴스만 갖는 경우)

생성자를 클래스 자체 내부에서만 사용할 수 있도록 private,final등으로 접근 제한을 해야 다른 곳에서의 접근을 막아야 한다.

구현 방법

- Eager Initialization (사전 초기화) : 클래스 로딩시에 인스턴스를 생성하는 방법 ( 클래스 내부에서 인스턴스를 생성)

  인스턴스를 실제로 사용하지 않는다몀 불필요한 연산과 메모리 낭비

- Lazy Initialization (지연 초기화) : 인스턴스를 실제로 사용할 시점에서 인스턴스를 생성하는 방법으로 인스턴스를 실제로 사용하지 않는다면 메모리와 연산량을 아낄 수 있으나 이중 객체 생성 문제 발생할 가능성이 높다.

<br><br>

## 구조 패턴

### Facade

복잡한 호출과정을 대신 처리해주는 wrapper객체를 따로 만드는 것으로 함수 호출 비용을 줄이거나 쉽게 사용 가능하게 해준다.

여러 클래스를 감싼 클래스 생성

하위 모듈을 건드릴 수 없는 외부 라이브러리나 추상화 계층을 구분하고 싶거나, 크로스플랫폼 기술 구현등의 이유로 객체를 따로 만들어 이용

<br>

### Proxy

연산을 수행 할때 객체 스스로가 직접 처리하지 않고 중간에 다른 `숨겨진` 객체를 통해 처리하는 방법

<br><br>

## 행위 패턴

### iterator

반복자라는 뜻으로 객체지향언어에서 가장 접하기 쉬운 패턴이고 고전적인 패턴이다.

index를 통해 자료구조를 접근하지 못할때, 반복자를 사용하고 이는 인터페이스로 미리 정의 해둔 메서드들의 집합.

```java
Iterator<Object> iterator = collection.iterator();
while(iterator.hasNext() == true) {
  Object object = iterator.next();
  object.doSomething();
}
```

for문을 통한 접근이 가능하다면 for문이 더 빠르다. (캐시 메모리의 효과를 많이 받기 때문)

<br>

### Template-Methods

전체적인 레이아웃을 통일시키지만 상속받는 클래스가 유연성을 가질 수 있게 만드는 패턴

<br><br><br>

---

## Reference

https://dailyheumsi.tistory.com/148

https://namu.wiki/w/%EB%94%94%EC%9E%90%EC%9D%B8%20%ED%8C%A8%ED%84%B4#s-3.1
