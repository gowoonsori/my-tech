Elasticsearch, Logstash, Kibana의 앞 글자를 따서 보통 ELK스택이라고들 부른다.

<br>

## Elastic Search

`아파치 루씬`기반의 검색엔진 오픈소스로 데이터 수집, 보강, 저장, 분석, 시각화를 위한 도구

로그,메트릭 등 다양한 데이터를 ElasticSearch가 받으면 이를 색인하고 이 데이터에 대해 쿼리(KQL)을 통해 검색할 수 있다.

Json형태로 데이터를 저장하고 데이터의 `key`를 `인덱스`라고 부르며 이를 통해 데이터들을 쉽게 분류하고 검색할 수 있다.

<br>
### 특징

1. `루씬`기반으로 검색속도가 빠르다.
1. `샤드`라고 하는 다른 컨테이너에 분산해 데이터를 저장하기 때문에 데이터를 분산 처리할 수 있다.
1. `Roll up`, `수명 주기 관리` 등 다양한 기능 제공
1. 데이터 수집(Beats, Logstash), 시각화(Kibana)등을 쉽게 구성 할 수 있다.

<br><br>

## Kibana

마찬가지로 오픈 소스 프론트엔드 애플리케이션이다.

ElasticSearch에서 색인된 데이터 들을 `차트`, `표`, `지도` 등 다양하게 시각화하고 보여주는 기능을 한다.

<br><br>

## 데이터 수집

### ◾ Logstash

실시간 파이프라인 기능을 가진 오픈소스 `데이터 수집` 엔진이다.

다양한 모듈,플러그인들이 존재하고 TCP, file등 다양한 방법으로 input(수집)을 할 수 있고 출력(out)도 다양하게 커스텀할 수 있다.

데이터 수집기능도 하지만, ElasticSearch로 보내기전 수집한 데이터를 pipeline을 통해 한번 `가공(filtering)`도 가능하다.

- logstash.yml : 실행 옵션을 설정하는 파일로 `파이프 라인`설정, `구성 파일 위치`, `로깅 옵션`등 지정할 수 있다.
  - pipeline.id (path.config) : 파이프라인의 id와 설정파일 경로를 지정
- pipeline.yml : 파이프라인들을 설정하는 파일이고 이 파일이 없어도 기본값으로 `logstash.yml`을 읽는다.
- `파이프라인 설정파일.conf` : 입력과 출력에 대해 설정을 할 수 있고, filtering을 추가할 수 있다.

  - mutate : 데이터타입을 변경하는 등 전처리 작업을 수행

    - gsub : 전처리 수행

  - grok : 비정형 데이터를 정형 데이터로 파싱하는 라이브러리로 `key/value`형태로 파싱
  - date : 날짜 수정(timezone), formatting

<br>

### ◾ beats

모든 데이터를 수집할 수 있는 Logstash는 무겁다는 단점이 존재하여 나오게 된 `경량 수집` 엔진이다.

- Filebeat
- Metricbeat
- Packetbeat
- Winlogbeat
- Auditbeat
- Heartbeat
- Functionbeat
  위와 같은 beat종류가 존재하며 사용자가 필요한 목적에 맞는 beat만 선택해 데이터를 수집할 수 있다.

이것도 output으로 Logstash뿐만이 아닌 ElasticSearch, kafka등 다양한 출력이 가능하다.

#### [beats.yml](https://www.elastic.co/guide/en/beats/filebeat/current/filebeat-reference-yml.html)

<br><br><br>

공식 홈페이지가 설명이 자세하게 너무 잘나와있다.

<br><br>

---

## Reference

https://www.elastic.co/kr/
