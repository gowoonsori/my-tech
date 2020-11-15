# 배열

순서가 있는 컬렉션을 저장하기위한 자료구조

특별한 객체중 한 종류이기 때문에 length라는 프로퍼티와 `대괄호 접근`등 이용이 가능하다.

<br>

## 선언방법

```js
let arr = new Array();
let arr = [];
```

<br>

## 특징

- 배열 요소의 자료형에 제약이 없다.

  ```js
  let arr = [
    '사과',
    { name: '이보라' },
    true,
    function () {
      alert('안녕하세요.');
    },
  ];
  ```

- `for...of`문 이용해서 순회 가능

- `length 프로퍼티`를 이용해서 배열을 자르는 게 가능하다.
  ```js
  let arr = [1, 2, 3, 4, 5];
  arr.legth = 2;
  alert(arr); //1,2
  ```
- 내부적으로 toString 메서드가 구현되어 있어 호출시 쉼표를 구분한 문자열이 반환된다.

  ```js
  let arr = [1, 2, 3];

  alert(arr); //1,2,3
  alert(String(arr) === '1,2,3'); //true
  ```

- 배열도 객체이기 때문에 완전한 복제가 아닌 참조에 의한 복사가 이루어진다.

- 객체형이기 때문에 `typeof`로는 일반 객체와 배열을 구분할 수 없다.

  > Array.isArray()이용

  ```js
  alert(typeof {}); // object
  alert(typeof []); // object
  alert(Array.isArray({})); // false
  alert(Array.isArray([])); // true
  ```

- sort제외 대부분의 함수를 호출하는 메서드에서 `thisArg`라는 매개변수를 옵션으로 받을수 있다.

  ```js
  let army = {
    minAge: 18,
    maxAge: 27,
    canJoin(user) {
      return user.age >= this.minAge && user.age < this.maxAge;
    },
  };

  let users = [{ age: 16 }, { age: 20 }, { age: 23 }, { age: 30 }];

  // army.canJoin 호출 시 참을 반환해주는 user를 찾음
  let soldiers = users.filter(army.canJoin, army);

  alert(soldiers.length); // 2
  alert(soldiers[0].age); // 20
  alert(soldiers[1].age); // 23
  ```

  army라는 `thisArg`매개변수를 함수에 전달하고 있어 `thisArg`는 함수의 `this`가 된다.

<br>

# 함수

## 요소 추가 / 제거

- push() : `맨끝`에 요소를 `추가`
- pop() : `맨끝`의 요소를 `추출`
  > 스택을 쉽게 구현 가능
- shift() : `제일 앞` 요소를 꺼내 `제거`한 후 남아있는 요소들을 앞으로 밀어주는 함수

  > 이를 이용해 큐를 쉽게 구현가능하다.

- unshift() : `배열 앞`에 요소를 `추가`

- splice() : 배열에서 `요소를 지우고 삽입`

  - arr.splice(start, length, element1 ...)

  - 음수 인덱스도 사용이 가능하다.

  ```js
  let arr = ['I', 'study', 'JavaScript', 'right', 'now'];

  arr.splice(0, 3, "Let's", 'dance');

  alert(arr); // now ["Let's", "dance", "right", "now"]
  ```

- slice(start,end) : `요소 지우기`

  start부터 end까지 요소를 복사한 새로운 배열을 반환

- concat(arg1,arg2,...) : 기존 배열의 요소를 사용해 `새로운 배열을 만들`거나 기존 배열에 `요소를 추가`하기

  ```js
  let arr = [1, 2];

  alert(arr.concat([3, 4])); // 1,2,3,4
  alert(arr.concat([3, 4], [5, 6])); // 1,2,3,4,5,6
  alert(arr.concat([3, 4], 5, 6)); // 1,2,3,4,5,6
  ```

  - 인자로 객체가 넘어오면 객체는 분해되지 않고 통으로 복사되어 더해진다.

    ```js
    let arr = [1, 2];

    let arrayLike = {
      0: 'something',
      length: 1,
    };

    alert(arr.concat(arrayLike)); // 1,2,[object Object]
    ```

    `Symbol.isConcatSpreadable`이 있으면 concat은 객체를 배열 취급

    ```js
    let arr = [1, 2];

    let arrayLike = {
      0: 'something',
      1: 'else',
      [Symbol.isConcatSpreadable]: true,
      length: 2,
    };

    alert(arr.concat(arrayLike)); // 1,2,something,else
    ```

<br>

## 배열 반복작업

- forEach() : 반복작업 하기

  ```js
  /*기본 구문*/
  arr.forEach(function (item, index, array) {});

  let arr = ['Bilbo', 'Gandalf', 'Nazgul'];
  arr.forEach((item, index, array) => {
    alert(`${item} is at index ${index} in ${array}`);
  });
  ```

<br>

## 배열 탐색

- `indexOf(item,from)`, `lastIndexOf(item,from)`, `includes(item,from)` : 문자열과 동일하게 item이 from부터 있는지 `검사`하는 함수

  - 내부적으로 요소를 찾을때 `===`을 사용한다.

  - includes는 `NaN`도 처리
    ```js
    const arr = [NaN];
    alert(arr.indexOf(NaN)); // -1 (=== 는 NaN엔 동작하지 않으므로 0이 출력되지 않습니다.)
    alert(arr.includes(NaN)); // true
    ```

