## 이해하기 힘든 이름

### 함수 선언 변경
- 이름만 보고도 어떻게 구현되었는지 이해할 수 있는 이름
- 매개변수는 내부의 문맥과 의존성을 결정
### 변수 이름 변경
### 필드 이름 변경
- Record 자료구조 사용 ( 특정 데이터와 관련있는 필드를 묶어놓은 자료 구조 )
  - 파이썬의 Dicts
  - C# 의 Record
  - java 14 부터는 record 키워드
  - PHP같은 동적타입의 언어는 존재X
    - stdClass(object)를 이용하면 어느정도 비슷하게는 할 수 있으나 특정 타입으로 정의 불가능

      ```php
      $obj = new stdClass();
      $obj->name = "홍길동";
      echo $obj->name;
        ```