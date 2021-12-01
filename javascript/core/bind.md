# 함수 바인딩

함수는 객체 메서드를 콜백으로 전달할 때 `this`정보가 사라지는 문제가 존재 하는데 이를 해결하기 위해 전달과 동시에 this의 객체도 전달하는 방법

<br>

## 1. 래퍼 함수 (wrapper)

기존은 같은 외부 렉시컬 환경에서 객체의 함수 프로퍼티만 가져오기 때문에 this가 어떤 객체인지 모르는 문제가 발생했는데 함수로 한번 감싸주어 내부 렉시컬 환경을 만들어 외부에서 user를 받아 호출하는 방법으로 해결하는 방법

```js
let user = {
  firstName: 'John',
  sayHi() {
    alert(`Hello, ${this.firstName}!`);
  },
};

setTimeout(function () {
  user.sayHi(); // Hello, John!
}, 1000);

setTimeout(() => user.sayHi(), 1000); // Hello, John!
```

하지만, 이방법은 외부의 user객체정보를 그대로 이용하기 때문에 setTiemout이 실행전에 user객체 정보가 바뀌면 실행 값도 바뀐다.

<br>

## 2. bind

this를 수정하게 해주는 내장 메서드

`func.bind(context)`는 함수처럼 호출 가능한 `특수 객체`를 반환한다. (this가 context로 고정된 함수를 반환 = > this가 고정된 func를 호출하는 효과)

```js
let user = {
  firstName: 'John',
  sayHi() {
    alert(`Hello, ${this.firstName}!`);
  },
};

let sayHi = user.sayHi.bind(user);

sayHi(); // Hello, John!

setTimeout(sayHi, 1000); // Hello, John!

user = {
  sayHi() {
    alert('또 다른 사용자!');
  },
};
```

위처럼 user객체를 함수에 고정시켜 실행시키기 때문에 user의 프로퍼티가 바뀌어도 기존의 함수와 동일한 결과를 출력한다.

<br>

### this뿐만이 아닌 인수도 바인딩이 가능

```js
function mul(a, b) {
  return a * b;
}

let double = mul.bind(null, 2); //this는 따로 없기때문에 null

alert(double(3)); // = mul(2, 3) = 6
alert(double(4)); // = mul(2, 4) = 8
```

이처럼 함수의 매개변수를 고정하여 새로운 함수를 만드는 것을 `부분 적용`이라고 한다.

<br>

## 화살표함수와 bind의 차이

화살표 함수는 어떤것도 바인딩 시키지 않는다. (this가 없는 것)

this값을 외부 렉시컬 환경에서 찾는다.

bind는 this를 고정시키는 것
