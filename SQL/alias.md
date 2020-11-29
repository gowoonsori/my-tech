# ALIAS

단어 해석 그대로 별칭을 부여할때 사용

## COLUMN ALIAS

```SQL
SELECT
   CONCAT_WS(', ', lastName, firstname) AS `Full name`
FROM
   employees;
ORDER BY
	`Full name`;
```

위와 같이 COLUMN이름이 길어지면 별칭을 사용하면 `ORDER BY` , `WHERE` 등에서 별칭으로 사용이 가능하다.

```SQL
SELECT
   CONCAT_WS(', ', lastName, firstname) `Full name`
FROM
   employees;
ORDER BY
	`Full name`;
```

와 같이 `AS`를 생략할 수 있다.

<br>

## TABLE ALIAS

행에 대해서 별칭을 사용한 것 처럼 TABLE명에 대해서도 별칭이 사용가능하다.

```SQL
SELECT
    e.firstName,
    e.lastName
FROM
    employees e
ORDER BY e.firstName;
```
