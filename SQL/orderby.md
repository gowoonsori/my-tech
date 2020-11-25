# ORDER BY

결과 TABLE의 데이터를 정렬하기 위한 문법

```SQL
SELECT
   select_list
FROM
   table_name
ORDER BY
   column1 [ASC|DESC],
   column2 [ASC|DESC],
   ...;
```

SELECT를 통해 가져온 데이터 결과 TABLE을 `ORDER BY`문법을 통해 정렬한다.

`column1`을 기준으로 `오름차순(ASC)` or `내림차순(DESC)`로 정렬하고, 그 후 `column`이 있다면 기본 정렬된 순서를 유지하면서 다음 column을 기준으로 정렬한다.

정렬 방식은 명시적으로 정렬하지 않아도 `ASC`로 정렬된다.

```SQL
//아래 두 문법은 동일하다.
ORDER BY column1;
ORDER BY column1 ASC;
```

<BR>

## 표현식을 통한 COLUMN 정렬

```SQL
SELECT
    numberOfOrder,
    price,
    numberOfOrder * price
FROM
    table_name
ORDER BY
    numberOfOrder * price DESC;
```

<br>

## 별칭(AS)를 이용해 column 정렬

```SQL
SELECT
    name AS first_name
FROM
    table_name
ORDER BY
    first_name DESC;
```

<br>

## 특정 COLUMN의 값을 사용자 지정 목록으로 지정

`FIELD()`함수를 이용

`orders`라는 TABLE에 `status`라는 column의 값을 Start - In Process - Cancelled - End 순으로 정렬하고자 한다면 `FIELD()`함수를 이용하여 정렬할 수 있다.

```SQL
SELECT
    orderNumber,
    status
FROM
    orders
ORDER BY
    FIELD(status,
        'Start',
        'In Process',
        'Cancelled',
        'End');
```
