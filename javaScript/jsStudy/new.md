# new연산자와 생성자 함수

유사한 객체를 여러개 만들어야 할때 이용하면 쉽게 만들 수 있다.

생성자 함수 앞에 new를 붙여 객체 할당

생성자 함수는 첫글자를 `대문자`로!

<Br>

## 동작 원리

내부적으로 빈객체 this를 만들어 새로 프로퍼티를 추가하고 그 this를 반환하게 된다.

```js
/*아래와 같은 함수가 있다고 한다면*/
function User(name) {
  this.name = name;
  this.isAdmin = false;
}

let user = new User('Jack'); //을 실행 하면

function User(name) {
  // this = {};  (빈 객체가 암시적으로 만들어짐)

  // 새로운 프로퍼티를 this에 추가함
  this.name = name;
  this.isAdmin = false;

  // return this;  (this가 암시적으로 반환됨)
}
```

그 결과로 아래와 같은 코드가 된다.

일회성으로 보면 아래의 방법이 간단할 수 있으나, name이 다른 객체를 수십개 만든다고 한다면 위와 같은 방법이 간단 할 수 있다.

```js
let user = {
  name: 'Jack',
  isAdmin: false,
};
```

<br>

## 익명 생성자 함수

복잡한 객체를 만들어야하는데 재사용할 필요가 없을때는 익명함수로 생성자함수를 생성하여 객체할당을 할 수도 있다.

```js
let user = new function(){
    this.name = "hong",
    this.isAdmin = false,
    /*
    그 외 함수
    */
}
```

<br>

## new.target

함수 내에서 `new.target`은 해당 함수가 new와 함께 호출되었다면 true, 아니면 false를 가르킨다.

<br>

## Return

생성자 함수는 `동작 원리`에서 설명한 것처럼 this를 내부적으로 만들어 this를 반환하기 때문에 return을 써줄 필요가 없으나 `객체`를 return하게 되면 this 대신 `객체`를 return한다.

`객체`가 아닌 그 외의 `원시형`을 return시 `this`를 return한다.