- find(function) : 객체로 이루어진 배열이 있을때 특정 조건에 부합하는 객체를 배열내에서 찾을 때 이용

  - `조건에 부합하는(true가 되는) 하나의 요소만 찾는다`

  ```js
  /*기본 구문*/
  let result = arr.find(function (item, index, array) {
    // true가 반환되면 반복이 멈추고 해당 요소를 반환
    // 조건에 해당하는 요소가 없으면 undefined를 반환
  });
  ```

  - function으로 화살 함수를 이용가능하다.

    ```js
    let users = [
      { id: 1, name: 'John' },
      { id: 2, name: 'Pete' },
      { id: 3, name: 'Mary' },
    ];

    let user = users.find((item) => item.id == 1);

    alert(user.name); // John
    ```

- filter(function) : `조건이 충족` 되는 모든 요소를 담은 `배열을 반환`

  ```js
  /*기본 구문*/
  let results = arr.filter(function (item, index, array) {
    // 조건을 충족하는 요소는 results에 순차적으로 더해집니다.
    // 조건을 충족하는 요소가 하나도 없으면 빈 배열이 반환됩니다.
  });
  ```

  - find()와 마찬가지로 function으로 화살 함수를 이용가능하다.

    ```js
    let users = [
      { id: 1, name: 'John' },
      { id: 2, name: 'Pete' },
      { id: 3, name: 'Mary' },
    ];

    // 앞쪽 사용자 두 명을 반환합니다.
    let someUsers = users.filter((item) => item.id < 3);

    alert(someUsers.length); // 2
    ```

<br>

## 배열 변형

- map(function) : 배열 요소 `전체를 대상`으로 함수를 호출하고 결과를 `배열로 반환`

  ```js
  let result = arr.map(function (item, index, array) {});

  let lengths = ['Bilbo', 'Gandalf', 'Nazgul'].map((item) => item.length);
  alert(lengths); // 5,7,6
  ```

- sort(function) : 배열을 정렬

  기본적으로 배열의 내부 요소를 문자열로 취급하여 재정렬한다.

  ```js
  let arr = [1, 2, 15];
  arr.sort();
  alert(arr); // 1, 15, 2
  ```

  따라서 숫자로 비교하려면 내부에 함수를 추가해주면 된다.

  ```js
  let arr = [1, 2, 15];
  arr.sort((a, b) => a - b);
  alert(arr); // 1, 2, 15
  ```

  비교 함수가 `양수`를 반환하는 경우는 첫번째 인수가 두번째보다 `크다`이고 `음수`는 `작다`이다.

  > 문자열은 유니코드 기준으로 정렬하기 때문에 발음기호등 정확하지 않을 수 있어 str.localeCompare(str2)를 이용하면 정확하게 비교가 가능하다.

- reverse() : 배열을 역순으로 정렬

- split(delim) : `구분자(delim)`을 기준으로 문자열을 쪼개준다.

  ```js
  let arr = 'Bilbo, Gandalf, Nazgul, Saruman'.split(', ');
  alert(arr); // Bilbo, Gandalf,Nazgul, Saruman

  let arr2 = 'Bilbo, Gandalf, Nazgul, Saruman'.split(', ', 2);
  alert(arr2); // Bilbo, Gandalf
  ```

  - delim으로 `빈문자열 ('')`을 주면 글자 단위로 분리할 수 있다.

- join(glue) : split과 반대의 기능으로 인수를 사용해 배열 요소를 `모두합친 문자열`을 만들어준다.

  ```js
  let arr = ['Bilbo', 'Gandalf', 'Nazgul'];
  let str = arr.join(';');
  alert(str); // Bilbo;Gandalf;Nazgul
  ```

- reduce() : 배열을 기반으로 `값 하나를 도출`해 낼때 사용

  ```js
  /*기본 구문*/
  let value = arr.reduce(
    function (accumulator, item, index, array) {
      // ...
    },
    [initial]
  );
  ```

  ```js
  let arr = [1, 2, 3, 4, 5];

  let result = arr.reduce((sum, current) => sum + current, 0);

  alert(result); // 15
  ```

  <br>

## Array.from

이터러블이나 유사 배열을 받아 진짜 `Array`를 생성해주는 함수

객체나 문자열은 대표적인 내장 이터러블

- 이터러블(iterable) : Symbol.iterator가 구현된 객체

- 유사 배열(array-like) : 인덱스와 length 프로퍼티가 있어서 배열처럼 보이는 객체

```js
let arrayLike = {
  0: 'Hello',
  1: 'World',
  length: 2,
};

let arr = Array.from(arrayLike);
alert(arr.pop()); // World
```

이를 이용해 배열을 초기화도 해줄수 있다.

```js
let arr = Array.from({ length: 5 }, () => 0);
```

이는 아래와 같은 기능을 한다.

```js
let arr = [];
arr.fill(0, 0, 5);
```
