# 프로토 타입

js의 객체는 [[Porototype]]이라는 숨김 프로퍼티를 갖고 이 프로퍼티의 값은 null/다른 객체의 참조를 갖는다.

다른 객체를 참조하는 경우 참조 대상을 `프로토 타입`이라고 한다.

## 프로토타입 상속

객체에서 프로퍼티를 읽을때, 해당 프로퍼티가 없으면 자동으로 `프로토타입`에서 프로퍼티를 찾는데 이런 동작 방식을 `프로토타입 상속`이라 하고 상속받은 프로퍼티를 `상속 프로퍼티`라고 한다.

## **proto**

[[Prototype]]용 getter/setter

```js
let animal = {
  eats: true,
};
let rabbit = {
  jumps: true,
};

rabbit.__proto__ = animal;
```

위 와 같이 객체에 숨김 프로퍼티를 추가 할 수 있다.

최근에느 `__proto__`대신 `Object.getProtoypeOf` / `Object.setPrototypeOf`를 이용하여 `숨김 프로토 타입`을 접근한다.

## 제약사항

- 순환참조 허용 X

- **proto**의 값은 null이나 객체만 가능하여 다른 자료형은 무시한다.
- 객체엔 하나의 [[Prototype]]만 존재하여 두 개 이상의 객체를 상속 받지 못한다.

## this

프로토타입에 영향을 받지 않는다.

메서드를 객체에서 호출하든, 프로토타입에서 호출하든 this는 `.`앞에 있는 객체가 된다.

=> 즉, 메서드는 공유하지만 객체의 상태는 공유하지 않는다.

## for...in

상속 프로퍼티중 열거 가능한 프로퍼티들도 순회 대상에 포함

```js
let animal = {
  eats: true,
};

let rabbit = {
  jumps: true,
  __proto__: animal,
};

// Object.keys는 객체 자신의 키만 반환합니다.
alert(Object.keys(rabbit)); // jumps

// for..in은 객체 자신의 키와 상속 프로퍼티의 키 모두를 순회합니다.
for (let prop in rabbit) alert(prop); // jumps, eats
```

### obj.hasOwnProperty(key)

자기 객체의 프로퍼티만 접근

```js
let animal = {
  eats: true,
};

let rabbit = {
  jumps: true,
  __proto__: animal,
};

for (let prop in rabbit) {
  let isOwn = rabbit.hasOwnProperty(prop);

  if (isOwn) {
    alert(`객체 자신의 프로퍼티: ${prop}`); // 객체 자신의 프로퍼티: jumps
  } else {
    alert(`상속 프로퍼티: ${prop}`); // 상속 프로퍼티: eats
  }
}
```

## 상속프로퍼티접근 vs 직접프로퍼티 접근 시간 비교

```js
let head = {
  glasses: 1,
};

let table = {
  pen: 3,
  __proto__: head,
};

alert(head.glasses);
aler(table.glasses);
```

Q. 어떤게 더 빠르게 접근이 가능할까?

A. 성능차이가 없다. 모던 js엔진 기준으로 프로퍼티가 어디서 발견했는지 기억했다가 그 정보를 재사용(캐시 기능)하고 변경이 생기면 내부 캐시를 변경

<br>

## 메서드

- Object.create(proto, [설명자]) : proto를 참조하는 빈 객체를 만들기
- Object.getPrototypeOf(obj) : obj의 [[Prototype]] 반환
- Object.setPrototypeOf(obj, proto) : obj의 [[Prototype]]을 proto로 설정

```js
let animal = {
  eats: true,
};

// 프로토타입이 animal인 새로운 객체를 생성합니다.
let rabbit = Object.create(animal);

alert(rabbit.eats); // true

alert(Object.getPrototypeOf(rabbit) === animal); // true

Object.setPrototypeOf(rabbit, {}); // rabbit의 프로토타입을 {}으로 바꿉니다.
```

### for...in 보다 효과적인 객체 복제 ( 프로토타입 포함 )

```js
let clone = Object.create(Object.getPrototypeOf(obj), Object.getOwnPropertyDescriptors(obj));
```

## Q. 프로토타입을 자주 변경해도 될까?

A. 원한다면 언제든 수정이가능하나, js엔진 자체가 처음 객체 생성 후 수정하지 않는 시나리오로 최적화 되어있기 대문에, 프로퍼티 접근은 속도가 느려 질 수 있다.
