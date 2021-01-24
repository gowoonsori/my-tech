# Next.js

가장 큰 기능으로 SSR ( Server Side Rendering )을 React에서도 손쉽게 할 수 있게 제공해주는 프레임워크이다.

`핫 리로딩`기능을 제공하여 코드의 변경사항을 감지하여 서버 재시작없이 페이지를 다시 렌더링 해주기 때문에 빠른 개발이 가능하다.

## 파일 구조

- pages : 기본 page들이 들어있는 폴더
  - index.js : Next를 실행시 가장 처음 시작되는 경로 (없으면 error)
  - \_app.js : 모든 페이지의 공통 layout을 정의할 수있는 파일
  - \_document.js : React의 `index.html`과 같은 기능을 수행하는 파일
  - \_error.js : React의 `error.html`과 같은 기능
- static : 이미지나 특정 파일등 정적 파일을 저장
- next.config.js : 환경 설정 파일

## \_app.js

- 공통 layout 정의
- 라우팅시에 상태 유지
- componentDidCatch이용하여 에러 잡기

위와 같은 기능을 수행하기 위한 루트 컴포넌트이다.

## \_document.js

보통 React의 index.html 파일을 보면 `<div id="root">`부분이 있고 이가 React 컴포넌트가 시작 되는 최초 요소로써 작용을 하는데, \_document.js에서는 `<Main />`, `<NextScript />`를 통해 알아서 마운트를 해준다.
