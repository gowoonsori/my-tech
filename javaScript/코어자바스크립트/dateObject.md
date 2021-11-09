# Date 내장 객체

현재 날짜를 출력하거나 시간을 측정 하는 등으로 활용

## 사용법

- Date객체 생성

  - new Date() : 현재 날자와 시간이 저장된 Date객체 생성
  - new Date(ms) : UTC 기준 1970/01/01 00:00:00 에서 ms 밀리초 후의 시점이 저장된 Date객체 생성

    이때 `ms`를 `타임스탬프`라고 한다.

    1970년 이전의 날짜의 타임스탬프는 `음수`

  - new Date(datestring) : 문자열을 자동으로 파싱하여 맞는 날짜의 객체 생성

  - new Date(YY,MM,DD,h,m,s,ms) : 값을 직접 지정해서 객체 생성

    - YY는 반드시 `4자리` 숫자
    - MM은 반드시 `0-11` 숫자
    - DD는 값이 없는 경우에 1로 처리, 음수~0이면 뒤로 센다.
    - h,m,s,ms는 값이 없는 경우에 0으로 처리

  ```js
  let now = new Date();
  let Jan01_1970 = new Date(0);
  let Dec31_1969 = new Date(-24 * 3600 * 1000);
  let Jan26_2017 = new Date('2017-01-26');
  let Jan01_2011 = new Date(2011, 0, 1);
  ```

- Date객체의 날짜 시간 반환

  - getFullYear() : 4자리 년도
  - getMonth() : 0 - 11
  - getDate() : 1 - 31 (일수)
  - getDay() : 0 - 6 (요일)
  - getHours(),getMinutes(),getSeconds(),getMilliseconds() : 시,분,초,밀리초
  - getTime() : 타임스탬프 값
  - getTimezoneOffset() : 현지 시간과 표준 시간 차이(분)

- Date객체의 날짜 시간 설정
  - setFullYear(year, [month], [date])
  - setMonth(month, [date])
  - setDate(date)
  - setHours(hour, [min], [sec], [ms])
  - setMinutes(min, [sec], [ms])
  - setSeconds(sec, [ms])
  - setMilliseconds(ms)
  - setTime(milliseconds)

<br>

## 자동 고침(auto correction)

Date 객체는 범위를 벗어나는 값을 설정하면 자동 고침 기능으로 날짜가 알맞게 변경이 된다.

```js
let date = new Date(2016, 1, 28);
date.setDate(date.getDate() + 2); //윤년도 자동으로 계산

alert(date); // 2016년 3월 1일
```

<br>

## 문자열에서 날짜 읽기

`Date.parse(str)`을 이용하면 문자열에서 날짜를 읽어올 수 있으나 문자열의 형식이 존재한다.

`YYYY-M-DDTHH:mm:ss.sssZ`

- `T`는 구분 기호
- `Z`는 옵션으로 `+-hh:mm`형식의 시간대이다.

위의 조건을 만족시 `타임스탬프`가 반환되며 조건에 맞지 않는다면 `NaN`반환
