# CTE

Common Table Expression 의 약자로 공통 테이블 표현식이다.

명령문 내에서 임시로 생성한 테이블로 쿼리 실행 중에만 지속되고 파생태이블과 달리 쿼리 실행 중에 여러번 참조 될 수 있다.

## 기본 구문

```sql
WITH cte_name (column_list) AS (
    query
)
SELECT * FROM cte_name;
```

WITH AS 절을 이용하여 ()안의 쿼리문[Select from where]을 이용해 임시 테이블 cte_name을 만들어 이 CTE에 접근이 가능하다.

## 예시 구문

```sql
WITH topsales2003 AS (
    SELECT
        salesRepEmployeeNumber employeeNumber,
        SUM(quantityOrdered * priceEach) sales
    FROM
        orders
            INNER JOIN
        orderdetails USING (orderNumber)
            INNER JOIN
        customers USING (customerNumber)
    WHERE
        YEAR(shippedDate) = 2003
            AND status = 'Shipped'
    GROUP BY salesRepEmployeeNumber
    ORDER BY sales DESC
    LIMIT 5
)
SELECT
    employeeNumber,
    firstName,
    lastName,
    sales
FROM
    employees
    JOIN
    topsales2003 USING (employeeNumber);
```

orders, orderdetails, customers 세개의 테이블을 join한 CTE를 employees와 join하여 select하는 쿼리문

## 재귀적 CTE (RECURSIVE CTE)

Mysql 8.0이상에서만 사용할 수 있고, anchor member(재귀 멤버,column)를 재귀 조건에에 따라 반복하며 `UNION ALL`, `UNION DISTINCT`와 결합하여 재귀 맴버들을 합친 TABLE을 생성한다.

### 예시 구문

```SQL
WITH RECURSIVE cte_name AS (
    initial_query  -- anchor member
    UNION ALL
    recursive_query -- recursive member that references to the CTE name
)
SELECT * FROM cte_name;
```

재귀 멤버는 집계함수(MAX,MIN,SUM,AVG,COUNT..), GROUP BY, ORDER BY, LIMIT, DISTINCT 를 포함 할 수 없다. (UNION DISTINCT를 사용하는 경우 DISTINCT는 사용가능하다)

### 사용 예시 구문

```SQL
WITH RECURSIVE
    cte AS (
        SELECT 0 AS HOUR
        UNION ALL
        SELECT HOUR + 1
        FROM cte
        WHERE HOUR <23)
SELECT
   hour, count(o.datetime)

FROM
    cte
left JOIN ANIMAL_OUTS AS O
ON cte.hour = HOUR(O.DATETIME)
group by hour;
```

숫자 0부터 23까지 1씩 증가하는 COLUMN(HOUR)를 가진 TABLE (CTE)를 생성하여 이 cte와 animal_outs라는 테이블과 join한 쿼리문이다.

```sql
WITH RECURSIVE employee_paths AS
  ( SELECT employeeNumber,
           reportsTo managerNumber,
           officeCode,
           1 lvl
   FROM employees
   WHERE reportsTo IS NULL
     UNION ALL
     SELECT e.employeeNumber,
            e.reportsTo,
            e.officeCode,
            lvl+1
     FROM employees e
     INNER JOIN employee_paths ep ON ep.employeeNumber = e.reportsTo )
SELECT employeeNumber,
       managerNumber,
       lvl,
       city
FROM employee_paths ep
INNER JOIN offices o USING (officeCode)
ORDER BY lvl, city;
```

employees테이블에서 reportsTo가 NULL인 row를 시작으로 해당 row의 employeeNumber와 같은 값의 reportsTo를 갖는 row들을 lvl을 증가 시키고 이 row에 대해 또 비교하며 재귀적으로 수행하여 employeeNumber와 같은 reportsTo의 값을 갖는 row가 없을때까지 반복하여 cte를 생성한다.

이 생성한 cte와 offices 테이블을 join하여 select하는 쿼리문이다.
