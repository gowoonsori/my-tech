# API

Application Programming Interface의 약자로 응용프로그램에서 사용할 수 있도록, 운영 체제나 프로그래밍 언어가 제공하는 기능을 제어 할 수 있게 만든 인터페이스

# REST API

REST 아키텍처 스타일을 따르는 API

Representational State Transfer의 약자로 자원(data)를 이름(표현)으로 구분하여 해당 자원의 상태를 주고 받는 모든 것 (웹 시스템의 기본을 유지하면서, 독립적인 진화를 보장하기 위한 방법)

data를 표현하고 이 data의 상태(정보)를 전달하는 것으로 `로이 필딩`이 `http`설계 우수성에 비해 제대로 사용되지 못하는 것같아 장점을 최대한 활요할 수 있는 아키텍처로 발표한 것

HTTP URI(Uniform Resource Identifier)를 통해 자원을 명시하고, HTTP Method(Post/Get/Put/Delete)로 자원의 상태를 적용하여 서버는 Json/Xml과 같은 데이터로 전달하는 방식

## 구성

- 자원(Resource) : URI
- 행위(Verb) : Method
- 표현

## 특징

- Uniform Interface : 정해진 방법으로 작업을 수행하는 아키텍쳐 스타일 이다.
- Stateless : 세션/쿠키와 같은 상태 정보를 별도로 저장 관리 하지 않아 서비스 자유도가 높아진다.

- Casheable : http프로토콜 표준의 last-modified나 E-Tag를 이용해 캐싱구현이 가능하다.

- client-server : 서버는 api를 제공하고 클라이언트는 사용자인증, 컨텍스등 을 직접 관리하는 구조로 역할이 확실히 구분이 되어 서로간 의존성이 줄어든다.

- Self-descriptiveness : 메시지만 보고 무엇을 의미하는지 쉽게 이해 할 수 있는 구조이다.

- 계층형 구조 : 다중 계층으로 구성할 수 있어 보안/로드 밸런싱/암호화 계층을 추가해 구조상 유연성을 둘 수 있고, Proxy/GateWay 같은 네트워크 기반의 중간매체도 사용 가능하다.

## 단점

- 표준이 존재 하지 않아 REST API규칙이 제대로 적용하고 있지 않는 경우가 많다.

  - Self-Describtive Message : 메세지만 보고 해석할 수 있어야 하는데 현재, post를 남발하는 api가 많다.

    - 해결방법

      1. 미디어 타입을 정의하고, IANA에 등록하고 그 미디어 타입을 리소스 리턴할때, Content-Type으로 사용한다.

      1. profile 링크 헤더를 추가 (대부분의 브라우저들이 스펙을 지원을 잘 안하기 때문에 `HAL`의 링크 데이터에 profile링크 추가)

  - HATEOAS (Hypermedia As The Engine Of Application State) : 하이퍼 링크를 통해 상태 이동이 일어나야 한다. (링크가 없으면 상태 전이는 불가능)

    - 해결방법

      1. 데이터에 링크를 제공 : 링크를 HAL을 이용해 정의
