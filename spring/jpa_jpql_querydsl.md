# 객체지향 쿼리

지금까지 사용했던 식별자 조회, 객체 그래프 탐색하는 방법의 문제점으로 특정 조건의 쿼리를 수행할때 메모리에 모든 회원을 올려놓고 특정 조건을 검색하는 것은 많이 무리가 있다.

그래서 SQL로 필터링을 해서 조회를 해야 하는데 테이블이 아닌 엔티티 객체를 대상으로 쿼리언어를 작성 할 수 있는 언어가 `JPQL` 이고 이를 편하게 사용하도록 도와주는 API,프레임워크로 `Criteria 쿼리/QueryDSL`등이 있다.

Criteria는 문자열로 작성하는 JPQL의 문제점을 해결해 주지만 코드가 너무 복잡하고 장황해서 직관적이지 ㅁ않고 가독성이 떨어지고 QueryDSL은 오픈소스 프로젝트로 현재 많이 사용하는 프레임워크 이다.

<br>

## JPQL

SQL을 추상화한 엔티티 객체를 조회하는 객체지향 쿼리로 특정 DB에 의존하지 않는다. (Dialect만 변경하면 DB에 맞게 자동으로 변경)

묵시적 조인, 다형성등 지원으로 SQL보다 코드가 간결하다.

<br>

### ◾ 쿼리 생성

```java
String jpql = "selct m from Member as m where m.username = 'kim'";
List<Member> result = em.createQuery(jpql, Member.class).getResultList();
```

쿼리 String의 SQL 키워드가 아닌 엔티티와 속성은 대소문자를 구분하고 별칭을 꼭 사용해서 작성해야 한다. 별칭을 작성하지 않으면 잘못된 문법이라는 오류가 발생한다. (JPA구현체로 Hiberante를 사용하면 별칭 없이 사용도 가능)

<br>

`createQuery()`를 이용해서 쿼리를 실행할 수 있고 반환 타입에 따라 인자가 달라진다.

#### TypedQuery

반환타입을 명확하게 지정할 수 있을 때 사용

```java
String jpql = "selct m from Member m";
TypedQuery<Member> query = em.createQuery(jpql, Member.class);
List<Member> result = query.getResultList();
```

createQuery 두번째 인자로 맵핑할 클래스를 지정하면 된다.

<br>

#### Query

반환타입이 명확하지 않을 때 사용

```java
String jpql = "selct m.username, m.age from Member m";
Query query = em.createQuery(jpql);
List result = query.getResultList();
```

별도의 두번째 인자를 지정하지 않으면 Query 객체를 이용하면 되고 `Object`형을 반환하기 때문에 사용할때 특정 타입에 맞게 형변환을 해주어야 한다.

<br>

### ◾ 결과 조회

- getResultList : 결과를 List로 반환하고 결과가 없으면 빈 컬렉션을 반환한다.
- getSingleResult : 결과가 하나일 때 사용하며 결과가 없으면 `javax.persistence.NoResultException`이 발생하고 1개보다 많다면 `javax.persistence.NonUniqueResultException`이 발생한다.

<br>

### ◾ 파라미터 바인딩

String으로 특정 sql을 작성하는 것은 sql인젝션의 위험이 존재하고 SQL문을 재사용하지 못하기 때문에 성능상 문제가 있어 파라미터 바인딩방식을 거의 필수로 작성하는 것이 좋다.

#### 이름 기준

```java
List<Member> members = em.createQuery("select m from Member m where m.username = :username", Member.class)
    .setParameter("username","user1")
    .getResultList();
```

#### 위치 기준

```java
List<Member> members = em.createQuery("select m from Member m where m.username = ?1", Member.class)
    .setParameter(1,"user1")
    .getResultList();
```

<br>

### ◾ 프로젝션

SELECT 문으로 조회할 대상을 지정하는 것을 `프로젝션`이라고 한다.

`엔티티 타입`은 영속성 컨텍스트에 의해 관리 되고 `값 타입`은 영속성 컨텍스트에서 관리되지 않는다.

```java
public class UserDto{
    private String username;
    private int age;
    //... 생성자 ,getter,setter
}

//Business logic
TypedQuery<UserDto> query = em.createQuery("select new example.jqpl.UserDto(m.username, m.age) from Member m",UserDto.class);
List<UserDto> result = query.getResultList();
```

특정 필드만 조회하려고 하면 타입을 지정할 수 없기 때문에 Query로 조회해서 Object로 받아 변환하는 과정을 거쳐야 하는데 과정이 너무 지루하기 때문에 실제 비즈니스로직에서는 Dto를 많이 사용하게 되고 이런 Dto를 `new`명령어로 바로 맵핑시켜줄 수 있다. 이때, 꼭 패키지명을 포함한 클래스명을 입력해야 하고 순서과 타입이 일치한 생성자가 필요하다.

