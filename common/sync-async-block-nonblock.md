# 동기와 비동기

작업 순서를 기준으로 구분

<br>

## 동기

대부분의 프로그램 구조이다

어떠한 함수가 실행된다고 할때, `절차적으로(순차적으로)` 위에서부터 아래로 코드를 모두 수행한 후 결과를 return하는 방식.

작업의 순서가 보장되는 것.

<br>

## 비동기

어떠한 함수가 실행된다고 할때, 함수내 로직을 처리하기 전 임시데이터(비어있는 데이터)를 return 후 로직 처리 완료 후에 결과를 return하는 방식.

작업의 순서가 보장되지 않는 것.

<br><br>

# Blocking 과 Non-Blocking

통지(?)를 기준으로 구분

<br>

## Blocking

코드를 수행하는 데 어떠한 함수의 결과 처리까지 다른 작업 수행을 하지 않고 기다린 후에 수행하는 방식 (기본적으로 절차적으로 수행되기때문이다.)

작업을 수행하는데 있어 대기시간을 갖으라는 통지를 받는 개념

<br>

## Non-Blocking

코드를 수행하는 데 어떠한 함수의 결과 처리까지 기다리지 않고 다른 작업 수행을 하고있다가 결과를 조회해 return받는 방식

작업의 완료를 대기하지 않고 나중에 통지받는 개념

<br>

Blocking이 곧 순차처리를 의미하지는 않는다. 어떤 프로세스가 blocking이 되더라도 다른 프로세스가 끼어들 수 있기도하고 없기도 하기 때문이다.

Blocking/Non-Blocking과 Sync/Async의 개념을 같은 의미 선상에 두고 해석하지말고 애초에 다른 개념이라 생각하자.

아래 블로그가 가장 나에게도 와닿고 맞는 설명인것 같다.

<br><br>

---

## Reference

[동기와 비동기 / Blocking 과 NonBlocking](https://jins-dev.tistory.com/entry/%EB%8F%99%EA%B8%B0Synchronous-%EC%9E%91%EC%97%85%EA%B3%BC-%EB%B9%84%EB%8F%99%EA%B8%B0Asynchronous-%EC%9E%91%EC%97%85-%EA%B7%B8%EB%A6%AC%EA%B3%A0-%EB%B8%94%EB%9D%BDBlocking-%EA%B3%BC-%EB%84%8C%EB%B8%94%EB%9D%BDNonBlocking-%EC%9D%98-%EA%B0%9C%EB%85%90)
