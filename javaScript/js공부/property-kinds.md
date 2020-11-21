# 프로퍼티 종류

- 데이터 프로퍼티 : 지금까지 사용, 설명한 모든 프로퍼티

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
};

alert(user.fullName); // John Smith
```
