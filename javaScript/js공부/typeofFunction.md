# 함수의 자료형

js에서 함수는 값으로 취급한다고 했다. 그러면 자료형은 무엇일까?

함수는 `호출이 가능한 행동 객체` 이다.

함수는 호출 할수도 있으며 객체처럼 함수에 프로퍼티를 추가/제거하거나 참조를 통해 전달할 수도 있다.

## 함수 객체의 프로퍼티

- name : 함수의 이름을 반환하고 익명 함수라도 자동으로 할당이 된다.

  익명함수나 기본값을 이용해 자동 할당으로 해주는데 이를 `contextual name`이라고 한다.

  ```js
  let sayHi = function () {
    alert('Hi');
  };
  alert(sayHi.name); // sayHi

  function f(sayHi = function () {}) {
    alert(sayHi.name);
  }
  f(); // sayHi
  ```

  하지만 적절한 이름을 추론하는 게 불가능 한 상황은 `빈 문자열`이 저장된다.

- length : 함수의 매개변수의 개수

  - `다형성` : 인수의 종류에 따라 인수를 다르게 처리하는 방식

- 커스텀 프로퍼티 : 함수에 자체적으로 만든 프로퍼티를 추가가 가능하다

  ```js
  function makeCounter() {
    // let count = 0 대신 아래 메서드(프로퍼티)를 사용함

    function counter() {
      return counter.count++;
    }

    counter.count = 0;

    return counter;
  }

  let counter = makeCounter();
  alert(counter()); // 0
  alert(counter()); // 1
  ```

  `클로저`를 이용하여 외부에서 함수 내부의 변수를 bind하여 제어 할 수 있게 하였는 데, 커스텀 프로퍼티를 이용하면 외부에서 값을 수정이 가능하다.

  하지만, 프로퍼티는 변수`let`과 관계가 전혀 없다. 변수가 아니다.

<br>

## 기명 함수 표현식

함수 선언식이 아닌 함수 표현식방식에 익명함수가 아닌 이름을 붙인 함수를 생성시 함수 내부에 자기 자신을 호출 할 수 있다.

하지만 함수 표현식의 함수를 독립적으로 사용은 불가능하다.

```js
let sayHi = function func(who) {
  if (who) {
    alert(`Hello, ${who}`);
  } else {
    func('Guest'); // func를 사용해서 자신을 호출합니다.
  }
};

sayHi(); // Hello, Guest
func(); // Error, func is not defined
```
