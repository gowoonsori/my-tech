# CSR

Cilent Side Rendering

브라우저가 특정 url에 접속하면 프론트 서버로 부터 `정적 파일`들을 받아 렌더링 후에 그 안에 들어있는 데이터는 백 서버로부터 필요할때마다 요청해서 받아 렌더링 하는 방식

# SSR

Server Side Rendering

브라우저가 특정 url에 접속하면 프론트 서버는 백서버로부터 파일안의 데이터를 요청후 응답받아 모든 데이터를 포함하여 렌더링해서 보여주는 방식

# SPA

Single Page Application

말그대로 한개의 페이지를 갖는 Application으로 페이지 이동을 통해 새로운 페이지를 요청하는 것이 라우팅을 현재 페이지에 동적으로 렌더링하는 방식 ( 바뀐 부분만 변경해주면 되기 때문에 빠르다.)

## 단점

- 바뀐 부분만 바꾸며 렌더링 하기 때문에 현재 페이지의 설명(메타 데이터)의 변경은 힘들고 검색엔진이 해당 페이지에대한 내용을 검새할때는 내용이 비어있기 때문에(Js로 동적으로 구성되기 때문) SEO 최적화가 힘들다.

- JS 파일이 커진다. ( 이동하지 않을 페이지에 대한 스크립트 파일도 모두 불러오기 때문)

  `code splitting`으로 어느정도 해결은 할 수 있다.

# MPA

Multi Page Application

예전부터 사용하던 방식으로 페이지간 이동을 서버로부터 새로운 페이지를 요청해서 받아 전부 다시 그리는 방식

## 단점

- SPA에 비해 느리다.