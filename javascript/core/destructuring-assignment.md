# 구조 분해 할당

객체나 배열을 변수로 `분해`할 수 있게 해주는 특별한 문법

<br>

# 배열 분해

## 사용법

```js
let arr = ['Bora', 'Lee'];

let [firstName = 'First', surname = 'last'] = arr;

alert(firstName); // Bora
alert(surname); // Lee
```

## 특징

- 우측에는 배열 뿐만이 아닌 모든 이터러블이 올 수 있다.

  ```js
  let [firstName, surname] = 'Bora Lee'.split(' ');
  alert(firstName); // Bora
  alert(surname); // Lee
  ```

  ```js
  let [one, two, three] = new Set([1, 2, 3]);
  ```

- 변수 교환하는데 사용할 수 있다.

  ```js
  let guest = 'Jane';
  let admin = 'Pete';

  [guest, admin] = [admin, guest];
  ```

- `...`으로 나머지 요소를 배열로 가져올 수 있다.

  ```js
  let [name1, name2, ...rest] = ['kim', 'lee', 'hong', 'No'];

  alert(rest.length); //2
  ```

- 할당할 값이 없으면 `undefined` 취급한다
  ```js
  let [first, last] = [];
  alert(first); //undefined
  alert(last); //undefined
  ```

<br>

# 객체 분해

## 사용법

```js
let {var1, var2} = {var1:…, var2:…}
```

아래 보이는 것처럼 순서가 바뀌어도 key에 상응하는 변수에 연결이 된다.

```js
let { height, width, title } = { title: 'Menu', height: 200, width: 100 };
alert(title); // Menu
alert(width); // 100
alert(height); // 200
```

## 특징

- 변수명을 key값이 아닌 목표 변수(`별칭`)로 설정 할 수 있다.

  ```js
  let options = {
    title: 'Menu',
    width: 100,
    height: 200,
  };

  let { width: w, height: h, title } = options;

  // width -> w
  // height -> h
  // title -> title

  alert(title); // Menu
  alert(w); // 100
  alert(h); // 200
  ```

- let으로 새로운 변수 선언이 아닌 기존 변수를 이용해 할당이 가능하다

  ```js
  ({ title, width, height } = { title: 'Menu', width: 200, height: 100 });
  ```

  이때, `()`로 안묶어 주면 `{}`를 표현식이 아닌 코드블럭으로 인식하여 에러가 난다.

- 함수의 인자로 객체를 전달시 자동으로 분해해서 사용한다.

  ```js
  let options = {
    title: 'My menu',
    items: ['Item1', 'Item2'],
  };

  function showMenu({ title = 'Menu', width = 100, height = 200 } = {}) {
    alert(`${title} ${width} ${height}`);
  }

  showMenu(); // Menu 100 200
  ```
