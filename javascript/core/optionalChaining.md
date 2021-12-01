# 옵셔널 체이닝 '?.'

최근에 추가된 문법으로 프로퍼티가 없는 중첩 객체를 에러없이 안전하게 접근 가능하게 해준다.

`?.`은 앞의 평가 대상이 undefined이거나 null이면 평가를 멈추고 undefined를 반환한다.
존재한다면 해당 프로퍼티를 반환

<br>

아래와 같이 없는 프로퍼티에 접근하여 에러가 나게된다.

user.address만 접근하면 없는 프로퍼티이기에 undefined가 출력되겠지만, undefined에 street을 참조하려고하기 때문에 error

```js
let user = {};

alert(user.address.street); // TypeError: Cannot read property 'street' of undefined
```

<br>

해결 방법

- 기존 방법 : `&&`이용

```js
alert(user && user.address && user.address.street); //undefined
```

- 새로운 방법 : 옵셔널 체이닝(?.) 이용

```js
alert(user?.address?.street); //undefined
```

<br>

## 특징

- `?.`앞의 변수는 꼭 선언이 되어있어야한다.

- `?.`은 연산자가 아니라 함수나 대괄호와 함께 동작하는 특별한 문법 구조체

  ```js
  let user1 = {
    firstName: 'Violet',
    admin() {
      alert('관리자 계정입니다.');
    },
  };
  let user2 = {};

  user1.admin?.(); // 관리자 계정입니다.
  user2.admin?.(); //아무일이 일어나지 않는다.

  alert(user1?.['firstName']); //Violet
  alert(user2?.['firstName']); //undefined
  ```
