# 객체

`key : value` 쌍으로 구성된 자료형으로 한쌍 한쌍을 `프로퍼티 (property)`라고 한다.

key엔 문자형/심볼형, value에는 모든 자료형이 올 수 있다.

일반 객체뿐만 아닌 `Array`,`Date`,`Error`등의 다양한 종류의 객체가 있다.

<br>

## 빈 객체 생성방식

```
let user = new Object(); //사용자 정의 객체 방식 ( 생성자 함수 이용 방식 )
let user = {};          //객체 리터럴 방식
```

<Br>

## 특징

- 일반 변수와 달리 참조에 의해 저장되고 복사된다.

  ```js
  let user = { name: 'hong' };
  let admin = user;
  admin.name = 'kim';
  alert(user.name); //hong
  ```

  - 참조에 의해 저장, 복사되기 때문에 `일치 연산자`도 true 리턴
    ```js
    alert(user === admin); //true
    ```

- `delete`이용해 프로퍼티 삭제 가능

- 프로퍼티 이름(key)이 복수의 단어라면 `따옴표`로 묶어줘야 한다.

  ```js
  let user = {
    'buy pencil': false,
  };
  ```

  - 점 표기법으로 프로퍼티 값을 읽을 수 없다.
    ```js
    user.buy pencil = true; //(x)
    ```

- `const`로 생성한 객체이더라도 전체적으로 다른 객체를 대입하는 것은 안되나 프로퍼티는 수정이 가능하다.

  ```js
  let user = {
    name: 'hong',
  };
  user.name = 'kim'; //(o)
  user = { name: 'kim' }; //(x)
  ```

- `대괄호 표기법`으로 프로퍼티 값 접근이 가능하다.
  <br>대괄호 안은 `따옴표`로 묶어줘야 한다.

      ```js
      let user = {
          'buy pencil' : false
      };
      user["buy pencil"] = true // (o)
      ```

- `대괄호 표기법`은 모든 표현식의 평가 결과를 `프로퍼티 키`로 사용가능하다.
  <br>`점 표기법`은 불가능하다.

  ````js
  let user = { name : "hong" };
  let key = "name";
      user[key] = "kim"; //(o)
      user.key = "kim"; //(x)
      ```

  ````

- 존재하지 않는 프로퍼티에 접근해도 에러가 발생하지 않고 `undefined`를 반환한다.

  ```js
  let user = {};
  alert(user.noSuchProperty === undefined); //true
  ```

  - 아래와 같이 `in` 연산자로 프로퍼티 존재 여부도 확인할 수 있다.

  ```js
  let user = {};
  alert('age' in user); // false
  ```

- `property key`가 `정수`라면 `오름차순`으로 자동 정렬이 되고, 그 외는 추가한 순서대로 정렬된다.

- 객체는 논리 평가시 항상 참을 반환한다

  ```JS
  let zero = new Number(0);
  if(zero) alert("yes"); //alert가 실행된다
  ```

  <br>

## 계산된 프로퍼티 (computed property)

객체를 생성할때 객체 리터럴 안의 `프로퍼티 키`가 대괄호로 둘러싸여 있는 경우를 계산된 프로퍼티라고한다.

```js
let key = "name";

let user = {
    [key] : "hong"
};

/* 아래와 같이도 사용 가능*/
let user;
user[key] : "hong";
```

<br>

## 단축 프로퍼티

프로퍼티 이름과 value의 이름(변수 이름)과 동일할때 줄여서 작성이가능하다.

```js
function join(name, age){
    return {
        name : name,
        age : age,
    };
}

->

function join(name, age){
    return {
        name,
        age,
    };
}

```

<br>

## for ... in 반복문

객체의 `모든 키`를 순회하는 반복문

```js
let user = {
  name: 'hong',
  age: 24,
};

for (let key in user) {
  alert(key); //name, age
  alert(user[key]); //hong, 24
}
```

<br>

## 복제

참조에 의한 복사이기 때문에 새로운 객체변수에 값을 그대로 복제를 하고싶다면, for문을 이용해 복제하거나 `Object.assign()`함수 이용

```js
let user = { name: 'hong' };
let admin = {};

/*for문이용한 복제*/
for (let key in user) {
  admin[key] = user[key];
}

/*Object.assgin()이용한 복제*/
Object.assgin(admin, user);

let admin2 = Object.assgin({}, user);
```

동일한 이름(key)의 프로퍼티가 있을때는 값(value)이 덮어씌워진다.

admin2 와 같이 빈 객체에 복제 후에 변수에 삽입하는 것도 가능하다.

<br>

### 객체 안의 객체가 있는 경우 복제

아래와 같이 객체안에 객체가 있는 경우 그냥 user만 복사하게 되면 안에 프로퍼티인 sizes는 참조값을 복사하게 된다.

```js
let user = {
  name: 'hong',
  sizes: {
    height: 172,
    width: 64,
  },
};

let clone = Objcect.assgin({}, user);

alert(user.sizes === clone.sizes); // true
```

이를 해결하려면 `user[key]`값을 for문을 통해 검사하며 객체안의 객체도 복사해주는 방법을 이용하거나 `lodash`라이브러리의 `_.cloneDeep(obj)`을 이용할 수 있다.

이를 `깊은 복사(deep cloning)`이라 한다.

<br>

## 객체안의 함수

객체 안에 key와 value를 갖는 프로퍼티를 말고도 함수가 들어 올수도 있다.

선언 방식

아래 두개와 같이 객체에 함수를 추가 해줄 수 있다.

1. ```js
   let user = { name: 'hong' };
   user.sayHi = function () {
     alert('hello');
   };
   ```

2. ```js
   let user = { name: 'hong' };
   function sayHi() {
     alert('hello');
   }
   ```

아래 두개와 같이 객체내에 함수를 선언 해 줄 수 있다.

1. ```js
   let user = {
     name : "hong"
     sayHi : function{
       alert("hello");
     }
   };
   ```
2. ```js
   let user = {
     name : "hong"
     sayHi(){
       alert("hello");
     }
   };
   ```

## Object.fromEntries()

배열이나 map,set을 객체로 바꾸는 함수

## 객체를 문자열로 전환

네트워크를 통해 객체를 어딘가에 보내거나 로깅 목적으로 객체를 출력해야 한다면, 객체를 문자열로 전환해야 하는데 `toString()`을 이용할 수 있다.

```js
let user = {
  name: 'John',
  age: 30,

  toString() {
    return `{name: "${this.name}", age: ${this.age}}`;
  },
};
alert(user); // {name: "John", age: 30}
```

그런데 위 방법은 객체의 프로퍼티가 추가될때마다 `toString()`을 수정해줘야하니 번거러운 작업이기 때문에 `json 메서드를 이용`

[json 메서드 보러가기](./json.md)
