# this

`this`는 현재 객체를 가르키는 키워드

<br>

## 특징

- 모든 함수에 this를 사용할 수 있다.
  <br>객체가 없어도 함수를 호출할 수 있다.

  ```js
  function sayHi() {
    alert(this);
  }
  sayHi(); //undefined
  ```

  엄격모드일때는 undefined를 할당하고, 엄격모드가 아니라면 전역객체를 참조한다. _(브라우저 환경에선 window라는 전역 객체)_

- this는 `런타임`에 결정된다.

  ```js
  let user = { name: 'John' };
  let admin = { name: 'Admin' };

  function sayHi() {
    alert(this.name);
  }

  user.f = sayHi;
  admin.f = sayHi;

  user.f(); //John (this == user)
  admin.f(); //Admin(this == admin)

  admin['f'](); //John (this == user)
  user['f'](); //Admin(this == admin)
  ```

  - 위와 같이 하나의 함수로 여러 객체에서 재사용할 수 있다는 장점이 있다.

  - this가 무엇을 가리키는지 헷갈려 실수 할 수도 있다는 단점이 있다.

- 화살표 함수에는 this가 없다
  <br>화살표 함수에서 this를 참조하면 `평범한` 외부 함수에서 this값을 가져온다.

      ```js
      let user = {
          firstName: "보라",
          sayHi() {
              let arrow = () => alert(this.firstName);
              arrow();
          }
      };
      user.sayHi(); // 보라
      ```
      ```js
      let user = {
          firstName: "보라",
          sayHi : () => alert(this.firstName);
      };
      user.sayHi(); // undefined
      ```
