# EntityManagerFactory와 EntityManager
## Entity Manager Factory

엔티티 메니저를 만드는 공장으로 이를 만드는 비용은 상당히 크기 때문에 한개만 만들어서 애플리케이션 전체에서 공유하도록 설계가 되어있다.

여러 스레드가 동시에 접근해도 안전하므로 스레드간 공유가 가능하다.

JPA 구현체들은 이 Entity Manager Factory를 생성할때 커넥션 풀도 생성한다.

## Entity Manager

이름 그대로 각 Entity를 관리하는 역할로 이는 여러 스레드가 동시에 접근하면 동시성 문제가 발생하므로 스레드간에 절대 공유하면 안된다.

## Persistence context

영속성 컨텍스트로 `엔티티를 영구 저장하는 환경`이다.

엔티티 메니저를 생성할 때 하나 만들어지며, 여러 엔티티 매니저가 같은 영속성 컨텍스트에 접근할 수도 있다.

### ◾ 특징

- 영속성 컨텍스트는 엔티티를 `식별자 값`으로 구분한다. (예를 들면 Id)

- 트랜잭션을 `커밋`하는 순간 영속성 컨텍스트에 저장된 엔티티를 DB에 반영하는데 이를 `flush`라고 한다.
- 장점
  - 1차 캐시 기능
  - 동일성 보장
  - 트랜잭션을 지원하는 `쓰기 지연`
  - 변경 감지
  - 지연 로딩

### ◾ Entity의 생명주기

- 비영속 : 영속성 컨텍스트와 관계 없는 상태

- 영속 : 영속성 컨텍스트에 저장된 상태 (persist())
- 준영속 : 영속성 컨텍스트에 저장되었다가 분리된 상태 (detach())
- 삭제 : 삭제된 상태 (remove())

## 조회/삽입/삭제

### ◾ 조회

```java
EntityManagerFactory emf = Persistence.createEntityManagerFactory("test");
EntityManager em = emf.createEnityManager();

Member member = new Member();
member.setId("member1");
em.persist(member);

//...

Member member1 = em.find(Member.class, "member1");
```

`find()`함수를 이용해 조회를 할 수 있고 가장 먼저 `1차 캐시`에서 `식별자 값`으로 엔티티를 찾고 있다면 DB 조회없이 조회가 가능하다.

이처럼 엔티티는 영속성 컨텍스트에 저장되어 관리 되기 때문에 같은 키의 엔티티를 반복 조회해도 같은 인스턴스를 반환하기 때문에 `동일성`을 보장한다.

### ◾ 삽입

`persist()`까지만 수행하면 DB에 쿼리는 날리지 않고 영속성 컨텍스트에 모아둔다.

```java
EntityTransaction transaction = em.getTransaction();
transaction.begin();

em.persist(member);

transaction.commit();
```

`commit()`을 통해 영속성 컨텍스트에 `쓰기지연 SQL 저장소`에 모아둔 쿼리를 날리게 된다.

이처럼 한번에 모아 트랜잭션을 날리기 때문에

### ◾ 수정

별다른 함수 없이 Entity의 필드를 `setter`를 통해 값을 수정하면 영속성 컨텍스트의 `변경 감지`를 통해 자동으로 update가 수행된다.

## flush

영속성 컨텍스트의 변경 내용을 DB에 반영하는 메서드이다.

현재 영속성 컨텍스트의 모든 엔티티를 스냅샷과 비교해서 수정된 엔티티를 찾고 수정된 엔티티에 맞게 쿼리를 만들어 `쓰기 지연 SQL저장소`에 등록한다.
<br>그 후, `쓰기 지연 SQL저장소`에 있는 쿼리를 DB에 전송한다.

### 영속성 컨텍스트 flush방법

1. 직접 호출

`em.flush()`를 통해 직접 호출할 수 있다.

1. 트랜잭션 커밋 시 자동 호출된다.

1. JPQL 쿼리 실행 시 플러시가 자동 호출 된다.
