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
