# 내장 프로토타입

빈 객체를 생성해도 자동으로 Object.prototype을 `[[Prototype]]`으로 갖고 Object.prototype 의 [[Prototype]] 은 없다. (null)

`Array`, `Function` 등 특수 객체들은 위의 체인으로 모두 Objcect.prototype을 가지고있다.

```js
let arr = [1, 2, 3];

// arr은 Array.prototype을 상속받았나요?
alert(arr.__proto__ === Array.prototype); // true

// arr은 Object.prototype을 상속받았나요?
alert(arr.__proto__.__proto__ === Object.prototype); // true

// 체인 맨 위엔 null이 있습니다.
alert(arr.__proto__.__proto__.__proto__); // null
```

<br>

`String`, `Number`, `Boolean`과 같은 원시값 객체는 앞서 배웠듯이 객체가 아니기 때문에 임시 래퍼 객체가 생성되어, 메서드를 호출하고 사라진다.

이 임시 래퍼 객체또한 Object.prototype을 상위 체인으로 갖는다.

<br>

## 네이티브 프로토타입 변경

```js
String.prototype.show = function () {
  alert(this);
};

'BOOM!'.show(); // BOOM!
```

위와 같이 객체 내장의 함수를 변경하거나 추가를 할 수 있지만, 프로토타입은 전역으로 영향을 미치기 때문에 오류발생이 커 함부로 사용하지는 말자!

`babel`에서도 나온 개념인 `polyfil`를 만들때 주로 사용되는 방법

<br>

## 프로토타입 빌려오기

한 객체에서 다른 객체로 복사 하거나, 객체에서 Array함수를 이용하고 싶을때와 같이 함수를 빌려오고 싶을때(엄밀히 보면 함수 복사) 사용될 수 있다.

```js
let obj = {
  0: 'Hello',
  1: 'world!',
  length: 2,
};

obj.join = Array.prototype.join;

alert(obj.join(',')); // Hello,world!
```

위와 같이 obj의 프로퍼티로 Array의 join 메서드를 복사하는 방법이 있으며,

```js
let obj = {
  0: 'Hello',
  1: 'world!',
  length: 2,
};

obj.__proto__ = Array.prototype;

alert(obj.join(',')); // Hello,world!
```

와 같이 Array객체를 상속받는 방법을 이용해 join 메서드를 이용하는 방법이 있다.
