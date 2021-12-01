대부분 자동형변환으로 적절한 자료형에 맞게 형변환이 수행된다.

## 명시적 형변환

아래와 같이 명시적으로 형변환을 수행하는 것

- String(value) : value를 string으로 변환

- Number(value) : 숫자로 반환하나 숫자가 아니여서 변환할 수 없는 경우 NaN 반환.
  <br><br>value 값에 따른 반환 - undefined : Nan - null : 0 - true/false : 1/0 - String : number / Nan

- Boolean(value ) : 0, null, undefined, NaN 은 false . 그 외는 true

<br>

## 자동형변환 응용

**string을 숫자로 변환**

- +String
- 1\*String
- String / 1
  ```js
  alert(typeof +'11'); //number
  alert(typeof 1 * '11'); //number
  alert(typeof '11' / 1); //number
  ```
  이 방법은 문자가 숫자가 아니라면 형변환이 실패하여 `NaN`을 반환한다.

이럴때는 `parseInt()`, `parseFloat()` 이용하여 앞에서 부터 읽을 수 있는 수까지만 반환

```js
alert(+'100px'); //NaN
alert(parseInt('100px')); //100
alert(parseInt('12.3')); // 12, 정수 부분만 반환
alert(parseFloat('12.3.4')); // 12.3, 두 번째 점에서 숫자 읽기를 멈춥니다.

alert(parseInt('a123')); // NaN,
```

위에서 마지막 경우와 같이 첫 문자부터가 숫자가 아니라 읽을 수 있는 숫자가 없을때는 NaN을 반환

진법은 `10`이 기본으로 다른 진법으로 변환하고자 한다면 `parseInt('0xff',16)` 과 같이 두번째 인자 입력해주면된다.
