# 복합 키와 식별 관계 매핑

복합 키를 매핑하는데 외래키가 기본 키에 포함되는지 여부에 따라 두가지 방법(식별관계, 비식별관계)이 존재한다.


## 복합 키를 지원하기 위한 방법
복합키를 사용하기 위해 별도의 식별자 클래스를 생성해주어야 하는데 이때 `equals`와 `hashcode`를 필수적으로 생성해주어야 한다.  자바의 모든 클래스는 `Object`클래스를 상속받는데 이 클래스가 제공하는 기본 `equals`는 인스턴스 참조 값 비교인 `==`비교를 하기 때문에 아래와 같이 같은 키여도 영속성 컨텍스트는 다르게 인식하여 동등성이 지켜지지 않기 때문이다.

```java
ParentId id1 = new ParentId();
id1.setId("1");
id1.setId("2");

ParentId id2 = new ParentId();
id2.setId("1");
id2.setId("2");

id1.equals(id2); //false 일 수 있다.
```

### 1. IdClass
관계형 데이터베이스에 가까운 방법

```java
@Entity
@IdClass(ParentId.class)
public class Parent{
    @Id
    @Column(name = "PARENT_ID1")
    private String id1;

    @Id
    @Column(name = "PARENT_ID2")
    private String id2;
}

@NoArgsConstructor @AllArgsConstructor @EqualsAndHashCode
public class ParentId implements Serializable{
    private String id1;
    private String id2;
}
```
식별자 클래스의 필드명과 엔티티에서 사용하는 식별자의 필드명이 같아야 하고 아래와 같이 저장할 수 있다.

```java
Parent parent = new Parent();
parent.setId1("1");
parent.setId2("2");
parent.setName("홍길동");
em.persist(parent);
```

<br>

### 2. EmbeddedClass
객체지향에 가까운 방법

```java
@Entity
public class Parent{
    @EmbeddedId
    private ParentId id;
   
}

@Embeddable @NoArgsConstructor @AllArgsConstructor @EqualsAndHashCode
public class ParentId implements Serializable{

    @Column(name = "PARENT_ID1")
    private String id1;
    @Column(name = "PARENT_ID2")
    private String id2;
}
```
식별자 클래스에 기본키를 직접 매핑하는 방법이며, 아래와 같이 저장을 수행할 수 있다.

```java
Parent parent = new Parent();
ParentId parentId = new ParentId("1","2");
parent.setId(parentId);
parent.setName("홍길동");
em.persist(parent);
```

<br><br>

##  식별 관계 
부모 테이블의 기본 키를 받아 자식 테이블의 기본 키 + 외래키로 사용하는 관계

## 1. IdClass 
참조하는 객체를 `@Id`를 이용하여 맵핑하면 된다.

## 2. EmbeddedId
참조하는 객체를 `@MapsId`를 이용하여 맵핑하면 되고 MapsId는 외래키와 맵핑한 연관간계를 기본 키에도 매핑하겠다는 뜻이다. 해당 어노테이셔의 속성값으로 @EmbeddeId를 사용한 식별자 클래스의 기본 키 필드를 지정하면 된다.

<br>

## 일대일 식별 관계
부모 테이블의 기본키를 이용하여 자식 테이블의 키 그대로 사용하기 때문에, 복합키를 구성하지 않아도 되고 `@MapsId`를 참조하는 객체에 붙여주고 속성값은 아무것도 명시 하지 않음으로써, 자기 자신의 Id와 외래키를 맵핑하겠다고 선언해주면 된다.

```java
@Entity
public class Parent{
    @Id @GeneratedValue @JoinColumn(name="PARENT_ID")
    private Long id;

    @OneToOne(mappedBy = "board")
    private parentDetail parentDetail;
}

@Entity
public class ParentDetail{
    @Id
    private Long parentDetailId;

    @MapsId
    @OneToOne
    @JoinColumn(name="PARENT_ID")
    private Parent parent;
}
```

<br>

##  비 식별 관계
부모 테이블의 기본 키를 받아 자식 테이블의 외래키로만 사용하는 관계

### 필수적 비식별 관계
외래키에 NULL을 허용하지 않는 관계

### 선택적 비식별 관계
외래키에 NULL을 허용하는 관계

이는 복합키를 사용하지 않아도 되기 때문에 일반 연관관계 연결하듯이 하면 된다.

<br>

## 식별관계와 비식별관계에 관하여
비즈니스가 확장되어 기본 키 컬럼이 늘어날 수도 있기 때문에 확장성과 유연성이 좋은 비식별관계가 더 많이 선호 되며, JPA에는 `GeneratedValue`라는 대리키 생성 전략을 쉽게 제공한다.

하지만, 식별관계는 인덱스 없이도 `기본키 인덱스`만을 가지고 빠르게 조회가 가능한 장점이 있으니 필요한곳에 적절하게 사용해야 한다.

또한, 대리키를 사용할때는 Integer가 아닌 Long을 사용하는 것이 안전하고 비식별 관계를 사용할때는 `필수적 비식별 관계`를 사용하는 것이 좋다. (Integer는 20억개 정도, Long은 920경)

<br><br>

## 조인 테이블

### 1. 조인 컬럼 사용 (@JoinColumn)
외래키를 사용하여 조인할 수 있지만, 외래키에 null값을 허용해야하고 `inner join`을 사용시 관계가 없는 컬럼들은 조회가 되지 않는다. 처음 컬럼 생성시 대부분의 FK는 null로 저장된다.

### 2. 조인 테이블 사용 (@JoinTable)
별도의 테이블을 사용해서 연관관계를 관리하는 방법으로 사용이 단순하고 쉬우나 테이블을 하나 더 관리해야 하기 때문에 부담이 늘어나며, 조인 시에 2개가 아닌 연관관계를 관리하는 테이블까지 추가해서 3개의 테이블을 조인 해야 한다.

기본은 `조인 컬럼`으로 사용하고 필요시에 조인 테이블을 이용하자. (주로 `조인 테이블`은 다대다 / 다대일 관계에 사용된다.)

<br>

## 하나의 엔티티로 여러개의 테이블 매핑
```java
@Entity
@Table(naem="PARENT")
@SecondaryTalbe(naem = "PARENT_DETAIL",
    pkJoinColumns = @PrimaryKeyJoinColumns(name = "PARENT_DETAIL_ID"))
public class Parent{
    @Id @GenreatedValue
    @Column(name = "PARENT_ID")
    private Long id;

    private String name;

    @Column(table = "PARENT_DETAIL")
    private String address;
}
```
하나의 클래스(Entity)에서 `@Table`과 `@SecondaryTable`을 통해 두개의 테이블과 매핑시킬 수 있고, @Column의 table 필드를 지정하면 해당 테이블에 매핑되며 지정하지 않는다면 기본인 `@Table`로 명시된 테이블에 매핑이 된다.

<br><br><br>

-----
## Reference
자바 ORM 표준 JPA 프로그래밍 책 (김영한 저)