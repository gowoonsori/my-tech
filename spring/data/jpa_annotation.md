# JPA 어노테이션
## @OrderBy

컬렉션으로 되어있는 컬럼을 정렬할때 사용하는 어노테이션으로 별도의 컬럼을 추가해서 관리하는 `@OrderColumn`과 달리 이 어노테이션은 SQL문에 `order by`문을 추가해 조회하기 때문에 별도의 컬럼이 필요가 없다.

```java
@Entity
public class User{
    //...

    @OneToMany(mappedBy = "user")
    @OrderBy("id asc", "price desc")
    private List<Order> orders = new ArrayList<>();
}
```

<br>

## @Converter

엔티티의 데이터를 변환해서 DB에 저장하고 조회할 수 있는 어노테이션

```java
@Entity
public class User{
    //...

    @Converter(converter = BooleanToYNConverter.class)
    priavate boolean admin;
}

@Converter
public class BooleanToYNConveter implements AttibuteConveter<Boolean, String>{
    @Override
    public String converterToDatabaseColumn(Boolean attr){
        return (attr != null && attr) ? "Y" : "N";
    }

    @Override
    public Boolean convertToEntityAtrribute(String data){
        return "Y".equals(data);
    }
}
```

AttributeConverter을 implementes하여 두메서드를 구현하면되는데 이름 그대로 `convertToDatabaseColumn()`은 엔티티의 데이터를 DB에 저장하기 위해 바꾸는 메서드이고 `convertToEntityAttribute()`는 반대로 DB의 데이터를 엔티티의 데이터에 맞게 변환해주는 메서드이다.

@Converter(autoApply=true)와 같이 옵션으로 글로벌 옵션을 적용할 수도 있다.

<br>

## 리스너

엔티티의 생명주기에 특정 이벤트를 수행할 수 있게 등록하는 어노테이션

| 어노테이션 이름 |                                                                          기능                                                                           |
| :-------------: | :-----------------------------------------------------------------------------------------------------------------------------------------------------: |
|   @PrePersist   |                                                                   persist 직전(merge)                                                                   |
|   @PreUpdate    |                                                                    flsuh/commit 직전                                                                    |
|   @PreRemove    |                                                           remove 직전(영속성 전이시에도 호출)                                                           |
|    @PostLoad    |                                                                조회된 직후(refresh 직후)                                                                |
|  @PostPersist   | 엔티티를 DB에 저장 직후에 호출되며 생성전략이 idenetity라면 식별자 생성을 위해 persist()를 호출하면서 DB에 엔티티르 저장하기 때문에 이 persist이후 호출 |
|   @PostUpdate   |                                                          flush/commit을 통해 DB에 수정한 직후                                                           |
|   @PostRemove   |                                                          flush/commit을 통해 DB에 삭제한 직후                                                           |

```java
@Entity
public class User{
    //...

    private LocalDateTime createdAt;

    @PrePersist
    private void onPersist(){
        this.createdAt = LocalDateTime.now();
    }
}
```

리스너들이 존재하는 별도의 클래스를 만들어서 `@EntityListeners(리스너클래스이름.class)` 어노테이션을 엔티티에 달아주면 해당 엔티티에서 분리된 별도의 리스너를 사용할 수 있다.

<br>

## 엔티티 그래프

### @NamedEntityGraph

```java
@NamedEntityGraph(name = "Order.withMember", attributeNodes = {
    @NamedAttributeNode("member")
})
@Entity @Table(name = "ORDERS")
public class ORDER{
    //...
}

EntityGraph graph = em.getEntityGraph("Order.withMember");
Map hints = new HashMap();
hits.put("javax.persistence.fetchgraph", graph);

Order order = em.find(Order.class, orderId, hints);
```

JPQL의 페치조인 없이 JPA의 힌트 기능을 사용해서 엔티티 그래프를 사용해 한번에 조회하는 방법이다.

```java
@NamedEntityGraph(name = "Order.withAll", attributeNodes = {
    @NamedAttributeNode("member"),
    @NamedAttributeNode(value = "orderItems", subgraph = "orderItems")},
    subgraphs = @NamedSubgraph(name = "orderItems", attributeNode = {
        @NamedAttributeNode("item")
    })
)
```

연관관계의 연관관계를 조회하고자 한다면 subgraph를 이용해 조회할 수 도 있다.

직접 JPQL문을 작성하는 것과는 다르게 설정만 해두면 간단하게 조회를 할 수 도 있을 것 같긴한데 뭔가 JPQL이 더 나은 것 같기도하다.