<br>

### ◾ 페이징

각 DB별로 페이징을 수행하는 문법이 다르기 때문에 이를 쉽게 사용하기 위한 api를 JPA는 제공한다.

#### setFirstResult

조회 시작 위치로 0부터 시작한다.

#### setMaxResults

조회할 데이터 수

```java
TypedQuery<Member> query = em.createQuery("select m from member m order by m.username desc", Member.class);

query.setFirstResult(10);
query.setMaxResults(20);
query.getResultList();
```

<br>

### ◾ Join

SQL문과 문법이 거의 비슷하나 JOIN시에 JOIN하는 엔티티를 연관 필드를 사용해서 표현한다.

```sql
select Member m join Team t     //에러
select Member m join m.team t   //성공
```

Join을 작성하지 않아도 연관관계의 엔티티내부의 필드값을 Jpql문에 이용하면 묵시적으로 inner join이 이루어진다. 하지만 컬렉션까지는 경로탐색이 가능하지만 컬렉션 내부의 필드에 접근하려고 하면 에러가 발생하기 때문에 조인을 사용해서 새로운 별칭을 획득해야 한다.

```sql
//jqpl
select o.member.team
from Order o
where o.product.name = 'productA' and o.address.city = 'JINJU'

//바뀐 sql
select t.*
from Orders o
inner join Member m on o.member_id = m.id
inner join Team t on m.team_id = t.id
inner join Product p on o.product_id = p.id
where p.name = 'productA' and o.city = 'JINJU'
```

```sql
select t.members.username from Team t //컬렉션 내부의 필드 탐색 시error
select m.username from Team t join t.members m //성공
```

N:1의 관계에서 연관필드의 id를 이용해 조회를 하는 것은 N의 엔티티가 FK를 가지고 있기 때문에 묵시적 조인이 이루어지지 않는다.

<br>

#### Inner join 예시

Inner은 생략해서 작성이 가능하다.

```java
String query = "Select m from member m inner join m.team t where t.name = :teamName";

List<Member> members = em.createQueyry(query, Member.class)
    .setParameter("teamName","팀A")
    .getResultList();
```

<br>

#### Outer join 예시

outer은 생략 가능하다.

```java
String query = "Select m from member m left outer join m.team t";

List<Member> members = em.createQueyr(query, Member.class)
    .getResultList();
```

<br>

#### 세타 조인

내부 조인만 지원하며 Cross Join을 이용하기 때문에 연관관계가 없는 엔티티도 조인할 수 있다.

```sql
//jpql
select count(m) from Member m, Team t where m.username = t.name

//sql
select count(M.ID)
from Member M cross join Team t
where M.username = t.name
```

<br>
<br>

### ◾ fetch join

JPQL에서 성능 최적화를 위해 제공하는 기능으로 연괸된 엔티티나 컬렉션을 한번에 같이 조회하는 기능으로 `join fetch`으로 조인하면 된다.

JPA는 원래 패치조인은 별칭을 사용할 수 없지만 `hiberante`는 별칭을 사용할 수 있다.

컬렉션을 패치 조인하면 페이징 api를 사용할 수 없다. 실제로는 사용할 수 있지만 경고로그를 남기고 데이터가 많아지면 성능 이슈와 메모리 초과 예외가 발생할 수 있다.

```java
String jqpl = "select t form Team t join fetch t.members where t.name = '팀A'";
List<Team> teams = em.createQuery(jpql,Team.class).getResultList();

for(Team team : teams){
    System.out println("----" + team.getName()+ "-----");
    for(Member member : team.getMembers()){
        System.out.println(member.getUsername());
    }
}
```

패치조인을 이용해서 한번에 조회하기 때문에 지연로딩이 발생하지 않는다.

<br>

#### 일반 조인과 차이

```sql
//내부 조인 JPQL
select t
from Team t join t.members m
where t.name = '팀A'

//내부 조인 사용시 SQL
SELECT T.*
FROM TEAM T
INNER JOIN MEMBER M ON T.ID = M.TEAM_ID
WHERE T.NAME = '팀A'

//패치 조인 JQPL
select t
from Team t join fetch t.members m
where t.name = '팀A'

//패치 조인 사용시 SQL
SELECT T.*, M.*
FROM TEAM T
INNER JOIN MEMBER M ON T.ID = M.TEAM_ID
WHERE T.NAME = '팀A'
```

일반 조인 사용하는데 연관필드의 로딩전략이 지연로딩이라면 JPQL의 수행 결과는 프록시나 초기화안된 컬렉션 래퍼를 반환하기 때문에 사용시점에 한번더 쿼리를 실행하게 된다.

바뀐 SQL을 봐도 일반 조인은 Member의 정보가 빠져있는 것을 볼 수 있다.

