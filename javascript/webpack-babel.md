# webpack

웹팩은 오픈소스로 js 모듈 bundler이다.
<br>(bundler란 어떠한 단위로 여러개의 파일들을 하나로 만들어 요청의 응답을 하기위한 환경을 관리하는 것.

한 페이지에 여러개로 나누어진 수많은 데이터 파일들(css,js등)을 하나하나 요청후 응답하기에는 시간이 오래걸리기 때문에 이런 모듈들을 하나로 합쳐주는 역할을 하는 번들러

> 번들러란? 의존성이 있는 파일(모듈)간 하나로 만들어 주는 도구
> <br>코드의 의존성(dependecy)문제를 해결하기 위함
>
> Js에 모듈이 도입되면서 수많은 모듈들을 성능적으로 문제를 해결하고 관리하기 위해 등장

빌드 도구 [Webpack/Grunt/Gulp 등이 있다.])\_

<br>

### webpack의 탄생 배경

Js를 모듈화 하기 위해 탄생했으며, 그 시작으로는 아래와 같은 명세를 뿌리로 시작한다.

하나의 프로젝트 내에 존재하는 여러개의 파일들을 서로 불러다 쓰다보면, 발생하는 변수 충돌의 위험성을 해결 하기 위해 `IIFE(즉시 함수 호출)`의 방식으로 모듈화를 해주는 방법으로 대표적인 명세가 `CommonJs`와 `AMD`가 있다.

`CommonJs`의 탄생배경은 JS를 브라우저 밖으로 꺼내기 위해 모듈화를 시키면서 생겨났으며, 이를 기반으로한 다양한 프로젝트가 있다.

<br>단점으로 필요한 모듈을 모두 내려받을때까지 아무것도 할 수 없게 되는 것.
<br>브라우저에서 동작할때는 비동기 모듈 로드 문제로 파일 단위의 스코프가 존재 하지 않고 전역변수 문제가 발생하여 require.define()함수를 이용해 전역변수를 통제

`AMD`는 비동기 상황에서도 JS모듈을 사용하기 위해 탄생한 명세.

<br>

`CommonJs`와 `AMD` 는 모듈 로드 방식의 차이. 파일이 모두 로컬 디스크에 있을때는 `CommonJs`가 네트워크를 통해 내려받아야하는 경우 `AMD`가 더 유연한 방법 제공

<br>

[CommonJs와 AMD](/javascript/moduleProject.md)

### webpack 핵심 4가지 개념

- 엔트리 : 모든 파일을 모듈화해서 묶는 웹팩에서 그 `시작점`
  서로 연결되어있는 모듈간의 의존성들의 시작 모듈

  ```js
  {
    entry: {
      1: '파일경로,
      2: '파일경로,
    }
  } //1.js / 2.js 두개 생성

  {
    entry: {
    1: ['a.js','b.js']
    }
  } // a.js와 b.js묶어 1.js 생성
  ```

- 아웃풋 : 엔트리에 설정한 Js파일을 시작으로 모든 모듈을 하나로 묶어 처리한 결과물로 여기에 명시되어 있는 정보를 통해 빌드 파일 생성

  - path : 결과 파일 저장될 경로
  - publicPath : 파일들이 위치할 서버상의 경로
  - filename : 파일이름 (`[name]`으로 파일이름을 사용하면 entry의 이름이 적용된다.)

- 로더 : webpack은 js, 이미지, css, file등 모두 모듈로 보고 관리한다고 했기 때문에, js밖에 이해를 못하는 webpack을 위해 이해할수 있게 변경해주는 역할을 하는 것.

  babel-loader, css-loader, style-loader, file-loader, url-loader, custom-loader등 다양하게 존재하고 정의할 수 있다.

  `JSX`나 `TS`와 같은 문법을 브라우저가 이해할 수 있게 js로 바꿔주는 기능

  - target : 지원하길 원하는 환경
  - modules : `false`로 하면 최신모듈 시스템이 그대로 유지되 `트리 쉐이킹`이 된다.(사용하지 않은 모듈들을 정리해주는 기능)
  - useBuiltIns : entry의 파일들을 target에 맞게 바꾸어주는 역할
    - entry
    - usage
    - false

- 플러그인 : 번들된 결과물을 처리하며, 번들된 js를 난독화 하거나 특정 텍스트를 추출하는 용도.

## 추가 개념

