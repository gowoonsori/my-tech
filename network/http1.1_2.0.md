# Http
## Http 1.1

하나의 연결당 하나의 요청/응답을 처리해(동시 전송 불가) 웹사이트 한개의 페이지의 수많은 파일들을 불러오는데 속도와 성능이 떨어진다. (파이프라이닝과 번들러로 어느정도 커버는 하고 있다.)

`HOL Blocking` : HOL은 Head of Line 의 약자로 `Head` 즉, 앞선 요청때문에 뒤의 요청들이 Block 되는 것 ( 요청과 응답 순서가 동기화 )

한 페이지에 수만은 요청/응답 때문에 `RTT`가 증가한다.

헤더 크기가 크다. (많은 메타 데이터들이 들어있다.)

- 도메인 샤딩 : 하나의 데이터를 여러개의 domain으로 나누어 저장하고 여기서 동시적으로 다운 받는 방법으로 속도향상을 꾀하는 방법

  도메인이 여러개이기 때문에 `질의`도 여러번해야 하고 각 connection을 구성하기 때문에 오히려 성능이 떨어질 수 도 있다.

- 번들러 : 일종의 파일 압축

- 이미지 스프라이트 : 여러개의 이미지를 합쳐서 관리

## Http 2

- Multiplexed Streams : 한 커넥션에 여러개의 데이터를 동시에 주고받을 수 있다.

- Stream Prioritization : 요청에 대한 우선순위를 정할 수 있다.
- Server Push : Html문서에 필요한 파일들(css,js등)을 요청없이 보내줄 수 있다.
- Header Compression : 헤더 정보를 압축하여 보낸다.
- 많은 브라우저들과 현재 꽤 높은 호환성을 갖는다.

<br><br>

## HTTP 3

https://evan-moon.github.io/2019/10/08/what-is-http3/

---

### Reference

https://medium.com/@shlee1353/http1-1-vs-http2-0-%EC%B0%A8%EC%9D%B4%EC%A0%90-%EA%B0%84%EB%8B%A8%ED%9E%88-%EC%82%B4%ED%8E%B4%EB%B3%B4%EA%B8%B0-5727b7499b78
