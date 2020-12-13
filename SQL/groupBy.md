# Group By

column 이나 표현식의 값을 기준으로 raw 집합을 그룹화하기 위해 사용

## 구문

```sql
SELECT
    column, column2 ... function(column) [ex. COUNT]
FROM
    member
WHERE
    column_condtion
GROUP BY column

```

## 실행 순서

FROM -> ON -> JOIN -> WHERE -> `GROUP BY`-> HAVING -> SELECT -> DISTINCT -> ORDER BY -> LIMIT

## 예

```sql
SELECT
    YEAR(orderDate) AS year,
    SUM(quantityOrdered * priceEach) AS total
FROM
    orders
INNER JOIN orderdetails
    USING (orderNumber)
WHERE
    status = 'Shipped'
GROUP BY
    YEAR(orderDate);
```

orderNumber이 외래키인 orderdetails테이블과 inner join을 한 후, status가 Shipped 인 raw 들을 년도로 group한 raw집합들을 year과, total을 계산하여 출력

## 별칭

표준 SQL에서는 group by절에 별칭을 사용 할 수 없지만 MySQL은 지원한다.

```sql
SELECT
    YEAR(orderDate) AS year,
    COUNT(orderNumber)
FROM
    orders
GROUP BY
    year;
```

## 정렬

마찬가지로 표준 SQL에서는 지원하지 않지만 order by가 아닌 group by에서도 정렬이 가능하다.

```sql
SELECT
    status,
    COUNT(*)
FROM
    orders
GROUP BY
    status DESC;
```
