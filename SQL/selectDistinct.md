# SELECT DISTINCT

중복을 제거하여 select

```sql
SELECT DISTINCT selct_list FROM table;
```

NULL도 포함하여 가져오며, NULL도 한개만 select

<br>

## 중복 DISTINCT

```sql
SELECT DISTINCT
    list1, list2
FROM
    table;
```

list1과 list2를 조합하여 중복을 제거해서 select한다.

따라서 list1과 list2는 여러번 올 수 있지만 (list1,list2)의 조합은 고유하다.

<br>

### GROUP BY와 차이

결과만 보면 동일하나 DISTINCT는 정렬이 되지 않지만 GROUP BY는 암시적으로 정렬 된 값을 출력한다

> 8버전 이후 부터는 암시적 정렬이 사라졌다.

사용 목적에 따라 무엇을 사용할지 경하자

`DISTINCT`는 중복을 제거, `GROUP BY`는 그룹핑을 하는 것

count와 같이 사용하고자 한다면, DISTINCT는 DISTINCT로 중복을 제거한 column을 count하는 개념 `COUNT(DISTINCT name)`

GROUP BY는 count후 그룹핑하는 개념

```sql
SELECT
    COUNT(name)
FROM
    table
GROUP BY name;
```

GROUP BY

- select와 from사이에 집계함수가 들어간 경우
- 조회결과를 GROUP으로 나누어 봐야하는 겨우

실행 순서는

```
FROM -> ON -> JOIN -> WHERE -> `GROUP BY`-> HAVING -> SELECT -> DISTINCT -> ORDER BY -> LIMIT
```

로 group by는 select전에 distinct는 select후에 일어난다.
