# CONCAT

문자열을 연결할때 사용할 수 있는 함수

```SQL
CONCAT(str1,str2...);
```

하나 이상의 str을 입력하면 문자열을 붙여준다.

매개변수로 NULL이 하나라도 있으면 NULL을 반환한다.

```SQL
SELECT
    concat(contactFirstName,' ',contactLastName) AS Fullname
FROM
    customers;
```

## CONCAT_WS

매개변수를 하나 더 받아 모든 문자열을 연결 시 사이에 매개변수를 사용하여 붙여준다.

```SQL
CONCAT_WS(seperator, str1, str2...)
```

seperator가 NULL이면 NULL을 반환

문자열이 NULL이면 건너 뛰고 다음 문자열연결

```SQL
SELECT
    CONCAT_WS(CHAR(13), //CL
            CONCAT_WS(' ', contactLastname, contactFirstname),
            addressLine1,
            addressLine2,
            CONCAT_WS(' ', postalCode, city),
            country,
            CONCAT_WS(CHAR(13), '')) AS Customer_Address
FROM
    customers;
```
