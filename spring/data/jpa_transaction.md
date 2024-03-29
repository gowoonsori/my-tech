# 트랜잭션 범위와 영속성 컨텍스트

스프링 컨테이너는 `트랜잭션 범위의 영속성 컨텍스트`를 제공하는데 이는 트랜잭션 범위내에서 영속성 컨텍스트가 존재한다는 의미이다.

보통 비즈니스로직을 시작하는 Service단 부터 `@Transaction`어노테이션을 이용해 트랜잭션을 시작하고 이렇게 트랜잭션 범위내애서만 영속성 컨텍스타가 유지된다. (`트랜잭션 어노테이션이 있으면 트랜잭션AOP가 Service의 메서드를 실행시키기전에 먼저 동작하여 트랜잭션을 시작하고 메서드가 종료되면 트랜잭션을 커밋하면서 종료한다.`)

**같은 트랜잭션이면 같은 영속성 컨텍스트를 사용하고 트랜잭션이 다르다면 영속성 컨텍스트도 다르기 때문에 멀티스레드 상황에도 안전하다.**

<br>

이처럼 영속성 컨텍스트는 트랜잭션 범위내에서만 존재하기 때문에 트랜잭션이 끝난 controller단에서 변경감지를 통한 수정, 지연로딩을 통한 조회를 하려고 하면 에러가 발생한다. (이때 프록시 객체가 이미 초기화 되어있는 상태라면 조회는 가능하지만 초기화가 되어있지 않다면 초기화하기 위해 영속성컨텍스트를 이용해 조회하고 쿼리를 날리겠지만 트랜잭션범위 밖이기 때문에 영속성컨텍스트도 존재하지 않아 에러가 발생한다.)

### 해결방법

1.  패치전략을 `즉시 로딩`으로 수정 : 이는 사용하지 않는 엔티티일경우에도 조회하고 `N+1`문제가 발생할 수 있어 성능상에 문제가 생길 수 있다.

    > N+1?
    >
    > 연관된 엔티티를 조회할때 JPQL을 이용해서 조회를 한다면 글로벌 패치 전략을 참조하지 않고 JPQL자체만을 해석해서 SQL문을 생성하기 때문에 JOIN을 하지 않고 연관된 테이블을 하나하나 조회하는 문제

1.  JPQL 패치 조인

    ```java
    em.createQuery("select o from Order o join fetch o.memeber", Order.class).getResultList();
    ```

    위와 같이 JPQL을 fetch join으로 명시해서 SQL의 join을 이용한 조회를 사용하도록 하는 방법

    문제점 : 이렇게 view가 원하는 대로 응답을 맞추는 것은 데이터접근 계층이 view단을 의존하게 되고 그때마다 비슷한 메서드를 만드는 것은 비효율적이다.

        연관된 테이블의 정보가 필요없는 view의 요청에서도 하나의 메서드를 만들고 내부에서 무조건 즉시로딩을 한 Entity를 반환하는 방식으로 하는 것이 조금 성능면에서는 떨어질 수 있어도 조금 더 결합도를 낮출 수 있다.

1.  강제 초기화

    지연로딩이 글로벌 페치 전략일때 view가 연관entity정보도 필요하다면 service단에서 강제로 프록시객체를 초기화하여 넘겨주는 방법

    이도 결국 view가 service계층영역을 침범하는 일이다.

    - FACADE : 계층간 역할 구분을 확실히 하기 위해 중간에 FACADE계층을 추가할 수 는 있지만 관리해야하는 계층이 한개더 추가되는 것이고 단순히 service를 호출하는 코드가 반복되게 되는데 기능하나 추가하는데 작업해야하는 코드가 많이 늘어난다.

### OSIV

Open Session In View의 약자로 해석 그대로 영속성 컨텍스트의 생존 범위를 View까지 유지하는 것이다.

하지만 이는 Update와 같은 비즈니스 로직을 수행할때마다 변경내용이 DB에 반영되게 되어 유지보수가 상당히 힘들어진다. 그래서 DTO와 같은 객체를 이용해서 작업하는 방식이 있지만 애초에 많은 문제를 야기할 수 있기 때문에 사용은 되지않고 문제점을 해결한 스프링 프레임워크가 제공하느 `OSIV`가 있다.

- hiberante OSIV servlet filter : OpenSessionInViewFilter
- hibernate OSIV spring intercepter : OpenSessionInViewInterceptor
- JPA OEIV servlet filter : OpenEntityManagerInViewFilter
- JPA OEIV spring interceptor : OpenEntityManagerInViewInterceptor

서블릿 필터에 적용할지 인터셉터에 적용할지에 따라 위의 클래스 중 선택하여 등록을 하면 된다.

### 스프링 OSIV

스프링 OSIV는 일반 OSIV의 문제점을 해결하고자 나온것으로 영속성 컨텍스트는 view까지 살아있으나 트랜잭션이 시작되기전에는 `읽기`만 가능하고 트랜잭션 시작 범위부터 `수정`이 가능하다.

여기서 트랜잭션 시작 범위부터 수정이 가능하다는 것은 영속성 컨텍스트의 변경사항을 `flush`한다는 뜻이고 트랜잭션 범위 밖이라면 메서드가 끝나도 자동으로 flush가 수행되지도 않고 강제로 호출한다고 해도 에러가 발생한다. 하지만, 영속성 컨텍스트에 존재하는 객체는 수정이 되어있는 상태이기 때문에 수정을하고 다시 Service의 메서드를 호출해서 트랜잭션 시작범위로 들어가게 되면 영속성컨텍스트가 기존과 변경되었기 때문에 변경사항의 쿼리가 발생하는 문제가 발생한다.

때문에, controller에서는 비즈니스로직이 모두 끝나고 수정을 해야 문제가 발생하지 않는다.

<br><br><br>

---

## Reference

자바 ORM 표준 JPA 프로그래밍 책 (김영한 저)
