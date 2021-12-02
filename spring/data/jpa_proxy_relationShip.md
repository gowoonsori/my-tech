# 프록시와 연관관계 맵핑

특정 엔티티를 조회할 때 그 엔티티에 연관된 엔티티들도 한번에 같이 조회하는 것이 아니라 실제 엔티티 객체 대신 DB 조회를 지연할 수 있는 가짜 객체를 `프록시 객체`라고 하고 이를 `지연 로딩`이라고 한다. 실제 연관된 엔티티가 있다면 JPA는 같이 조회하게 되는데 연관된 데이터의 정보가 필요가 없기도 하고 `일대다`의 맵핑이라면 한번의 조회가 아닌 `1+N`의 조회를 하기 때문에 성능상의 문제로 지연로딩을 수행해야 할 시점이 있다.

### ◾ 사용 방법

```java
Member member = em.find(Memeber.class, "member1");  //원래 조회 방법
Member member = em.getRefernece(Member.class, "member1"); //지연 로딩(프록시 객체 생성)
member.getName();  //실제 데이터를 조회할때 DB조회
```

`EntityManager.getRefernce()`메서드를 사용하면 해당 엔티티의 프록시 객체가 생성 되고 `getName()`과 같이 엔티티의 데이터를 실제로 조회하는 시점에 `영속성 컨텍스트`에 엔티티의 유무를 파악하고 없다면 그때서야 조회를 수행한다.

### ◾ 특징

- 프록시 객체는 처음 사용할 때 한 번만 초기화
- 영속성 컨텍스트에 찾는 엔티티가 존재할 시 DB조회가 아닌 실제 엔티티를 반환
- 초기화는 영속성 컨텍스트의 도움이 필요하기 때문에 `준영속`상태의 프록시를 초기화 시 `org.hibernate.LazyInitializationException`예외를 발생

### ◾ isLoaded()

```java
boolean isLoad = em.getEntityManagerFactory().getPersistenceUnitUtil().isLoaded(entity);
```

프록시 객체인 entity가 초기화가 되었는지 확인하는 메서드이다.

<br><br>

## 즉시로딩과 지연로딩

연관관계 설정시에 어노테이션(`@ManyToOne` ...)에 로딩전략을 설정할 수 있다.

```java
@Enity
public class Member{
    //...
    @ManyToOne(fetch = FetchType.EAGER)
    @JoinColumn(name = "TEAM_ID")
    private Team team;
}
```

즉시 로딩은 `FetchType.EAGER` , 지연 로딩은 `FetchType.LAZY`로 설정이 가능하고 즉시로딩시에는 대부분의 JPA구현체는 성능을 위해 `Join`으로 쿼리를 날린다.

그런데 Member는 팀이 없을 수도 있는데 inner join을 하게 되면 조회가 되지 않는 Member,Team이 있을 수도 있기 때문에 기본전략으로 외부 조인을 수행하게 된다. 별도로 `Inner join`을 수행하도록 하고 싶다면 `@JoinColumn(nullable = false)`와 같이 nullable옵션을 false로 설정하면 JPA는 null이 없다는 것을 보고 inner조인을 사용한다.

JPA구현체 중 하나인 `하이버네이트`는 엔티티를 영속 상태로 만들때 엔티티에 컬렉션(List, Map...) 이 있다면 컬렉션을 추적,관리 목적으로 원본 컬렉션을 하이버네이트가 제공하는 `내장 컬렉션`으로 변경한다.(이를 컬렉션 래퍼라고 한다.) 그래서 1:N과 같이 컬렉션 필드가 있다면 `프록시 객체`가 지연 로딩을 수행하는 것이 아니라 `컬렉션 래퍼`가 지연 로딩을 처리해준다.

<br>

### ◾ 기본 전략

- ManyToOne, OneToOne : 즉시 로딩

- OneToMany, ManyToMany : 지연 로딩

컬렉션을 즉시 로딩하는 것은 비용이 많이 들기 때문에 지연로딩을 기본 전략으로 수행한다.

> 김영한 저자는 모든 연관관계는 지연 로딩을 사용하고 개발 완료단계에서 성능 측정후 필요한 곳에 즉시 로딩을 사용하는 방법으로 최적화하는 것을 추천하고 있다.

<br><br>

## 영속성 전이

연관관계 어노테이션의 `cacade` 옵션으로 영속성 전이를 JPA는 제공한다.

```java
@Enity
public class Team{
    //...
    @OneToMany(mappedBy= "team", cascade = CascadeType.PERSIST)
    private List<Member>  members;
}
```

엔티티를 저장할때 연관된 모든 엔티티도 영속상태이어야 하기 때문에 특정 엔티티만 영속화 해도 연관된 엔티티도 같이 영속화하는 기능 이다.

저장뿐만이 아닌 삭제할때도 영속성 전이가 가능하고 제공하는 옵션은 다음과 같다.

```java
public enum CascadeType{
    ALL,        //모두 적용
    PERSIST,    //영속
    MERGE,      //병합
    REMOVE,     //제거
    REFRESH,
    DETACH
}
```

영속성 전이도 쿼리와 같이 메서드호출이 아닌 `flush`를 호출할 때 전이가 발생한다.

<br>

### ◾ 고아 객체

JPA는 부모엔티티의 컬렉션에서 참조가 끊긴 자식 엔티티를 자동으로 삭제하는 기능을 제공한다.

```java
@Enity
public class Parent{
    //...
    @OneToMany(mappedBy= "team", orphanRemoval = true)
    private List<Child>  Children;
}

//business logic
Parent parent = em.find(Parent.class, id);
parent.getChildren().remove(0);
```

마찬가지로 연관관계 어노테이션 옵션으로 설정이 가능하고 컬렉션에서 지우고 플러시를 하게 되면 자동으로 DELETE 쿼리가 실행된다. 또한, 부모를 제거하게 되면 모든 연관된 자식 객체들은 연관관계가 끊기기 때문에 모든 자식들도 지워지게 되고 이는 CascadeType.REMOVE와 동일한 기능이다.

<br><br><br>

---

## Refernece

자바 ORM 표준 JPA 프로그래밍 책 (김영한 저)
