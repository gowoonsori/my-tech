# 심볼형

심볼은 유일한 식별자를 만들고 싶을때 사용

```js
let id = Symbol();
let id1 = Symbol('name'); //심볼 이름이라 불리는 설명을 붙일 수도 있다. 여기서 name이 설명 부분
```

심볼은 유일성이 보장되는 자료형이기 때문에, 설명이 동일한 심볼을 여러개만들더라도 각 심볼값은 다르다.

또한, 심볼은 문자형으로 자동 형변환이 되지 않는다.
<br>굳이 출력해야겠다면 `.toString()`함수 이용하거나 `.description`을 이용하면 설명만 보여줄 수 있다.

```js
let id1 = Symbol('id1');
let id2 = Symbol('id2');

alert(id == id2); //false
alert(id1); //error
alert(id1.toString()); //Symbol(id)
```
