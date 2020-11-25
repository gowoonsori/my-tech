# 프로퍼티 종류

- 데이터 프로퍼티 : 지금까지 사용, 설명한 모든 프로퍼티 (key, value , 설명자, 함수)

- 접근자 프로퍼티 : 엄밀히 보면 함수로 get과 set역할하는 프로퍼티로 외부에서 보면 일반적인 프로퍼티 처럼 보인다.

<br>

## 접근자 프로퍼티 (getter / setter)

```js
let user = {
  name: 'John',
  surname: 'Smith',

  get fullName() {
    return `${this.name} ${this.surname}`;
  },
  set fullName(value) {
    [this.name, this.surname] = value.split(' ');
  },
};

alert(user.fullName); // John Smith
```

위와 같이 getter와 setter를 이용해 `가상`의 프로퍼티를 구성할 수 있고, 이는 읽고 쓸 순 있지만 실제로 존재하진 않는다.

접근자 프로퍼티에는 설명자 `value`와 `writable`이 없고 get/set함수가 존재하며 프로퍼티는 `접근자 프로퍼티`와 `데이터 프로퍼티`중 한종류에만 속한다.

<br>

## 활용 방법

1. 프로퍼티 값을 통제하기 위해 wrapper처럼 사용하기

```js
let user = {
  get name() {
    return this._name;
  },

  set name(value) {
    if (value.length < 4) {
      alert('입력하신 값이 너무 짧습니다. 네 글자 이상으로 구성된 이름을 입력하세요.');
      return;
    }
    this._name = value;
  },
};

user.name = 'Pete';
alert(user.name); // Pete

user.name = ''; // 입력하신 값이 너무 짧습니다. 네 글자 이상으로 구성된 이름을 입력하세요.
```

위 처럼 set함수를 통해 프로퍼티 입력 단계에서 제어하기 위해 사용할 수 있다.

<br>

1. 비슷한 개념의 프로퍼티를 (있어도 나쁠것이 없는) 생성할때, 기존의 프로퍼티 값을 이용하여 프로퍼티를 생성할때

```js
function User(name, birthday) {
  this.name = name;
  this.birthday = birthday;

  // age는 현재 날짜와 생일을 기준으로 계산됩니다.
  Object.defineProperty(this, 'age', {
    get() {
      let todayYear = new Date().getFullYear();
      return todayYear - this.birthday.getFullYear();
    },
  });
}

let john = new User('John', new Date(1992, 6, 1));

alert(john.birthday); // birthday를 사용할 수 있습니다.
alert(john.age); // age 역시 사용할 수 있습니다.
```

태어난 날을 이용하여 객체를 생성할때 이를 이용해 age를 계산하여 생성하고싶을때 이용하면 유용하게 사용할 수 있다.
