# Class

JS에서도 클래스를 사용하여 객체 지향적으로 프로그래밍이 가능하다.

## 표현식

class 를 이용해 선언하고 `new`를 이용해 생성

```js
class User {
  constructor(name) {
    //생성자
    this.name = name;
  }

  sayHi() {
    alert(this.name);
  }
}

let user = new User('John');
user.sayHi();
alert(typeof User); // function
alert(User === User.prototype.constructor); // true
alert(User.prototype.sayHi); // alert(this.name);
alert(Object.getOwnPropertyNames(User.prototype)); // constructor, sayHi
```

- 기명 표현식

```js
let User = class {
  sayHi() {
    alert('Hello');
  }
};
new User().sayHi();

alert(MyClass); //error
```

- 클래스 동적 생성

```js
function makeClass(phrase) {
  // 클래스를 선언하고 이를 반환함
  return class {
    sayHi() {
      alert(phrase);
    }
  };
}

// 새로운 클래스를 만듦
let User = makeClass('Hello');

new User().sayHi(); // Hello
```

## 원리

위의 코드를 예로 `User`라는 함수를 만들고 함수는 생성자`constructor`로 부터 생성하고 클래스 내의 메서드들은 `User.prototype`에 저장한다

## 일반적인 생성자 함수와 다른점

1. class로 만든 함수엔 특수 내부 프로퍼티인 `[[FunctionKind]]:"classConstructor"`가 존재한다. 따라서 `new`를 붙이지 않고 `User();`와 같이 그냥 호출하게 된다면 잘못 사용된것을 감지하고 에러를 발생시킨다.

2. prototype의 메서드 전체의 `enumerable`플래그는 false로 클래스 메서드는 열거가 불가능 하다.

3. 항상 `use strict`모드로 실행되어 클래스 생성자 안의 코드 전체에 자동으로 엄격모드가 적용된다.

## getter/setter

리터럴을 사용해 만든 객체처럼 getter/setter를 만들 수 있다.

```js
class User {
  constructor(name) {
    // setter를 활성화합니다.
    this.name = name;
  }

  get name() {
    return this._name;
  }

  set name(value) {
    if (value.length < 4) {
      alert('이름이 너무 짧습니다.');
      return;
    }
    this._name = value;
  }
}

let user = new User('John');
alert(user.name); // John

user = new User(''); // 이름이 너무 짧습니다.
```

## 클래스 필드

`프로퍼티이름 = 값` 으로 필드를 추가가 가능하며, Obj.prototype이 아닌 개별 객체에만 클래스 필드가 설정된다.

```js
class User {
  name = 'John';
}

let user = new User();
alert(user.name); // John
alert(User.prototype.name); // undefined
```
