# Transaction Script와 Domain Model

비즈니스 로직을 처리하는 두가지 패턴방법이다.

## Transaction Script

(메서드 와 같은 것의)책임소재를 사용자가 작성하는 코드 로직에 두는 방식으로 하나의 트랜잭션 안에서 필요한 모든 로직을 수행하는 패턴

> 트랜잭션?
>
> 데이터의 상태를 변환시키는 하나의 논리적 기능을 수앻하기 위한 작업들,단위,연산

구현이 쉽고 단순하지만 구조가 복잡하질 수록 모듈화가 복잡해지지만, 하나의 모듈에서만 구현,사용될 경우에 부작용(side effect)를 예방할 수 있다.

```java
Student student = loadStudent("홍길동");
School school = loadSchool("S대");

...

if(student.getSchoolName() == school.getName())
    return true;
```

<br>

## Domain Model

책임소재를 객체 자체의 모델링에 두는 방식으로 각 객체에 객체가 수행해야 하는 업무를 분담시키는 방식

데이터와 프로세스가 같이 존재하며, 객체간의 관계를 맺을 수 있어 로직의 단순화에 도움이 되고 상속과 같이 유연성이 높아져 모듈화가 간단해진다.

하지만, 객체들간의 모델 설계/구축이 필요하고 객체간의 의존성(dependency)를 맺고 있어 제약사항이 될 수 도 있다.

```java
if(student.isBelongTo(school))
    return true;
```
