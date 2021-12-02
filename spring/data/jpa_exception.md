# JPA 예외처리
Runtime Exception을 상속받은 PersistenceException 클래스가 JPA의 표준 예외 클래스이다.

## 롤백을 표시하는 예외

트랜잭션 롤백을 표시하는 예외로 이는 심각한 예외이기 때문에 작업을 복구해서는 안된다.

1. EntityExistException : persist()호출 시 이미 같은 엔티티 있을 시 발생
2. EntityNotFoundException : 엔티티가 존재하지 않을 때 발생
3. OptimisticLockException : 낙관적 락 충돌 시 발생
4. PessimisticLockException : 비관적 락 충돌 시 발생
5. RollbackException : commit실패 시 발생(Rollback이 표시되어있는 트랜잭션의 커밋시에도 발생)
6. TransactionRequriedException : 트랜잭션이 없으면 발생

## 롤백을 표기하지 않는 예외

1. NoResultException : singleResult() 조회시 결과가 하나도 없을때 발생
1. NonUniqueResultException : singleResult() 조회시 결과가 둘 이상일때 발생
1. LockTimeoutExeption : 비관적 락에서 시간 초과 시 발생
1. QueryTimeoutException : 쿼리 실행 시간 초과 시 발생

## 주의사항

트랜잭션 롤백시 DB는 원래대로 복구가 되지만 영속성 컨텍스트는 수정된채 그대로이기 때문에 `clear()`나 새로운 영속성 컨텍스트를 생성해서 초기화한다음 사용해야 안전하다. (기본 전략은 문제발생시 트랜잭션 AOP가 종료시점에 트랜잭션을 롤백하면서 영속성 컨텍스트를 함께 종료시킨다.)

<br><br><br>

---

## Reference

자바 ORM 표준 JPA 프로그래밍 책 (김영한 저)