- mode : `development` / `production`

- resolve : 웹팩이 알아서 경로나 확장자를 처리할 수 있게 도와주는 옵션

  - modules : 모듈들의 루트 디렉토리를 설정하면 이를 통해 인식

  - extensions : 지정한 확장자들을 알아서 처리해 준다.

<br><br>

# Polyfill

웹 개발에 있어 어떤 기능을 지원하지 않는 웹브라우저 상에서 그 기능을 구현하기 위한 코드로 `Js`는 계속해서 발전하는 언어이기 때문에 `웹 브라우저`를 만드는 곳에서의 `JS 엔진`또한 지속적인 업데이트가 없다면 새로운 문법,기능을 지원하지 않기 때문에 호환성을 위한 코드이다.

## babel 이란

[babel github](https://github.com/babel/babel) 에 보면 아래와 같이 소개가 되어있다.

> Babel은 최신 버전의 JavaScript로 코드를 작성하는 데 도움이되는 도구입니다.
> <br>지원되는 환경이 특정 기능을 기본적으로 지원하지 않는 경우 Babel은 해당 기능을 지원되는 버전으로 컴파일하도록 도와줍니다.

babel은 오픈 소스로써, js 컴파일러 인것이다. (컴파일은 소스코드를 기계가 이해할 수 있는 코드로 바꾸는 과정인데, JS엔진또한 기계이고 이런 엔진이 이해할 수 있게 바꿔주는 과정이기 때문에 컴파일러라고 볼 수 있다.)

여기서 js는 인터프리터 언어인데 왜 컴파일러가 필요하냐고 할 수 있는데, babel은 정확히 [transfiler _(소스 대 소스 컴파일러)_](https://ko.wikipedia.org/wiki/%EC%86%8C%EC%8A%A4_%EB%8C%80_%EC%86%8C%EC%8A%A4_%EC%BB%B4%ED%8C%8C%EC%9D%BC%EB%9F%AC)로 일종의 현재 js코드나 ts코드를 새로운 js코드로 만들어내는 것.

여기서 ts를 js로 변환 하는 것은 이해가 되는데 js에서 js로 변환하는 이유가 무엇이냐고 묻는다면, 그 이유는 js문법이 변화하여 현재 js문법이 `legacy`가 되거나, 현재 문법이 `IE`와 같은 브라우저에서는 지원을 하지 않거나 새로운 문법이라면, 해당 브라우저에서도 돌아갈 수 있게 자동으로 맞는 js문법으로 변환해주는 기능을 수행하기 때문이다.

<br>

예를 들어 `ES2020`의 문법인 `??*(nullish 병합)*`기호를 사용한다고 한다고 하자.

[??기호 설명 보기](https://ko.javascript.info/nullish-coalescing-operator)

```js
function greet(input) {
  return input ?? 'Hello world';
}
```

위의 최신 문법을 현재 브라우저가 인식할 수 있게 아래와 같이 바꿔주는 역할을 하는 것이 babel.

```js
function greet( input ){
  return  input ! = null ? input : "Hello world" ;
}
```

### 주요 역할

- transpiler : 위에서 설명한 것 처럼 코드를 재작성해주는 역할로 웹팩과 같은 빌드 시스템은 코드가 수정될때마다 자동으로 트랜스파일러를 동작시켜준다.

- polyfill : 새롭게 표준에 추가된 함수와 같이 변경된 표준을 준수할 수 있게 기존 함수의 동작 방식을 수정하거나, 새롭게 구현해주는 역할.
  <br>_(이때 새롭게 구현한 함수의 스크립트를 폴리필이라 부른다. => 구현이 누락된 새로운 기능을 매꿔주는 역할)_

  `core js`, `polyfill.io`등이 있다.

<br><br>

---

## Reference

webpack

- https://jeonghwan-kim.github.io/js/2017/05/15/webpack.html
- https://d2.naver.com/helloworld/12864
- https://ui.toast.com/fe-guide/ko_BUNDLER

babel

- https://github.com/babel/babel
- https://en.wikipedia.org/wiki/Babel_(transcompiler)
- https://ko.javascript.info/nullish-coalescing-operator
- https://ko.wikipedia.org/wiki/%EC%86%8C%EC%8A%A4_%EB%8C%80_%EC%86%8C%EC%8A%A4_%EC%BB%B4%ED%8C%8C%EC%9D%BC%EB%9F%AC
