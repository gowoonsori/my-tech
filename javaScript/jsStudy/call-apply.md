# 데코레이터와 포워딩

## 데코레이터

캐싱기능을 위해 인수로 받은 함수의 행동을 변경시켜주는 함수

자주 사용되는 함수의 재연산 시간을 줄이기 위해 캐싱 기능을 위해 래퍼 함수 만들기

```js
function slow(x) {
  // CPU 집약적인 작업이 여기에 올 수 있습니다.
  alert(`slow(${x})을/를 호출함`);
  return x;
}

function cachingDecorator(func) {
  let cache = new Map();

  return function (x) {
    if (cache.has(x)) {
      // cache에 해당 키가 있으면
      return cache.get(x); // 대응하는 값을 cache에서 읽어옵니다.
    }

    let result = func(x); // 그렇지 않은 경우엔 func를 호출하고,

    cache.set(x, result); // 그 결과를 캐싱(저장)합니다.
    return result;
  };
}

slow = cachingDecorator(slow);
```

- cachingDecorator함수를 생성하여 없는 결과값이면 메모리에 저장하고 이미 실행되었던 함수 인자라면 실행없이 바로 결과를 return해주는 캐시 기능의 함수로 return값은 캐싱기능이 추가되어 `wraaping`된 함수가 반환되므로 동일한 작업을 수행하는 것은 변함이 없다.

  <br>

  캐싱 데코레이터는 객체 메서드에 사용하기에 적합하지 않기 때문에 `func.call`함수 이용 (객체 함수에서 this이용시 decorator함수로 wrapp도중 this가 undefined되기 때문에)

- func.call : this를 명시적으로 고정해 함수를 호출할 수 있게 해주는 내장 메서드

```js
let worker = {
  slow(x) {
    alert(`slow(${x})을/를 호출함`);
    return x * this.someMethod();
  },
};

function cachingDecorator(func) {
  let cache = new Map();
  return function (x) {
    if (cache.has(x)) {
      return cache.get(x);
    }
    let result = func.call(this, x); // 이젠 'this'가 제대로 전달됩니다.
    cache.set(x, result);
    return result;
  };
}

worker.slow = cachingDecorator(worker.slow); // 캐싱 데코레이터 적용
```
