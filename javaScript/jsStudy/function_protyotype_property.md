# 함수의 prototype 프로퍼티

생성자 함수를 이용하여 객체를 생성시 [[Prototype]]을 설정하는 방법으로 기본 문법은 아래와 같다.

```js
F.prototype = obj;
```

```js
let animal = {
  eats: true,
};

function Rabbit(name) {
  this.name = name;
}

Rabbit.prototype = animal;

let rabbit = new Rabbit('White Rabbit'); //  rabbit.__proto__ == animal

alert(rabbit.eats); // true
```

이때 `prototype`은 **proto**와 같은 객체가 아닌 `Rabbit`에 정의된 일반 프로퍼티이다.

`F.prototype`은 `new`문법을 통해 호출할때만 사용을 하여 새로운 객체에 `[[Prototype]]`을 할당해주는 프로퍼티

## constructor 프로퍼티

모든 함수는 기본적으로 `constructor`이라는 프로퍼티를 갖고있는 객체를 가리키는 `prototype`를 갖는데, `constructor`는 함수 자신을 가리키는 프로퍼티

```js
function Rabbit() {}

/* 기본 prototype
Rabbit.prototype = { constructor: Rabbit };
*/

alert(Rabbit.prototype.constructor == Rabbit); // true

let rabbit = new Rabbit(); // {constructor: Rabbit}을 상속받음

alert(rabbit.constructor == Rabbit); // true (프로토타입을 거쳐 접근함)
```
