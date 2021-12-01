JS에는 8가지의 자료형이 존재한다.

## 원시 자료형

- 문자 (string)

  - `템플릿 리터럴` : `${...}` 을`백틱`으로 감싸 문자열 중간에 표현식을 표시하는 방식

    ```js
    let num = 111;
    alert(`num is ${num}`); //num is 111
    ```

  - length : 문자열 길이

    - str.length()가 아닌 str.length이다.

      > 함수가 아니라 숫자가 저장되는 프로퍼티이기 때문

  - `for ... of` 문 이용하여 문자에 접근가능
    ```js
    for (let char of 'hello') {
      alert(char); // h,e,l,l,o
    }
    ```
  - 문자열은 수정이 불가능하다.
    ```js
    let str = 'hi';
    str[0] = 'B'; //error
    ```
  - `str.toLowerCase()`,`str.toUpperCase()` : 문자열 대소문자 변경

  - `str.indexOf(substr,pos)` : 부분 문자열 위치 찾기

    str에서 pos번째 substr의 시작 위치를 반환 없으면 `-1`반환

    ```js
    let str = 'Widget with id';
    alert(str.indexOf('id', 2)); // 12
    ```

  - `str.includes(substr,pos)` : 부분 문자열 포함 여부 확인

    str에서 pos번째 substr이 있으면 true, 없으면 false

  - `str.slice(start,end)` : 부분 문자열 추출

    str에서 start부터 end까지 추출

    end는 생략 가능하며 생략시 끝까지

    start와 end는 음수도 허용하며 end는 start보다 커야한다.

  - `str.substring(start, end)` : 부분 문자열 추출

    str.slice와 비슷하나 start가 end보다 커도 괜찮으며 음수를 허용하지 않는다.

  - `str.substr(start,length)` : 부분 문자열 추출

    start부터 length만큼 문자열을 추출하고 start는 음수를 허용하나 substr은 구식 스크립트에 대응하기 위해 남겨놓은 메서드이다.

  - `str.codePointAt(pos)` : pos에 위치한 글자의 코드를 반환

    ```js
    alsert('z'.codePointAt(0)); //122
    ```

  - `String.fromCodePoint(code)` : 숫자 형식의 code에 대응 되는 글자 반환
    ```js
    alert(String.fromCodePoint(122)); // z
    ```

- 숫자 (number)

  - e를 이용해 0의 개수 표시 가능
    ```js
    let billion = 1e9; //10억
    alert(7.3e9); //73억
    let ms = 1e-6;
    0.000001;
    ```
  - 16진수는 `0x`로 표현
  - 2진수는 `Ob`
  - 8진수는 `0o`
  - 숫자를 문자로 바꿀때 `num.toString(base)`이용

    base는 2~36으로 바꿀 진법

    변수를 이용하는 것이 아닌 숫자 그대로 이용할때는 `.`을 한개 더 이용하거나 `괄호()`로 묶어주면 이용가능

    ```js
    let num = 255;
    alert(num.toString(16)); //ff
    (255).toString(16); //ff
    (255).toString(16); //ff
    ```

  - `Math.floor(num)` : 소수점 첫째 자리에서 버림
  - `Math.ceil(num)` : 소수점 첫째자리에서 올림
  - `Math.round(num)` : 소수점 첫째자리에서 반올림
  - `Math.trunc(num)` : 소수 무시
  - `num.toFixed(x)` : 소수 x자리까지 반올림 후 `문자열` 반환

  - 숫자가 너무 크면 `Infinity`처리

  - js에서는 숫자의 부호를 단일비트로 저장하기 때문에 `0`과 `-0`두종류의 0이 존재한다. _(대부분의 연산은 동일 취급)_

  - `NaN`은 자기 자신을 포함하여 어떤 값과도 같지 않다.
    ```js
    alert(NaN === NaN); //false
    ```
    - `isNaN(value)` : value를 숫자로 변환후 NaN 인지 판별 _(value가 false면 숫자)_
    - `inFinte(value)` : value를 숫자로 변환후 NaN/Infinity/-Infinity인지 판별 _(value가 true면 일반 숫자)_
  - `Math.random()` : 0과 1사이 난수 반환
  - `Math.max(a,b,...)` : 최대값 반환
  - `Math.min(a,b,...)` : 최솟값 반환
  - `Math.pow(n,pow)` : n의 pow 제곱 반환

- bigint
- boolean
- null
- undefined
- symbol

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

## 객체형

함수도 객체의 일종이다.

함수를 프로퍼티로 저장이 가능

js는 날짜, 오류, 시간, HTML 요소 등을 다룰 수 있게 내장 객체또한 제공

Array도 객체형에 속한다.

<br>

### 원시 래퍼 객체

원시값이 메서드나 프로퍼티에 접근할 수 있게 추가 기능을 제공해주는 특수 개체

`String`,`Number`,`Boolean`,`Symbol` 과 같다.

아래와 같이 원시값인 string형의 변수에 메서드를 접근할 수 있게 도와준다.

```js
let str = 'hello';
alert(str.toUpperCase()); //HELLO

/*원시값으로 toUpperCase에 접근하는 순간 래퍼 객체가 자체적으로 만들어지고 이를 이용해 메서르를 접근하여 문자열을 반환후 래퍼 객체는 자동 소멸된다.*/
```
