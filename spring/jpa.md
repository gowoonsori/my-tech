# JPA

Java Persistence API약자로 객체와 RDB간에 맵핑 시켜주는 `인터페이스`의 모음이다. 즉, 특정기능을 수행하는 라이브러리가 아니라 명세이다.

# Hibernate

JPA의 구현체로, 인터페이스인 JPA를 구현한 class같은 것.

JPA를 사용하기 위해 반드시 Hibernate를 사용할 필요가 없고 다른 JPA구현체를 사용해도 되며, 직접 JPA를 구현햏서 사용할 수도 있다.

# Spring Data JPA

Spring에서 제공하는 모듈 중 하나로 개발자가 JPA를 좀더 편하게 사용할 수 있게 도와주기 위해 Repository라는 인터페이스를 제공 (JPA를 추상화 시킨것)

Repository인터페이스 규칙대로 메서드를 작성하면 Spring이 알아서 JPA를 이용하여 적합한 쿼리를 날리는 구현체를 만들어 BEAN으로 등록 해주는 것.

## 동작과정

앱과 JDBC 사이에서 동작하며, JPA를 사용시 JPA내부에서 JDBC API를 사용해 DB와 통신을 한다.

## 저장/조회 과정

JPA에게 객체를 넘기면 JPA는 엔티티를 분석하여, SQL문을 생성하고 이를 JDBC API가 DB에 날리고 결과를 객체에 매핑시킨다.

## 장점

- SQL의 코드 반복을 줄여주고, CRUD를 간단하게 할 수 있어 생산성과 유지보수가 용이하다.

- 객체와 RDB간의 모델링이 달라 발생하는 패러다임 불일치를 해결할 수 있다.

  (객체는 단방향의 상속관계와 참조를 통한 연관관계를 갖고 RDB는 상속관계가 없이 테이블간의 슈퍼-서브 타입관계의 양방향 연관관계를 갖는다.)

- 동일한 트랜잭션 안에서는 같은 엔터티를 반환하여 캐싱기능과 동일성을 보장한다.

- 트랜잭션을 commit할때까지 쓰기 지연(버퍼링)을 지원하여 한번에 SQL문을 보낼 수 있다.

- 객체가 실제로 사용될 때 로딩하는 지연 로딩을 사용할 수 있다.

## 사용법

Entity에서 Spring Data JPA에서 제공하는 JpaRepository인터페이스를 상속하기만 해도 되어, 인터페이스에 따로 @Repository를 추가할 필요가 없다.

상속받을 때는 JpaRepository<T,ID>의 형태로 Entity의 클래스와 ID값이 들어가게 된다.

### 기능

- save() : 레코드 저장 (INSERT, UPDATE)
- findOne() : primary key로 레코드 찾기
- findAll() : 전체 레코드 불러오기 ( sort, pageable )
- count() : 레코드 갯수
- delete() : 레코드 삭제

위의 기능을 제외한 기능은 메서드를 추가하여 사용 할 수 있으며, 명명 규칙은 Refernece를 참조하자.

- findBy~ : 쿼리를 요청하는 메서드
- countBy~ : 쿼리 결과 레코드 수를 요청하는 메서드

메서드의 반환형이 Entity객체이면 하나의 결과, List이면 모든 객체를 전달

---

## Reference

https://docs.spring.io/spring-data/jpa/docs/1.10.1.RELEASE/reference/html/#jpa.sample-app.finders.strategies

https://docs.jboss.org/hibernate/orm/5.4/userguide/html_single/Hibernate_User_Guide.html
