# 함수 선언식

```js
function sayHello() {
  alert('hello');
}
sayHello();

let func = sayHello(); //이처럼
fucn(); //변수에 대입도 가능
```

# 함수 표현식

js는 함수를 `특별한 동작을 하는 구조`가 아닌 `특별한 종류의 값`으로 취급

따라서, 함수를 복사해 다른 변수에 할당할 수도 있다.

아래코드를 보면 함수의 이름없이 변수에 할당하는 것을 볼 수 있다.

```js
let sayHello = fucntion(){
    alert( "hello");
}

sayHello();
```

# 콜백 함수

함수를 함수의 인자로 전달하고, 필요할때 인수로 전달한 그 함수를 나중에 호출하는 것

아래의 코드를 보면 yes의 인자로 alert('동의')가, no의 인자로 alert('취소')가 할당되는 것을 볼수 있다.

```js
function ask(question, yes, no) {
  if (confirm(question)) yes();
  else no();
}

ask(
  '동의하십니까?',
  function () {
    alert('동의하셨습니다.');
  }, //함수 표현식
  function () {
    alert('취소 버튼을 누르셨습니다.');
  } //함수 이름 없이 사용
);
```

# 함수 표현식과 함수 선언문 차이

## 1. js엔진이 함수를 생성하는 시기

함수 표현식은 실제 실행 흐름이 도달했을때 생성하고, 함수 선언문은 정의되기전에도 호출할 수 있다.
<br>
-> 함수 선언은 전역함수로 선언이 되며, js는 스크립트 실행전 모든 선언문을 찾고 생성후에 실행되기 때문이다.

<br>

그래서, 아래와 같이 선언문 전에 호출을 해도 실행을 하면 동작이 가능하다.

```js
sayHi('John');

function sayHi(name) {
  alert(`Hello, ${name}`);
}
```

하지만 함수 표현식은 불가능하다.

## 스코프

함수 선언문은 함수가 선언된 코드 블럭 안에서만 유효하다.

만약 반복문이나 if와같이 `{}`안에 함수를 선언학고 밖에서 호출할 시 오류가 발생한다.

```js
if (true) {
  function welcome() {
    alert('안녕!');
  }
}

welcome(); // Error: welcome is not defined
```

위와 같이 사용하고 싶다면 함수 표현식을 사용.

```js
let welcome;
if(true){
    welcome = fuction(){
        alert("안녕!");
    }
}

welcome(); //안녕!
```

# 화살표 함수

함수 표현식보다 단순하고 간결한 문법으로 함수를 생성.

컨택스트가 있는 긴코드보다 자체 `컨텍스트`가 없는 짧은 코드를 담을 용도

```js
let sum = function (a, b) {
  return a + b;
};
```

```js
let sum = (a, b) => a + b;
```

인수가 하나밖에 없다면 괄호를 생략 가능하고, 인수가 없을땐 괄호 생략 불가능하다.

```js
let sum = (a) => a;

let sum2 = () => 1;
```

함수 내용이 여러줄일때는 중괄호를 이용하여 묶어준다.

```js
let sum = (a, b) => {
  let sum = a + b;
  return a + b;
};
```

## 특징

- this가 없기때문에 사용이 불가능하다.
  <br>this를 호출하면 외부에서 값을 가져온다.
  <br>this가 없기 때문에 new와 함께 사용이 불가능해 생성자 함수로 사용할 수 없다.

- arguments가 없다.

```
unction defer(f, ms) {
  return function() {
    setTimeout(() => f.apply(this, arguments), ms)
  };
}

function sayHi(who) {
  alert('안녕, ' + who);
}

let sayHiDeferred = defer(sayHi, 2000);
sayHiDeferred("철수"); // 2초 후 "안녕, 철수"가 출력됩니다.
```

위와 같은 코드를 이용하려면 아래와 같이 args와 ctx를 반드시 생성해줘야한다.

```js
function defer(f, ms) {
  return function (...args) {
    let ctx = this;
    setTimeout(function () {
      return f.apply(ctx, args);
    }, ms);
  };
}
```

<br>

## 매개변수

실제 함수의 매개변수 인자는 2개로 선언을 했어도, 호출 시 매개변수를 여러개 넣어주어도 에러가 나지 않는다.

```js
function sum(a, b) {
  return a + b;
}

alert(sum(1, 2, 3, 4, 5)); //3
```

`arguments`라는 특수한 `유사 배열 객체`가 존재해 이를 이용해 모든 인수를 접근가능하나 화살표 함수에는 `arguments`가 없다.

```js
function hello() {
  alert(arguments.length);
  alert(arguments[0]);
}

hello('hi', 'hello'); // 2, hi
```

- spread 문법 :

  함수에 배열의 요소를 매개변수로 여러개를 입력할때, 일일히 수동입력이 아닌 자동으로 입력할 수 있게 해주는 문법

  말그대로 array를 전개시켜주는 문법으로 배열앞에 `...`을 붙여주면된다.

  ```js
  let arr = [3, 5, 1];
  alert(Math.max(...arr)); //  5
  ```

  배열뿐만이 아니라 `이터러블 객체`라면 모두 사용가능하다.

  ```js
  let str = 'hello';
  alert([...str]); //h,e,l,l,o
  ```

  이는 문법 내부에서 iterator를 사용해 요소를 수집해 각각의 값을 반환하여 `[]`로 감싸 문자 목록들을 배열로 만들어주기 때문에 다음과 같은 출력결과를 보인다.

  따라서 `[...obj]`을 이용해 배열을 만들 수 있지만 `Array.from(obj)`와 비교해서 `[...obj]`는 유사 배열 객체에는 사용할 수 없다는 단점이 있어 무언가를 배열로 만들때는 `Array.from()`을 이용한다.
