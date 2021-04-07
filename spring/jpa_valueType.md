# 데이터 타입

## 엔티티 타입

@Entity로 정의하는 객체로 이는 `식별자`를 통해 추적,관리가 가능하다.

## 값 타입

단순히 특정 데이터의 값으로 사용되는 primitive type 이나 Reference type과 같은 타입으로 단순히 값으로 사용되는 값이다.

값 타입은 엔티티 타입의 특정 데이터들을 표시하는 타입으로 생명주기를 엔티티에 의존하고 값 타입은 영속성을 위해 공유되면 안된다.

한 데이터에서 값을 변경할 때 다른 엔티티의 값이 변경되면 안되기 때문에 불변이어야 한다. 또한, 값 타입은 동등성을 판단하기 위해 `equals/hashcode`를 구현해야 한다.

### ◾ 기본 값 타입(Basic type)

- 기본 타입 (Primitive type)
- Wrapper Class
- String

기본 타입과 String은 기본적으로 불변이고, Wrapper 클래스는 기본타입과 같이 표현할 수 있는 기능을 제공한다.

### ◾ 임베디드 타입(Embedded type)

새로운 값 타입을 직접 정의해서 사용할 수 있는 타입이고 복합키를 설정할때 `Embedded Id`를 설정한 것이 이에 해당한다.

```java
@Entity
public class Member{
    //...
    @Embedded
    Address homeAddress;
}

@Embeddable
public class Address{
    private String city;
    private String street;
    private String zipCode;
}
```

위와 같이 어노테이션으로 임베디드 타입을 생성하고 사용할 수 있으며 임베디드 타입에는 특정 의미있는 메서드를 만들어 사용할 수도 있어 재사용성과 응집도가 높다.

임베디드 타입의 관계를 UML로 표현하면 `컴포지션 관계`가 되고 하이버네이트는 `component`라고 한다.

<br>

#### @AttributeOverride

임베디드 타입에 정의한 맵핑정보를 재정의하는 어노테이션

```java
@Entity
public class Member{
    //...
    @Embedded
    @AttributeOverrides({
        @AttributOverride(name="city", column=@Column(name = "COMPANY_CITY")),
        @AttributOverride(name="street", column=@Column(name = "COMPANY_STREET")),
        @AttributOverride(name="zipcode", column=@Column(name = "COMPANY_ZIPCODE"))
    })
    Address homeAddress;
}
```

#### 문제점

```java
memeber1.setHomeAddress(new Address("old city"));
Address address = member1.getHomeAddress();

address.setCity("new city");
member2.setHomeAddress(address);
```

값 타입은 영속성을 위해 불변 객체이어야 하는데 객체이기 때문에 `setter`가 존재하면 불변성이 깨지며 위의 코드와 같이 member2의 주소정보만 변경하고 싶었지만 member1의 주소정보까지 변경되는 문제가 발생한다. (address라는 객체를 공유하기 때문)

그래서 이를 해결하기 위해서는 `clone()`메서드와 같이 값을 복사해서 사용하거나 애초에 `setter`를 없애 변경하지 못하도록 해야 부작용을 원천 봉쇄할 수 있다.

```java
Address address = member1.getHomeAddress();

Address newAddress = new Address(address.getCity());
member2.setHomeAddress(newAddress);
```

### ◾ 컬렉션 값 타입(Primitive type)

값 타입을 하나 이상 저장하기 위한 타입

```java
@Entity
public class Member{
    //...
    @ElementCollection
    @CollectionTable(name = "FAVORITE_FOODS", joinColumns = @JoinColumn(name = "MEMBER_ID"))
    @Column(name = "FOOD_NAME")
    private Set<String> favoriteFoods = new HashSet<String>();
}
```

값타입 컬렉션을 저장하려면 @CollectionTable을 이용해서 별도의 DB테이블과 맵핑해야 하고 별도의 테이블을 이용하기 때문에 삽입시 각각 insert query가 수행된다. 또한, 컬렉션도 조회시 패치 전략을 설정할 수 있고 `LAZY`가 기본이다.

값 타입은 모두 불변이기 때문에 수정하기 위해서는 삭제하고 새로 등록해야 한다.

### ◾ 문제점

값 타입은 엔티티 타입이 아니기 때문에 별도의 `식별자`로 관리 되는 것이 아니기 때문에 이 테이블의 수정사항이 발생하면 테이블에서 지우고 새로 insert하는 방법으로 수정을 한다. 이 때문에 성능에 문제가 발생할 여지가 있어서 데이터가 많다면 `1:N`관계를 고려해야 한다.

<br>

**식별자가 필요하고 지속해서 값을 추적하고 구분하고 변경해야 한다면 값 타입이 아닌 엔티티**

<br><br><br>

---

## Refernece

자바 ORM 표준 JPA 프로그래밍 책 (김영한 저)