**글로벌 전략은 지연로딩을 사용하고 최적화가 필요한 부분에 패치조인을 적용하는 것이 효과적**

<br>

### ◾ distinct

```java
String jqpl = "select distinct t from Team t join fetch t.members where t.name = '팀A'"
```

1:N의 의 관계에서 패치조인시에 distinct를 사용하면 1차적으로 SQL문에 distinct문을 삽입해서 중복 데이터를 걸러주고 데이터가 넘어온 애플리케이션단에서 distinct명령어를 보고 또 한번 중복된 데이터를 걸러내기 때문에 Team엔티티 정보가 중복되어 저장하는 것을 방지할 수 있다.

<br>

### ◾ 서브 쿼리

SQL의 서브 쿼리처럼 사용이 가능한데 WHERE, HAVING절에만 사용이 가능하고 SELECT,FROM절에는 사용이 불가능하다.

hibernate는 SELECT 절에도 사용이 가능하다.

<br><br>

## QueryDSL

라이브러리를 추가하고 compile을 진행하면 target/gernerated-sources/ 위치에 Q로 시작하는 쿼리 타입들이 생성되고 이 쿼리타입을 이용해 entity에 접근해 쿼리를 수행할 수 있다.

쿼리 타입은 사용하기 편하도록 기본 인스턴스를 저장하고 있으나 같은 조인을 조인할때는 별칭이 겹치기 때문에 직접 지정해서 사용해야한다.

```java
public class QMember extends EntityPathBase<Member>{
    public static final QMember member = new QMember("member");
}//이렇게 기본적으로 기본 인스턴스를 보관하고 있다.

QMember member = QMember.member;    //기본 인스턴스 사용
QMember member = new QMember("m")   //직접 별칭 지정
```

### ◾ 기본 사용법

```java
JPAQuery query = new JPAQuery(em);
QMember member = QMember.member;

List<Member> result = query.from(member).where(member.username.eq("kim").and(member.age.gt(21))).list(member);
```

JPAQuery 객체와 쿼리타입을 이용해서 쉽게 쿼리를 이용가능 하며 체인형식으로 한눈에 보기 쉽게 쿼리를 작성이 가능하다.

where절에는 and,or을 이용가능하고 값 비교연산시에는 `eq, gt, lt`메서드를 이용할 수 있다. 또한 `between, contains, startsWith`와 같은 검색도 가능하다.

### ◾ 결과 조회

- uniqueResult() : 조회 결과가 한 건일 때 사용하고 결과가 없다면 null, 한개 이상이라면 `NonUniqueResultException`을 발생 시킨다.

- singleResult() : uniqueResult와 같지만 결과가 하나 이상이라면 처음 데이터를 반환한다.
- list() : 결과가 하나이상일때 사용하고 결과가 없다면 빈 컬렉션을 반환한다.

### ◾ 페이징

```java
JPAQuery query = new JPAQuery(em);
QMember member = QMember.member;

SearchLists<Member> result = query.from(member)
        .where(member.username.eq("kim").
            and(member.age.gt(21)))
        .orderBy(member.age.desc(), member.username.asc())
        .offset(10).limit(20)
        .listResults(member);

long total = resutl.getTotal();
long limit = resutl.getLimit();
long offset = resutl.getOffset();
List<Member> results = result.getResults();
```

`offset()`,`limit()`으로 쉽게 페이징을 처리할 수 있고 list가 아닌 listResults를 실행해야 전체 데이터 조회를 위한 `count` 쿼리가 한 번더 실행되 진짜 페이징을 처리할 수 있다.

그러면 반환값도 `SearchResults`가 되고 이 객체에서 전체 데이터 수 등을 조회할 수 있다.

### ◾ Join

첫번째 파라미터로 조인 대상을 지정하고 두번째 파라미터로 별칭으로 사용할 쿼리타입을 지정하면 된다.

innerJoin, leftJoin, rightJoin, fullJoin을 사용할 수 있고 fetchJoin도 사용가능하다.

```java
QOrder order = QOrder.order;
QOrderItem orderItem = QOrderItem.orderItem;

query.from(order)
    .leftJoin(order.orderItems, orderItem).fetch()
    .on(orderItem.count.gt(2))
    .list(order)
```

### ◾ 서브 쿼리

`JPASubQuery`를 새로 생성하여 사용할 수 있다.

```java
QItem item = QItem.item;
QItem itemSub = new QItem("ItemSub");

query.from(item)
    .where(item.in(
        new JPASubQuery().from(itemSub)
            .where(itemSub.price.eq(10000))
            .list(itemSub)
    )
    .list(item);
```

### ◾ 프로젝션에따른 반환 타입

#### 프로젝션이 한개

해당 프로젝션에 해당하는 타입으로 반환된다

```java
List<String> result = query.from(item).list(item.name);
```

