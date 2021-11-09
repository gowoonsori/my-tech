# Map

key와 value를 이용해 데이터를 저장하는 자료구조

객체와는 다르게 key에 다양한 자료형을 허용한다

map의 value에 접근할때 `대괄호[]`로 접근이 가능하나 이는 객체와 같은 취급을 하기에 `get`,`set`을 이용

key로 객체도 허용한다.

맵은 key를 비교할때 `===`이 아닌 `SameValueZero`라는 알고리즘으로 등가 여부를 확인하기 때문에 `NaN`도 key로 사용가능하다

맵의 key로 객체를 사용하고 객체를 삭제시에 가비지 컬렉터가 객체를 삭제하지 않는다. _(여전히 맵이 객체를 참조하고 있기 때문에)_

## 주요 메서드와 프로퍼티

- new Map() : 맵 생성

- map.set(key,value) : key를 이용해 value 저장

- map.get(key) : key의 value 반환. key가 없으면 undefined

- map.has(key) : key가 존재하면 true, 없으면 false

- map.delete(key) : key에 해당하는 value 삭제

- map.clear() : 맵 모든 요소 지우기

- map.size : 맵의 요소 개수 반환

- map.keys() : key들을 모은 iterable객체를 반환

- map.values() : value들을 모은 iterable 객체를 반환

- map.entries() : [key,value]를 쌍으로하는 iterable객체를 반환

  ```js
  let recipeMap = new Map([
    ['cucumber', 500],
    ['tomatoes', 350],
    ['onion', 50],
  ]);

  for (let vegetable of recipeMap.keys()) {
    alert(vegetable); // cucumber, tomatoes, onion
  }

  for (let amount of recipeMap.values()) {
    alert(amount); // 500, 350, 50
  }

  alert(recipeMap.entries());
  ```

- forEach() : 모든 요소에 대해 반복실행

- Object.entries : 객체를 맵으로 바꾸기

  ```js
  let obj = {
    name: 'John',
    age: 30,
  };

  let map = new Map(Object.entries(obj));
  alert(map.get('name')); // John
  ```

- Object.fromEntries : 맵을 객체로 바꾸기

  ```js
  let map = new Map();
  map.set('banana', 1);
  map.set('orange', 2);
  map.set('meat', 4);

  let obj = Object.fromEntries(map.entries()); // obj = { banana: 1, orange: 2, meat: 4 }
  alert(obj.orange); // 2
  ```

## WeekMap

위크맵은 일반 맵과 달리 키로쓰인 객체가 가비지 컬렉션의 대상이 된다.

key가 반드시 객체이어야 한다.

### 사용가능 함수

- weakMap.get(key)
- weakMap.set(key, value)
- weakMap.delete(key)
- weakMap.has(key)

### 사용 예

- 부가적인 데이터를 저장할 곳이 필요할때

  외부 코드에 속한 객체를 가지고 작업을 할때, 어떤 객체에 데이터를 추가해줄때 _(굳이 외부 코드에 속한 객체를 메모리에 남길 필요가 없다.)_

- 캐싱이 필요할때

  동일한 함수를 여러번 호출할때 (처음 실행값을 여러번 사용할때) 캐싱을 이용하며 캐시에 필요없어진 함수를 삭제할때 WeekMap이 유용하다.

<br>

# Set

중복을 허용하지 않는 값들을 모아놓은 자료구조

## 주요 메서드 및 프로퍼티

- new Set(iterable) : iterable객체(배열, 객체)을 전달받으면 값을 복사해 셋을 만들어준다.

- set.add(value) : value를 추가하고 셋 자신을 반환
- set.delete(value) : value를 제거하고 제거가 성공하면 true, 아니면 false 반환
- set.has(value) : 셋 내에 값이 존재하면 true, 아니면 false
- set.clear() : 셋 초기화
- set.size : 셋의 요소 개수

- for...of / forEach : 반복작업 수행

  ```js
  let set = new Set(['oranges', 'apples', 'bananas']);

  for (let value of set) alert(value);

  set.forEach((value, valueAgain, set) => {
    alert(value);
  });
  ```

  map과 set의 상호 변환을 쉽게하기 위해 forEach에 쓰인 인수를 2개 사용한다.

## WeekSet

위크맵처럼 복잡한 데이터를 저장하지 않고 `예`, `아니오`처럼 간단한 답변을 얻는 용도로 사용

### 사용가능 함수

- weakSet.get(key)
- weakSet.set(key, value)
- weakSet.delete(key)
- weakSet.has(key)

### 사용 예

- 부가적인 데이터를 저장할 곳이 필요할때

  외부 코드에 속한 객체를 가지고 작업을 할때, 어떤 객체에 데이터를 추가해줄때 _(굳이 외부 코드에 속한 객체를 메모리에 남길 필요가 없다.)_

- 캐싱이 필요할때

  동일한 함수를 여러번 호출할때 (처음 실행값을 여러번 사용할때) 캐싱을 이용하며 캐시에 필요없어진 함수를 삭제할때 WeekMap이 유용하다.
