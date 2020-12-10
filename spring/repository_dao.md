# Repository와 DAO

두 개 모두 Persistence(영속성) 로직에 대해 객체 지향적인 인터페이스를 제공하고 도메인 로직과 영속성 로직을 분리하여 `관심의 분리(separation of concerns)`원리를 만족시키는 데에 목적이 있다는 것은 같다.

<br>

## Repository

메모리에 로드된 객체 컬렉션에 대한 집합 처리를 위한 인터페이스를 제공한다.

DAO보다는 덜 세밀한 오퍼레이션으로 Repository내부에서는 다수의 DAO를 호출하는 방식으로 구현이 가능하다.

객체 컬렉션 처리에 관한 책임만을 갖는다.

순수한 도메인 모델 객체로 도메인의 요구사항에 따라 설계된다.

`DOMAIN MODEL`패턴과 함께 사용된다.

<br>

## DAO

Data Access Object로 데이터에 접근하는 객체를 뜻한다.

실제 개발 시에는 하부의 Persistence 메커니즘이 DB라는 사실을 숨기려고 하지 않고, DB와의 CRUD 쿼리와 1:1 매칭되는 자세한 오퍼레이션을 제공한다.

대체적으로 테이블 하나당 하나의 DAO를 사용하는 것이 일반적인 패턴이며, `TRANSACTION SCRIPT`패턴과 함께 사용된다.

Persistence 로직의 요구사항에 따라 설계 된다.

Persistence Layer에 속하는 `FACADE`

<br>

##

[Transaction Script와 Domain Model 차이점](/develop-common-sense/transactionScript_domainModel.md)

`Persistence`는 영속성으로 데이터의 지속성을 뜻한다. (앱을 종료하고 다시 실행해도 데이터의 변경없이 지속되는 것.)

즉 `Persistence Layer`는 데이터소스와 커넥션 풀을 담당하며 SQL 맵핑과 캐싱등을 수행한다.

<Br><Br>

---

## Reference

http://egloos.zum.com/aeternum/v/1160846
