# 비교 연산자

## 동등 연산자 ==

비교하려는 값의 자료형이 다르면 값들을 숫자로 바꾸어 비교

- 0과 false를 구별하지 못한다.
- null과 undefined는 형변환을 수행하지 않는다.
- null과 undefined는 특별한 규칙이 적용되 true가 반환된다.

## 일치 연산자 ===

형변환 없이 값을 비교한다. (자료형까지 똑같아야 한다.)

## 추가) >=, > , <, <=

비교 연산자는 null 을 0으로, undefined는 NaN으로 변환하여 비교를 수행한다.

undefined는 NaN을 반환하기때문에 항상 false가 나온다.

## Objcet.is(val1,val2) 이용해 정확한 비교

```js
Object.is(NaN,NaN) === true
Object.is(0,-0) === false
Object.is(a,b) 는 a === b와 같다.
```
