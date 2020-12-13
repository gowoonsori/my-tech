# ROLLUP

소계와 총 합계를 생성하여 출력하기 위한 구문

## 기본 문법

```SQL
SELECT
    select_list
FROM
    table_name
GROUP BY
    c1, c2, c3 WITH ROLLUP;
```

```SQL
SELECT
    orderYear,
    productLine,
    SUM(orderValue) totalOrderValue
FROM
    sales
GROUP BY
    orderYear,
    productline
WITH ROLLUP;
```

## GROUP조건이 여러개 일때

계층적으로 그룹화 세트가 만들어지며, 두개의 COLUMN이라면 C1에 대해 C2들의 합이 출력되고나서 C1의 총합들의 합이 출력된다.

출력될 때, 합의 기준이 된 COLUMN값은 NULL이 된다.

| orderYear |   productLine    | totalOrderValue |
| :-------: | :--------------: | :-------------: |
|   2003    |   Classic Cars   |     5571.80     |
|   2003    |   Montorcycles   |     2240.50     |
|   2003    |      Planes      |     4825.44     |
|   2003    |      Ships       |     5072.71     |
|   2003    |      Trains      |     2770.95     |
|   2003    | Trucks and Buses |     3284.28     |
|   2003    |   Vintage Cars   |     4080.00     |
|   2003    |     **NULL**     |    28045.68     |
|   2004    |   Classic Cars   |     8124.98     |
|   2004    |   Montorcycles   |     2598.77     |
|   2004    |      Planes      |     2857.35     |
|   2004    |      Ships       |     4301.15     |
|   2004    |      Trains      |     4646.88     |
|   2004    | Trucks and Buses |     4615.64     |
|   2004    |   Vintage Cars   |     2819.28     |
|   2004    |     **NULL**     |    29964.05     |
| **NULL**  |     **NULL**     |    58009.75     |

## GROUPING()

NULL 결과 집합이 부분합이나 총합을 나타내는지 확인하기 위한 함수

## 문법 예시

```sql
SELECT
    orderYear,
    productLine,
    SUM(orderValue) totalOrderValue,
    GROUPING(orderYear),
    GROUPING(productLine)
FROM
    sales
GROUP BY
    orderYear,
    productline
WITH ROLLUP;
```

| orderYear |   productLine    | totalOrderValue | GROUPING(orderYear) | GROUPING(orderYear) |
| :-------: | :--------------: | :-------------: | :-----------------: | :-----------------: |
|   2003    |   Classic Cars   |     5571.80     |          0          |          0          |
|   2003    |   Montorcycles   |     2240.50     |          0          |          0          |
|   2003    |      Planes      |     4825.44     |          0          |          0          |
|   2003    |      Ships       |     5072.71     |          0          |          0          |
|   2003    |      Trains      |     2770.95     |          0          |          0          |
|   2003    | Trucks and Buses |     3284.28     |          0          |          0          |
|   2003    |   Vintage Cars   |     4080.00     |          0          |          0          |
|   2003    |     **NULL**     |    28045.68     |          0          |          1          |
|   2004    |   Classic Cars   |     8124.98     |          0          |          0          |
|   2004    |   Montorcycles   |     2598.77     |          0          |          0          |
|   2004    |      Planes      |     2857.35     |          0          |          0          |
|   2004    |      Ships       |     4301.15     |          0          |          0          |
|   2004    |      Trains      |     4646.88     |          0          |          0          |
|   2004    | Trucks and Buses |     4615.64     |          0          |          0          |
|   2004    |   Vintage Cars   |     2819.28     |          0          |          0          |
|   2004    |     **NULL**     |    29964.05     |          0          |          1          |
| **NULL**  |     **NULL**     |    58009.75     |          1          |          1          |

이런 특성을 이용해 `IF`와 합쳐서 표현이 가능하다

```sql
SELECT
    IF(GROUPING(orderYear),
        'All Years',
        orderYear) orderYear,
    IF(GROUPING(productLine),
        'All Product Lines',
        productLine) productLine,
    SUM(orderValue) totalOrderValue
FROM
    sales
GROUP BY
    orderYear ,
    productline
WITH ROLLUP;
```

| orderYear |    productLine    | totalOrderValue |
| :-------: | :---------------: | :-------------: |
|   2003    |   Classic Cars    |     5571.80     |
|   2003    |   Montorcycles    |     2240.50     |
|   2003    |      Planes       |     4825.44     |
|   2003    |       Ships       |     5072.71     |
|   2003    |      Trains       |     2770.95     |
|   2003    | Trucks and Buses  |     3284.28     |
|   2003    |   Vintage Cars    |     4080.00     |
|   2003    | All Product Lines |    28045.68     |
|   2004    |   Classic Cars    |     8124.98     |
|   2004    |   Montorcycles    |     2598.77     |
|   2004    |      Planes       |     2857.35     |
|   2004    |       Ships       |     4301.15     |
|   2004    |      Trains       |     4646.88     |
|   2004    | Trucks and Buses  |     4615.64     |
|   2004    |   Vintage Cars    |     2819.28     |
|   2004    | All Product Lines |    29964.05     |
| All Years | All Product Lines |    58009.75     |
