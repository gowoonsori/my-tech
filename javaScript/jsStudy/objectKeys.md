# Object.keys, values, entries

`Map`, `Array`, `Set`에 keys, values, entries함수를 사용할 수 있었는데, `일반 객체`에도 사용이 가능하지만 사용법이 조금 다르고 반환 형식이 다르다.

사용법은 `obj.keys()`가 아닌 `Objcect.keys(obj)`이고 반환 형식은 `iterable 객체`가 아닌 `배열`이다.

- Object.keys(obj) – 키가 담긴 배열을 반환
- Object.values(obj) – 값이 담긴 배열을 반환
- Object.entries(obj) – [key, value] 쌍이 담긴 배열을 반환

<br>

## 응용 : 객체 변환

일반 객체에는 배열 메서드를 사용할 수 없는데 `Object.entries`와 `Object.fromEntries`를 이용하면 객체도 배열전용 메서드를 사용할 수 있다.

```js
let prices = {
  banana: 1,
  orange: 2,
  meat: 4,
};

let doublePrices = Object.fromEntries(Object.entries(prices).map(([key, value]) => [key, value * 2]));

alert(doublePrices.meat); // 8
```
