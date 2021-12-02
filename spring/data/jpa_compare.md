# 엔티티 비교

비교에는 메모리 주소가 같은지 비교하는 `== (동일성)`이 있고 데이터가 같은지 비교하는 `equals() 동등성`이 있다.

동일한 컬럼의 데이터에 대해서 같은 트랜잭션 범위내에서 동일성 비교는 성공할 수 있지만 트랜잭션 범외가 달라져 영속성 컨텍스트가 서로 다르다면 동일성 비교는 실패한다.

그렇기 때문에 그다음으로는 데이터가 같은지 비교해볼 수 있는데 첫번째로는 DB의 식별자(ID)를 이용해서 비교를 해볼 수 있다. 하지만 이 또한 영속성컨텍스트는 달라도 영속성컨텍트으에 한번 영속이 된상태에서만 Id정보를 알 수 있기 때문에 한번 초기화를 해야지만 비교를 할 수 있다.

두번째로는 Entity의 Id와 같은 식별자를 이용한 equals()를 오버라이딩하여 동등성을 비교하는 것이 있고 이 식별자들은 중복되지 않고 거의 변경되지 않기 때문에 가장 좋은 방법이다.

<br>

## 프록시 타입 비교

엔티티 타입을 비교하고자 한다면 `==`이 아닌 프록시타입은 `instanceof`로 비교를 해야한다. (== 비교 연산시 부모클래스와(엔티티클래스) 자식 클래스(그를 참조하는 프록시클래스)를 비교하기 때문이다.)

`equals`로 동등성을 비교하고자 한다면 새로 equals를 오버라이딩해서 구현해주어야 한다.
일반적인 equals는 `==`으로 객체의 타입을 비교하고 필드의 값을 비교할때 멤버변수로 직접비교하기 때문에 `==`연산에서 객체타입이 같지도 않고 프록시 객체는 변수데이터 값을 `getter`로 조회하기 때문에 이로 코드를 변경해주어야 동등성도 비교가 된다.

프록시를 이용해서 상속관계에 있는 객체와 상속관계를 비교하고자 한다면 `instanceof`연산도 사용할 수 없고 다운캐스팅도 할 수 없기 때문에 문제가 발생한다.

### 해결방법

1. JPQL로 직접 조회 : 처음부터 자식타입을 직접 조회 하는 방법
1. 프록시 벗기기 : 하이버네이트에서 제공하는 `unProxy()`메서드를 이용해서 프록시를 벗겨낼 수 있다.

   하지만 영속성 컨텍스트는 한번 프록시로 노출한 엔티티는 계속 프록시로 노출을 하기 때문에 벗겨내게 되면 원본 엔티티와의 동일성을 비교가 실패한다.

<br><br><br>

---

## Reference

자바 ORM 표준 JPA 프로그래밍 책 (김영한 저)