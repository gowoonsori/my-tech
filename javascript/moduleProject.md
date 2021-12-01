## CommonJs

`exports`, `require`키워드를 사용한 방식

```js
const fun1 = require('example');
```

example 이라는 모듈(라이브러리)를 `require`이라는 키워드를 통해 불러와 변수에 할당하는 방식이다.

```js
const div = 2;

const func1 = function (num2) {
  return num2 / div;
};

exports.func1 = func1;

module.exports = func1;
```

`exports`키워드를 통해 여러개의 객체들을 내보낼 수도 있고 `module.exports`키워드를 통해 한개의 객체만 보낼 수도 있다.

CommonJs는 모든 파일이 디스크에 있는 상황을 전제로 한다. (서버 사이드)
<br>때문에, 한개의 Js파일을 내려받는데 그 파일에 추가되어있는 의존성 파일들(모듈)을 모두 서버사이드에서 다운받아 처리한 후에 응답을 주기 때문에 block된다는 문제가 있다.

이는 동적으로 `script 태그`를 삽입하는 방법으로 극복을 하려고 한다고 한다. (브라우저가 특정 Js를 로딩하는 동안 block이 되기 때문에 이를 막고자 js파일내에서 script태그를 만들고 나중에 특정 태그에 붙이는 방법)

서버의 모듈을 비동기적으로 전달하기 위해서는 `require.define({},[])`의 포맷으로 감싸 전송하면 브라우저는 비동기적으로 로드할 수 있다.

## AMD

`import - from`키워드를 이용하여 모듈을 로드하는 방식으로 CommonJs에 비해 명시적이다.

비동기환경과 서버사이드에서 잘 동작하고 define() 함수를 이용해 모듈을 구성해 전역변수의 문제가 없다.

보통 `트리 쉐이킹`을 위해 프론트에서는 AMD명세를 사용한다.

---

### Reference

https://d2.naver.com/helloworld/12864
