# SQL

RDBMS(관계형 데이터베이스 관리 시스템)을 이용해 데이터를 관리하기 위한 언어

RDBMS 종류 마다 문법은 조금씩 상이하다.

나는 MySQL을 기본으로 [MYSQL TUTORIAL](https://www.mysqltutorial.org/basic-mysql-tutorial.aspx)를 통해 SQL문을 공부하고자 한다.

<br>

## 종류

- 데이터 정의 언어 (Data Definition Language)

  - CREATE : DB 객체(TABLE) 생성
  - DROP : DB 객체(TABLE) 삭제
  - ALTER : DB 객체(TABLE) 구조 변경
  - RENAME : DB 객체(TABLE) 이름 변경
  - TRUNCATE : 테이블 내의 모든 데이터를 삭제 ( 내부적으로 COMMIT연산 포함 )

- 데이터 조작 언어 (Data Manipulation Language)

  - INSERT INTO : TABLE에 데이터 삽입
  - UPDATE ~ SET : TABLE 업데이트
  - DELETE FROM : TABLE의 데이터 삭제
  - SELETE ~ FROM ~ (WHERE) : TABLE내의 특정 데이터 선택

- 데이터 제어 언어 (Data Control Language)
  - GRANT : 특정 사용자에게 DB에 접근 권한을 부여
  - REVOKE : 특정 사용자의 DB의 접근 권한을 박탈
  - SET TRANSACTION : 트랜잭션 모드 설정
  - BEGIN : 트랜잭션 시작
  - COMMIT : 트랜잭션 실행
  - ROLLBACK : 트랜잭션 취소
  - SAVEPOINT : 무작위로 롤백 지점 설정

<br>

## 조건 표현

다른 언어의 `if~else` 문의 역할이며 아래의 문법을 이용해 표현

- CASE
- WHEN
- THEN
- ELSE
- END

```sql
CASE WHEN n > 0 THEN 'positive' WHEN n < 0 THEN 'negative' ELSE 'zero' END
```

<br>

## 자료형

- CHAR(N) : N크기의 고정폭 문자열 (RDBMS에 따라 공백으로 채워지거나 동적으로 줄어든다.)
- VARCHAR(N) : 최대 N크기의 가변폭 문자열
- NCHAR(N) : 국제 문자셋 고정폭 문자열

- NVARCHAR(N) : 가변폭 NCHAR
- BIT(N) : N비트의 배열
- INTEGER | BIGINT : 정수와 LONG
- NUMERIC / DECIMAL : 소수
- DATE / TIME / DATETIME / TIMESTAMP : 날짜와 시간

<br><Br>

---

## Reference

https://ko.wikipedia.org/wiki/SQL
