# WHERE

SELECT를 통해 데이터를 GET할때 RAW를(결과) 필터링 할 때 사용하는 구문

```SQL
SELECT
    select_list
FROM
    table_name
WHERE
    search_condition;
```

<br>

# WHERE과 같이 쓰이는 문법

`search_condition`에 오는 구문으로 아래의 연산자들중 한개 이상의 표현을 이용하여 작성 할 수 있다.

<br>

## 조건 연산자

- `=` : 같다

- `<>`, `!=` : 같지 않다
- `<` : 보다 작다
- `>` : 보다 크다
- `<=` : 보다 작거나 같다
- `>=` : 보다 크거나 같다

<br>

## 논리 연산자

- AND
- OR
- NOT

<br>

## BOOL

- TRUE
- FALSE
- UNKNOWN

<br>

## BETWEEN

사이의 값 필터링

```SQL
SELECT
    firstName,
    lastName,
    officeCode
FROM
    employees
WHERE
    officeCode BETWEEN 1 AND 3
    //officeCode >=1 AND officeCode <=3 과 같다
ORDER BY officeCode
```

<br>

## LIKE

data에 특정 패턴을 검샣나는 구문으로 아래와 같은 `와일드 카드`들을 이용해 정규표현식같이 사용 하여 표현할 수 있게 해준다.

`%` : 0개 이상의 문자
`_` : 단일 문자
`

`lastName가 Patterson`인 data가 있다고 한다면

```sql
SELECT
    firstName,
    lastName
FROM
    employees
WHERE
    lastName LIKE '%son' //Patterson
    lastName LIKE '_atterson' // Patterson
    lastName LIKE 'P%' //Patterson
ORDER BY firstName;
```

1. A% : 'A'로 시작하는 모든 문자열
2. %A% : 'A'가 포함된 모든 문자열

3. \_A% : 두 번째 문자가 'A'인 모든 문자열

만일 data에 `_`,`%`와 같은 특수문자가 들어가 있어 이를 검색하고자 한다면 `역슬래시 \`를 이용해서 표현할 수 있다.

```sql
SELECT * FROM employees WHERE first_name LIKE '%\_%'; //_가 포함된 data
```

<br>

## IN

`IN (val1, val2 ...)` val안에 해당하는 data들을 조회하기 위한 문법

```sql
SELECT
    *
FROM
    employees
WHERE
    officeCode IN (1 ,2, 3)
    //=> officeCode = 1 or officeCode = 2 or officeCode = 3
ORDER BY
    officeCode;
```

<br>

## IS NULL

data가 NULL인지 아닌지 판별해 NULL인 data를 조회

```sql
SELECT
    *
FROM
    employees
WHERE
    reportsTo IS NULL;
```
