# HAVING

데이터를 필터링하기 위한 구문

## 기본 문법

```sql
SELECT
    select_list
FROM
    table_name
WHERE
    search_condition
GROUP BY
    group_by_expression
HAVING
    group_condition;
```

## WHERE과 차이

결과만 보면 where과 비슷하다고 생각 할 수도 있지만 having은 group by 뒤에 위치해서 그룹핑한 데이터에 대해 조건을 주고 where은 모든 필드에 대해 조건을 줄 수 있다.

실행 순서도 where은 group by전에 조건을 걸고, having은 group by후에 조건을 건다.

## 사용 예

```sql
SELECT
    ordernumber,
    SUM(quantityOrdered) AS itemsCount,
    SUM(priceeach*quantityOrdered) AS total
FROM
    orderdetails
GROUP BY
   ordernumber
HAVING
   total > 1000;
```

orderdetails 테이블에서 ordernumber로 그룹핑을 한 데이터들 중 total이 1000이상인 데이터들 select
