# SELECT

TABLE에서 특정 조건에 맞는 데이터를 읽기 위해 데이터를 QUERY 하는 구문

## 기본 구문

```SQL
SELECT select_list
FROM table_name;
```

이때, select_list는 여러가지가 올 수 있다.

```sql
//table내의 모든 열
SELECT *
FROM table_name;

//한개의 열
SELECT list1
FROM table_name;

//원하는 열 선택
SELECT list1,list2,list3
FROM table_name;
```

`*`는 DB서버와 앱사이에 불필요한 I/O 디스크, 네트워크 트래픽을 생성하고, 민감한 데이터의 `열`또한 가져옴으로써, 정보가 노출 될 수도 있기 때문에, 지양하자.
