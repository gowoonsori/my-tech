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

- 영속 : 영속성 컨텍스트에 저장된 상태
- 준영속 : 영속성 컨텍스트에 저장되었다가 분리된 상태
- 삭제 : 삭제된 상태