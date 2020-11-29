# IFNULL

column값이 null이면 특정 값으로 바꿔주는 문법

```sql
SELECT
    IFNULL(revenue, 0) AS revenue
FROM
    table
```

revenue가 null 이면 0으로 바꿔 가져오는 쿼리문이다.
