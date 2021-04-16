## N+1 문제

즉시로딩이던지 지연로딩이던지 문제는 발생한다.

### 즉시로딩

Memeber와 Order가 1:N의 관계를 맺고있다고 했을때 `em.find(Member.class,id)`와 같은 메서드를 이용한다면 JOIN을 통한 SQL문이 실행되면서 문제없이 한번에 로딩이 된다.

```java
em.createQuery("select m from Member m", Memeber.class).getResultList();
```

하지만 위와같이 JPQL을 이용할때 위와같은 JPQL을 가지고 SQL문을 생성하기 때문에 `select * from member`로 member를 한 번 조회하고 memberid를 외래키로 연관된 order컬럼들을 N번 조회를 하게 되는 N+1 문제가 발생한다.

<br>

### 지연로딩

```java
em.createQuery("select m from Member m", Memeber.class).getResultList();
```

위와같이 JPQL을 사용하면 처음의 Member만 조회하고 Order 리스트는 프록시로 갖고있기 때문에 SQL문은 한번만 실행되지만 `getOrder()` 모든 Order를 조회하고자 한다면 이 또한 N번 실행되며 N+1 문제가 발생한다.

N+1은 ORM이라면 DB와 객체라는 특성상의 괴리로 발생하는 대표적인 문제이다.

<br><br>

### 해결방법

#### 1. 패치 조인 사용

JPQL의 `join fetch`를 이용해 명시적으로 즉시로딩을 수행하면 N+1문제가 발생하지 않는다. (일대다 관계에서 조인을 해서 즉시로딩으로 가져오면 1의 중복된 결과데이터가 나타날 수 있기 때문에 JPQL의 distinct를 사용하는 것이 좋다.)

#### 2. @BatchSize

하이버네이트가 제공하는 어노테이션을 이용하여 한번에 연관된 데이터를 조회할 개수를 지정할 수 있다.

IN절을 이용하여 지정한 사이즈 개수만큼의 데이터를 가져오는 SQL문을 생성해서 가져오고 즉시로딩으로 설정이 되어있다면 `실제 데이터 개수 / BatchSize` 만큼의 SQL문이 실행되기 때문에 N+1문제를 어느정도 완화가 가능하다.

지연로딩이라면 In절을 이용해 BatchSize만큼의 데이터를 한번 조회하고 그 다음을 조회하려고 할때 그 이후의 BatchSize만큼의 데이터를 다시 조회한다.

#### 3. @Fetch(FetchMode.SUBSELECT)

연관관계를 갖는 컬럼에 패치모드를 SUBSELECT로 설정하면 JPQL의 where절이 In 내부의 sub쿼리로 수행되어 데이터를 한번에 가져온다.

```sql
-- SQL
select m from Member m where m.id > 10

-- JPQL
select o from orders o
    where o.member_id in (
        select m.id
        from member m
        where m.id > 10
    )
```

<br><br>

## 읽기전용 쿼리 최적화

수정, 조회도 다시 안할 단순 보여주기용의 대용량 읽기 쿼리의 같은 경우는 읽기전용으로 엔티티 조회시 메모리사용량을 최적화 할 수 있다.

```sql
--JPQL
select o from Order o
```

### 1. 스칼라 타입으로 조회

```sql
select o.id, o.name, o.price from Order P
```

스칼라 타입은 영속성 컨텍스트가 결과를 관리하지 않는다.

### 2. 쿼리 힌트 사용

하이버네이트가 제공하는 readOnly힌트를 이용해서 읽기전용으로 조회할 수 있다.

```sql
TypedQuery<Order> query = em.createQuery("select o from Order o", Order.class);
query.setHint("org.hibernate.readOnly",true);
```

### 3. 읽기 전용 트랜잭션 사용

`@Transaction(readOnly = true)`옵션을 이용하면 하이버네이트 세션의 플러시 모드를 `MANUAL`로 설정해서 강제로 플러시를 호출 하지 않는 한 플러시가 일어나지 않아 스냅샷과 같은 로직을 수행하지 않기때문에 성능이 향상된다.

하지만, 트랜잭션 시작, 로직 수행, 커밋의 과정은 이루어진다.

### 4. 트랜잭션 밖에서 읽기

`@Transaction(propagation = Propagation.NOT_SUPPORTED)`옵션을 이용하면 아예 트랜잭션 없이 조회를 수행하기 때문에 커밋 자체를 수행하지 않는다.

<br>

메모리를 최적화하기 위해서는 1,2와 같은 방법을 이용하고 플러시/커밋을 막아 속도를 최적화하려고한다면 3,4번의 방법을 이용하면 된다.

<br><br><br>

---

## Reference

자바 ORM 표준 JPA 프로그래밍 책 (김영한 저)
