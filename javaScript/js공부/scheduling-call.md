# 호출 스케줄링 ( scheduling a call )

일정 시간이 지난 후에 원하는 함수를 예약 실행 할 수 있게 하는 것

구현 하는 방법은 아래 두가지가 있으며, `명세서`에 명시 되지 않았지만 대부분의 js환경에서 유사한 메서드와 스케줄러를 지원한다.

<br>

## setTimeout

일정 시간이 지난 후에 함수를 실행

```js
//기본 문법
let timer = setTimeout(func, [ms], [arg...]);
```

func 자리에 `문자열`이 와도 js가 알아서 함수를 만들어 정상적으로 동작하나 추천하지 않는 방법으로 익명 화살표 함수를 이용

setTimeout함수 반환값으로 `타이머 식별자(timer identifier)`이 반환

명세가 따로 없기 때문에 브라우저 환경에서는 식별자가 숫자이며, Node.js에서는 타이머 객체이다.

<br>

## clearTimeout

스케줄링을 취소 하고 싶을때 타이머 식별자 값으로 취소

```js
clearTimeout(timer);
```

<br>

## setInterval

일정 시간 간격을 두고 함수를 실행

```js
//기본 문법
let timer = setInterval(func, ms, arg...);
```

setTimeout과 동시에 작업도 가능하다.

```js
// 2초 간격으로 메시지를 보여줌
let timerId = setInterval(() => alert('째깍'), 2000);

// 5초 후에 정지
setTimeout(() => {
  clearInterval(timerId);
  alert('정지');
}, 5000);
```

## clearInterval

setInterval 취소하고 싶을때 사용하며 clearTimeout과 문법이 똑같다.

<br>

## 중첩 setTimeout과 setInterval의 차이

```js
let i = 1;
setInterval(function () {
  func(i++);
}, 1000);
```

```js
let i = 1;
setTimeout(function run() {
  func(i++);
  setTimeout(run, 1000);
}, 1000);
```

위 두 코드는 1초마다 재실행 되는 함수이지만 실제 동작을 해보면 시간의 차이가 존재한다.

실제로 setInterval은 함수를 실행하는데 `소모되는 시간`도 지연간격에 포함시키기 때문에 함수 실행과 실행 사이의 시간이 1초가 되지 않고 setTimeout은 1초마다 재실행된다.

이처럼 중첩 setTimeout은 `지연 간격`을 보장하지만 setInterval은 지연 간격을 보장하지 않는 차이를 보여준다.

setTimeout은 이전 함수의 실행이 종료된 이후에 다음 함수 호출에 대한 계획이 세워지기 때문에 지연 간격이 보장된다.

<br>

## 대기시간 0인 setTimeout

ms를 표시를 안하거나 대기 시간을 0으로 세팅하게 되면 가능한 한 빨리 실행 하라는 뜻의 함수

실행중인 스크립트의 처리를 종류이후에 스케줄링 함수를 실행하는 것(계획표에 기록해주는 느낌)
