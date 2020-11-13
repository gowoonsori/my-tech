대부분 자동형변환으로 적절한 자료형에 맞게 형변환이 수행된다.

- String(value) : value를 string으로 변환

- Number(value) : 숫자로 반환하나 숫자가 아니여서 변환할 수 없는 경우 NaN 반환.
  <br><br>value 값에 따른 반환 - undefined : Nan - null : 0 - true/false : 1/0 - String : number / Nan

- Boolean(value ) : 0, null, undefined, NaN 은 false . 그 외는 true
