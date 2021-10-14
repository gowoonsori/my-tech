# 💻 [TIL] Studying tech / computer science knowledge

> 사소한 질문들에 대한 공부, 개발하면서 공부했던 개념이나 cs기초들을 정리합니다.

<br>
<br>

##  자료구조

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

##  네트워크

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

##  알고리즘

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

##  개발 상식

- [빅엔디안과 리틀 엔디안](/common/endian.md)
- [라이브러리와 프레임워크](/common/library-framework.md)

- [동기-비동기/block-nonBlock](common/sync-async-block-nonblock.md)
- [API와 REST API](/common/rest-api.md)
- [디자인 패턴(GOF 패턴)](/common/design-pattern.md)
- [Transaction Script과 Domain Model](/common/transactionScript_domainModel.md)
- [테스트 종류](/common/kindsOfTesting.md)
- [Git](/common/git.md)
- [Gitmoji](/common/gitmoji.md)
- [RegExp (regex = 정규표현식)](/common/regex.md)
- [Asciidoctor](/common/asciidoctor.md)
- [컴파일러](/devlop-common-sense/compiler.md)
- [ELK](/common/elk.md)

<br>

##  Linux

- [Linux와 내부구조](/linux/linux.md)

- [Linux 디렉토리 구조와 기능](/linux/directory.md)
- [Linux 개념들과 명령어](/linux/command.md)

##  DevOps

- [MSA](/devOps/msa.md)
- [Kubernetes란](/devOps/kubernetes/kubernetes.md)

<br>

##  DataBase

- [Index](/sql/index.md)

- [SQL이란](/sql/sql.md)
  - Querying data (데이터 get)
    - [SELECT](/sql/select.md)
  - Sorting data (정렬)
    - [ORDER BY (FIELD)](/sql/orderby.md)
  - Filtering data (필터링)
    - [WHERE](/sql/where.md)
    - [SELECT DISTINCT](/sql/selectDistinct.md)
  - Join table (테이블 연결)
    - [Alias](/sql/alias.md)
    - [Join](/sql/join.md)
  - Grouping (데이터 그룹화)
    - [Group By](/sql/groupBy.md)
    - [HAVING](/sql/having.md)
    - [ROLLUP](/sql/rollup.md)
  - [Concat (문자열 연결)](/sql/concat.md)
  - [IFNULL](/sql/ifnull.md)
  - [공통 테이블 표현식(CTE) / 재귀 CTE](/sql/cte.md)

<br>

##  Web

- [구조](/web/structure.md)

- [Web Server와 WAS](/web/WAS.md)
- [브라우저 동작 과정](/web/browser.md)
- [사용자 인증(쿠키/세션과 JWT)](/web/authentication.md)
  - [OAuth](/web/OAuth.md)
- [Http 헤더](/network/httpHeader.md)
- [Https](/web/https.md)
- [CSR/SSR, SPA/MPA](/web/csr_ssr.md)

  <br>

##  Java

- [JVM과 자바 실행 방법](/java/jvm.md)

- [데이터타입과 변수,배열](/java/dataType.md)
- [연산자](/java/operator.md)
- [Thread](/java/thread.md)
- [Enum](/java/enum.md)

<br>

##  Spring Framework

- [스프링이란?](/spring/spring.md)

  - [Controller](/spring/Controller.md)
  - [Entity와 DTO](/spring/entity.md)
  - [Repository와 DAO](/spring/repository_dao.md)
  - [Spring Bean](/spring/spring-bean.md)
  - [Spring MVC](/spring/springMVC.md)

- 스프링 프로젝트

  - [스프링 Boot](/spring/springboot.md)
  - [스프링 REST Docs](/spring/restDocs.md)
  - [스프링 HATEOAS](/spring/hateoas.md)
    - [Representation Model](/spring/representationModel.md)
  - 스프링 Data
    - [Spring Data JPA](/spring/jpa.md)
      - [EntityManagerFactory와 EntityManager](/spring/jpa_operation.md)
      - [연관관계 맵핑](/spring/jpa_relationship.md)
        - [상속관계 맵핑](/spring/jpa_super_sub_type_relationship.md)
        - [복합키와 식별관계 맵핑](/spring/jpa_composite_key.md)
        - [프록시와 연관관계 맵핑](/spring/jpa_proxy_relationShip.md)
      - [데이터 타입](/spring/jpa_valueType.md)
      - [JPQL과 QueryDSL](/spring/jpa_jpql_querydsl.md)
      - [트랜잭션 범위에 따른 영속성 컨텍스트](/spring/jpa_transaction.md)
      - [추가 어노테이션](/spring/jpa_annotation.md)
      - [예외](/spring/jpa_exception.md)
      - [엔티티 비교](/spring/jpa_compare.md)
      - [성능 최적화](/spring/jpa_optimization.md)
      - [MySQL연결하기](/spring/mySQL.md)
      - [Pageable](/spring/pageable.md)
  - [스프링 Security](/spring/security.md)

    - [DelegatingProxyChain / FilterChainProxy](/spring/security_chain.md)
    - [SecurityContext](/spring/security_context.md)
    - [Authentication](/spring/security_authentication.md)
    - [인증필터](/spring/security_authenticationFilter.md)
    - [인가](/spring/security_authorizationFilter.md)
    - [OAuth2](/spring/security_oauth.md)

  - [스프링 Cloud](/spring/cloud.md)

    - [Eureka](/spring/eureka.md)

  - Elasticsearch Client API
    - [index](/spring/es_index.md)

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

##  PHP

- Laravel

  - [기본 구조](/php/laravel/architecture.md)
  - [route](/php/laravel/route.md)
  - [view](/php/laravel/view.md)
  - [blade](/php/laravel/blade.md)
  - [model](/php/laravel/model.md)
  - [db](/php/laravel/db.md)
  - [eloquent](/php/laravel/eloquent.md)
  - [seeding](/php/laravel/seeding.md)
  - [paging과 로딩](/php/laravel/pagingLoading.md)
  - [middleware](/php/laravel/middleware.md)
  - [controller](/php/laravel/controller.md)
  - [validate](/php/laravel/validate.md)
  - [event](/php/laravel/event.md)
  - [Exception Handling](/php/laravel/exceptionHandling.md)
  - [debug](/php/laravel/debug.md)
  - [Email](/php/laravel/email.md)

- [composer](/php/laravel/composer.md)
- [::](/php/scopeResolutionOperator.md)
- [Facade](/php/Facade.md)

<br>

##  CDC

- [kafka](/cdc/kafka.md)
  - [connect와 debezium](/cdc/debezium.md)

<br>

##  JavaScript

- [Webapck과 Babel](/javaScript/webpack-babel.md)
  - [CommonJs, AMD](/javaScript/moduleProject.md)
- [JS문법과 코어개념 공부](/javaScript/modern-js-tutorial.md)

<br>

##  React

- [특징](/react/react-feature.md)
- [NextJs](/react/nextjs.md)