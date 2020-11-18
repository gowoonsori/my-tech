# var

초기에 js 변수 선언방식이다.

<br>

## 특징

- 블록 스코프가 없다.

- 이미 존재하는 변수가 있으면 이전의 변수를 무시한다.

  ```js
  var user = 'Pete';
  var user = 'John';

  alert(user); // John
  ```

  블록 스코프가 없는데다가 이전의 변수를 무시하고 덮어쓰기 때문에 작업시 오류를 범할 확률이 높다.

- 선언하기 전에 사용할 수 있다.
  var 선언은 선언 위치에 상관없이 함수내에서 선언했다면 함수가 시작될때,전역에서 선언했다면 스크립트가 시작될 때 처리된다.

        ```js
        function sayHi() {
            phrase = "Hello";
            alert(phrase);
            var phrase;
        }
        sayHi();
        ```

- 선언은 호이스팅 되지만 할당은 호이스팅 되지 않는다.

  ```js
  function sayHi() {
    alert(phrase);
    var phrase = 'Hello';
  }
  sayHi(); //undefined
  ```

  위의 함수의 내부 동작방식은 다음과 같다.

  ```js
  function sayHi() {
    //var phrase;

    alert(phrase);
    var phrase = 'Hello';
  }
  sayHi(); //undefined
  ```

<br>

## 즉시 실행 함수 표현식 (IIFE, Immediately-Invoked Function Expressions)

js는 함수 선언문으로 정의한 함수를 정의와 동시에 바로 호출하는 것을 허용하지 않기 때문에 바로 실행하는 것이 불가능하다.

하지만 함수 선언문을 `()`로 감싸 선언문이 아닌 표현식으로 인식하도록 속여 함수의 이름이 없으며, 즉시 호출이 가능한 함수를 작성할 수 있다.

```
(function() {
  alert("함수를 괄호로 둘러싸기");
})();

(function() {
  alert("전체를 괄호로 둘러싸기");
}());

!function() {
  alert("표현식 앞에 비트 NOT 연산자 붙이기");
}();

+function() {
  alert("표현식 앞에 단항 덧셈 연산자 붙이기");
}();
```

<br>

# let

# const

c/c++의 const, java의 final과 같이 상수변수를 선언하기위한 방식
