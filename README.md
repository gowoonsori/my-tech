# 💻 [TIL] Studying tech / computer science knowledge

> 사소한 질문들에 대한 공부, 개발하면서 공부했던 개념이나 cs기초들을 정리합니다.

<br>
<br>

## 🟦 자료구조

- [자료구조에 따른 공간 복잡도 & 시간 복잡도](/dataStructure/complexity.md)
- [배열과 리스트 ( Array and List )](/dataStructure/array-list.md)
- [스택 과 큐 ( Stack and Queue )](/dataStructure/stack-queue.md)
- [트리 ( Tree )](/dataStructure/tree.md)

  - [AVL Tree](/dataStructure/AvlTree.md)
  - [Red Black Tree](/dataStructure/redBlackTree.md)
  - [Splay Tree](/dataStructure/SplayTree.md)
  - [AA Tree](/dataStructure/aaTree.md)

- [힙 ( Heap )](dataStructure/heap.md)
- [그래프 ( Graph )](/dataStructure/graph.md)

<br>

## 🟦 네트워크

- [ 오류 검출 / 정정 기법 ](/network/errorDetection-correction.md)
- [ 네트워크와 관련 개념 ](/network/network.md)
- [ 응용 계층 ](/network/applicationLayer.md)
  - [Http 헤더](/network/httpHeader.md)
  - [HTTP/1, HTTP/2, HTTP/3](/network/http1.1_2.0.md)
- [ 전송 계층 ](/network/transportLayer.md)
- [ 네트워크 계층 ](/network/networkLayer.md)

  - [ 데이터 평면 ](/network/forwarding.md)
  - [ 제어 평면](/network/routing.md)

    <br>

## 🟦 알고리즘

- [시간 복잡도 & 공간 복잡도](/algorithm/time-space-complexity.md)
- [복잡도 계산](/algorithm/computational-complexity.md)
- [dp (동적 계획법)](/algorithm/dynamic-programming.md)
- [정렬 알고리즘](/algorithm/sorting-algorithm.md)
- [최장 증가 수열 (LIS) ](/algorithm/longest-increasing-subsequence.md)
- [Disjoint Set과 union-find](/algorithm/DisjointSet-unionFind.md)
- MST
  - [Kruskal's algorithm](/algorithm/kruskal-algorithm.md)
  - [Prim's algorithm](/algorithm/prim-algorithm.md)
- 최단 경로 ( Shortest Path )
  - [Dijkstra's algorithm](/algorithm/dijkstra.md)
  - [Bellman-Pord algorithm](/algorithm/bellman-ford.md)
  - [Floyd-Warshall algorithm](/algorithm/floyd-warshall.md)
- [위상정렬 (Topological Sort)](/algorithm/topological-sort.md)

- [피셔-예이츨 셔플 알고리즘]

<br>

## 🟦 개발 상식

- [라이브러리와 프레임워크](/develop-common-sense/library-framework.md)
- [동기-비동기/block-nonBlock](develop-common-sense/sync-async-block-nonblock.md)
- [API와 REST API](./develop-common-sense/rest-api.md)
- [디자인 패턴(GOF 패턴)](./develop-common-sense/design-pattern.md)
- [Transaction Script과 Domain Model](./develop-common-sense/transactionScript_domainModel.md)
- [테스트 종류](./develop-common-sense/kindsOfTesting.md)
- [Git](./develop-common-sense/git.md)
- [Gitmoji](./develop-common-sense/gitmoji.md)
- [RegExp (regex = 정규표현식)](./develop-common-sense/regex.md)
- [Asciidoctor](/develop-common-sense/asciidoctor.md)

<br>

## 🟦 Kubernetes

- [Kubernetes란](./kubernetes/kubernetes.md)

<br>

## 🟦 SQL

- [SQL이란](/SQL/sql.md)
- Querying data (데이터 get)
  - [SELECT](/SQL/select.md)
- Sorting data (정렬)
  - [ORDER BY (FIELD)](/SQL/orderby.md)
- Filtering data (필터링)
  - [WHERE](/SQL/where.md)
  - [SELECT DISTINCT](/SQL/selectDistinct.md)
- Join table (테이블 연결)
  - [Alias](/SQL/alias.md)
  - [Join](/SQL/join.md)
- Grouping (데이터 그룹화)
  - [Group By](/SQL/groupBy.md)
  - [HAVING](/SQL/having.md)
  - [ROLLUP](/SQL/rollup.md)
- [Concat (문자열 연결)](/SQL/concat.md)
- [IFNULL](/SQL/ifnull.md)
- [공통 테이블 표현식(CTE) / 재귀 CTE](/SQL/cte.md)

<br>

## 🟦 Web

- [구조](/web/structure.md)
- [Web Server와 WAS](/web/WAS.md)
- [브라우저 동작 과정](/web/browser.md)
- [사용자 인증(쿠키/세션과 JWT)](/web/authentication.md)
  - [OAuth](/web/OAuth.md)
- [Http 헤더](/network/httpHeader.md)
- [Https](/web/https.md)
- [CSR/SSR, SPA/MPA](/web/csr_ssr.md)

  <br>

## 🟦 Java

- [JVM과 자바 실행 방법](/java/jvm.md)
- [데이터타입과 변수,배열](/java/dataType.md)
- [연산자](/java/operator.md)
- [Thread](/java/thread.md)
- [Enum](/java/enum.md)

<br>

## 🟦 Spring Framework

- [스프링이란?](/spring/spring.md)
  - [Controller](/spring/Controller.md)
  - [Entity와 DTO](/spring/entity.md)
  - [Repository와 DAO](/spring/repository_dao.md)
  - [Spring Bean](/spring/spring-bean.md)
  - [Spring MVC](/spring/springMVC.md)
- 스프링 프로젝트
  - [스프링 Boot](/spring/springboot.md)
  - [스프링 HATEOAS](/spring/hateoas.md)
    - [Representation Model](/spring/representationModel.md)
  - 스프링 Data
    - [Spring Data JPA](/spring/jpa.md)
      - [EntityManagerFactory와 EntityManager](/spring/jpa_operation.md)
      - [MySQL연결하기](/spring/mySQL.md)
      - [Pageable](/spring/pageable.md)
  - [스프링 REST Docs](/spring/restDocs.md)
  - [스프링 Security](/spring/security.md)
    - [OAuth2](/spring/OAuth.md)
- 라이브러리
  - [Lombok](/spring/lombok.md)
  - [Model Mapper](/spring/modelMapper.md)
  - JackSon
    - [Object Mapper](/spring/objectMapper.md)
  - [Custom Serialize](/spring/customSerialize.md)
- 프로젝트 라이플 사이클 관리 도구 (빌드 배포 Tool)
  - [Maven](/spring/maven.md)
- Test

  - [JUnit5](./spring/Junit5.md)
    - [JunitParams](./spring/JunitParams.md)
  - [AssertJ](./spring/AssertJ.md)
  - [Mock](/spring/mock.md)

- [@ConfigurationProperties](/spring/configurationProperties.md)

<br>

## 🟦 JavaScript

- [Webapck과 Babel](/javaScript/webpack-babel.md)
  - [CommonJs, AMD](/javaScript/moduleProject.md)
- [JS문법과 코어개념 공부](/javaScript/modern-js-tutorial.md)

<br>

## 🟦 React

- [특징](/react/react-feature.md)
- [NextJs](/react/nextjs.md)

<br>

## 🟦 VSCode / IntelliJ 단축키

- [통합 단축키 기록](./keymap.md)