#### 프로젝션이 여러개

여러 필드를 선택하면 기본적으로 Tuple이라는 Map과 비슷한 QueryDSL 내부타입을 사용한다.

```java
List<Tuple> result = query.from(item).list(item.name, item.price);
```

Map과 비슷하기 때문에 `get()`메서드를 통해 key로 값에 접근할 수 있다.

#### DTO로 반환

프로젝션이 여러개일때 DTO와 같은 객체로 받고 싶다면 `빈 생성`기능을 이용할 수 있다.

```java
List<ItemDto> result = query.from(item).list(
    Projections.bean(ItemDto.class, item.name.as("username"), item.price));
```

Projections.bean() 메소드를 이용해서 맵핑시킬 수 있으며 해당 메소드는 첫번째 매개변수의 클래스타입의 `setter`를 이용해서 값을 채우기 때문에 setter가 존재해야 하고 쿼리결과와 맵핑할 필드이름이 다르다면 `as`를 사용해서 맵핑할 수 있다.

#### 수정, 삭제 배치 쿼리

한번에 여러개의 데이터를 수정,삭제할 수 있는 배치 기능을 제공한다.

```java
QItem item = QItem item;
JPAUpdateClause updateClause = new JPAClause(em,item);
long count = updateClause.where(item.name.eq("시골개발자의 JPA 책")).set(item.price, item.price.add(100)).execute();
```

삭제도 JPADeleteClause를 사용하여 배치쿼리를 이용가능 하고 반환값으로 배치수행한 컬럼의 개수를 반환한다.

#### 동적 쿼리

BooleanBuilder 를 사용하면 동적쿼리를 생성할 수 있다.

```java
BolleanBuilder  builder = new BooleanBuilder();
builder.and(item.name.contains("가"));
builder.and(item.price.gt(10000));

query.from(item)
    .where(builder)
    .list(item);
```

<br><br>

## Native SQL

특정 DB에 종속된 문법같은 기능을 사용할때는 네이티브SQL을 이용할 수 있다.

`em.createNativeQuery(sql문, 결과 클래스)`와 같이 이용 할 수 있고 sql문법은 일반 SQL문법을 이용한다. 문법이 SQL문법으로 바뀌었을 뿐이지 그 외의 사용법은 JPQL과 같다.

## 벌크 연산시 주의점

한번에 여러개의 데이터를 수정,삭제를 수행할때는 `영속성 컨텍스트`를 무시하고 DB에 직접 쿼리를 수행하기 때문에 영속성이 깨질 수 있기 때문에 주의해야한다. (영속성에 특정 엔티티의 정보가 들어있는데 벌크 연산 수행하고 조회를 하면, 그대로 연산된 정보가 아닌 이전 정보를 조회하기 때문)

### ◾ 해결법

#### em.refresh()

영속성 컨텍스트에 있는 엔티티들을 새로 조회

#### 벌크 연산을 먼저 실행

하지만 영속성 컨텍스트에 값이 남아있을 수도 있다.

#### 벌크 연산 수행 후 영속성 컨텍스트 초기화

아예 영속성 컨텍스트를 초기화하고 다시 필요한 시기에 엔티티들을 새로 조회하는 방법

## JPQL의 문제점

조회한 결과를 영속성 컨텍스트에서 먼저 찾고 없다면 저장하는 `em.find()`와는 달리 JPQL은 영속성 컨텍스트에서 먼저 찾지 않고 바로 DB에서 조회를 날려 결과값을 받아오고 영속성 컨텍스트에 해당 엔티티가 있다면 결과값을 버리고 없다면 저장한다.

그래서 영속성 컨텍스트의 캐시 역할을 기대할 수있는 `em.find`가 성능상 이점이 있다.

## 플러시 모드

JPA는 기본 플러시 모드가 `FlushModeType.AUTO`로 커밋이나 쿼리 실행 시 자동으로 플러시가 수행된다. 하지만, 플러시가 너무 자주 발생하는 상황에 성능향상을 위해 Commit모드로 변경하게 되면 문제가 발생할 수 있다.

특정 엔티티의 필드를 수정하고 flush를 하지 않은 상태에서 쿼리를 수행하면 수정하지 않은 값이 조회되기 때문이다. 이때는 쿼리전에 `em.flush()`로 직접 호출하거나 `setFlushMod(FlushModeType.AUTO)`로 특정 쿼리에 플러시모드를 설정 할 수 있다.

```java
em.setFlushMode(FlushModeType.COMMIT);

member.setUserName("홍길동");

//em.flush();m
Member member = em.createQuery("select m from Member m where m.username = '홍길동'", Member.class)
    .setFlushMode(FlushModeType.COMMIT)
    .getSingleResult();
```

<br><br><br>

---

## Reference

자바 ORM 표준 JPA 프로그래밍 책 (김영한 저)
