LinkedIn에서 처음 개발 한 것으로, 일종의 Pub-Sub모델로 구성된 메세지 큐 구조의 메시지 브로커.
분산 트랜잭션 로그로 구성되어 실시간 데이터 피드를 관리하기 위해 통일된, 높은 처리량, 낮은 지연시간을 갖는 것이 목표인 프로젝트.

## RabitMQ와 차이점
kafka는 single consumer가 아니라 multi consumer를 염두에 두고 설계 되었기 때문에 consumer가 broker로 부터 메시지를 pull해오는 방식으로 처리한다. rabitMQ는 broker가 consumer에게 메시지를 push해주는 방식으로 이는 메시지 소비속도보다 생산속도가 빠를 경우 병목현상이 발생해 consumer에게 많은 부하를 줄 수 있으며 기존에 메모리를 사용하고 다 사용하면 disk로 처리하기 때문에 이또한 병목현상이 발생할 수 있다.

kafka는 애초에 메시지를 disk에 저장하고 offset이라는 개념을 통해 메시지를 자유롭게 관리할 수 있으며, 디스크에 저장할때도 BTree를 사용하지 않고 파일끝에 데이터를 추가하는 방식의 단순 저장방식으로 디스크의 순차탐색을 이용해 읽어오는 방식으로 효율을 끌어올렸다. 

물론 pull방식도 단점이 존재하는데, 주기적으로 polling하기 때문에 자원이 낭비될 수 있다는 부분이다.

## 구성요소
- zookeeper : 클러스터 최신 설정정보 관리나 동기화, 리더 선정 등 클러스터의 서버들이 공유하는 데이터를 관리하기 위해 사용되어 kafka서버를 실행시키기 위해서는 zookeeper가 선행되어야 하며, 현재는 이 의존성을 제거하기 위한 프로젝트도 진행중이다.

- broker : 한개의 kafka sever 이며, 한 클러스터 내에 여러 broker를 실행할 수 있다.
- topic : 메시지가 생산되고 소비되는 큰 `주제`,`제목`이라고 볼 수 있다.
    - partition : 한 토픽내에 메시지가 분산되어 저장되는 단위이며, 큐 방식으로 저장되어 한 파티션내에서는 순서를 보장하지만 서로 다른 파티션끼리는 메시지 순서를 보장해주지 않기 때문에 topic내에 여러 파티션이 있다면 그에 맞게 처리방법이 달라진다.

    - log : partition의 한 칸 한칸을 log라고 하며 key,value,timestamp로 구성된다.
    - offset : partition의 각 메시지를 식별할 수 있는 유니크한 값으로 이를 이용해 consumer에서 데이터를 어디까지 소비했는지 파악한다.

- producer : 특정 topic의 메시지를 발행하는 주체. 한 topic내에 여러 partition이 있다면 default로는 RR방식으로 저장이 된다. 한 partition내에서는 마지막 offset 뒤에 신규 메시지가 저장이 되기 때문에 순서가 보장이 된다.

- consumer : 메시지를 소비하는 주체.
- consumer group : 하나의 consumer group에서는 하나의 topic을 담당하기 때문에 하나의 topic만 접근이 가능하지만, topic은 여러개의 consumer group이 접근 할 수 있다.

    목적 

    - partition접근하는 consumer 관리 : 여러개의 consumer가 한 partition에 접근하여 메시지를 소비하려고 할 때 따로 관리자가 없다면 몇번째의 메시지를 소비하는지 알 수 없기 때문에 이를 관리하기 위해 consumer group이 존재하여 관리
    - offset 공유 : partition에는 하나의 consumer만 접근할 수 있기 때문에 이 consumer가 에러발생했을 때를 대비해서 consumer들의 offset을 공유하고 있어 고가용성이 확보된다.

    위와 같은 이유로 partition의 개수와 consumer의 개수를 잘 설계해야 하는데 partition >= consumer 가 적절하다. consumer가 많아봤자 중복해서 접근할 수 없기 때문에 놀고 있는 consumer가 발생하기 때문.


<br>

## 윈도우 설치
### 1. java 설치
1.8 버전이상의 java 설치하기

### 2. kafka 설치
[kafka 공식 홈페이지](https://kafka.apache.org/downloads)에서 `binary downloads` 파일 다운받아 압축해제

### 3. zookeeper 실행
```sh
# 압축해제한 파일 경로로 이동
cd C:\압축해제한 파일 경로

# zookeeper 실행
bin\windows\zookeeper-server-start.bat config\zookeeper.properties
```
zookeper.properties설정파일을 토대로 bat파일로 실행시키게 되는데 bin\windows 내의 bat파일을 실행해야 윈도우에서 실행이된다.

이때 zookeeper의 default 포트는 2181번이다.

### 4. kafka 실행
```sh
# kafka 실행
bin\windows\kafka-server-start.bat config\server.properties
```
default 포트번호는 9092번.

<br>

## 실행 예제
###  topic 생성
```sh
bin\windows\kafka-topics.bat --create --topic topickname --bootstrap-server localhost:9092
```
### topic check
```sh
bin\windows\kafka-topics.bat --describe --topic topickname --bootstrap-server localhost:9092
```
### console이용해 메시지 발행/소비하기
```sh
#producer
bin\windows\kafka-console-producer.bat --topick topickname --bootstrap-server localhost:9092

#consumer
bin\windows\kafka-console-consumer.bat --topic topickname --bootstrap-server localhost:9092
```





<br><br><br>

----
### Reference
https://github.com/HomoEfficio/dev-tips/blob/master/Kafka%20%EB%91%98%EB%9F%AC%EB%B3%B4%EA%B8%B0.md