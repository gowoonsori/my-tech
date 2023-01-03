# Kafka Connect
각종 데이터 소스(DB, searchEngine, cache, metric ...)와 kafka를 연결해주는 일종의 매개체. Connect에는 Connector들을 등록하여 여러 데이터소스와 연결할 수 있으며 오픈소스의  connector들이 많이 존재한다.

Producer역할을 수행하여 메시지를 발행하는 connector를 `source connector`라고 하며, consumer 역할을 수행하는 connector를 `link connector`라고 한다.

# debezium
source connector중 오픈소스 프로젝트로 각종 db의 변경사항을 캡처하여 처리할 수 있도록 해주는 분산 서비로 데이터 변경을 changed event stream에 기록하여 이 변경 이벤트를 순서대로 읽게 된다.

MySQL같은 경우 binlog에 접근하고 postgres의 경우 logical replication stream에 접근한다.

Kafka의 connector로 등록을 할 수도 있지만 `Embedded Engine`을 사용하면 커넥터를 사용하지 않고 자바 애플리케이션 라이브러리로써 사용이 되어 변경이벤트를 바로 consuming 하거나 다른 메시지 브로커에게 전달도 가능하다.


## 실행
### 1. debezium 설치
[debezium 공식 홈페이지](https://debezium.io/releases/1.6/)에서 debezium을 다운받아 압축해제 해준다.

### 2. connect의 plugin으로 등록
`kafka설치 경로\config\connect-distributed.properties` 파일을 열어 plugin.path에 debezium 설치 경로를 추가해준다. 
```sh
plugins.path=C:\kafka-connect-plugins\
```
이때 connect-distributed 분산환경에 적합한 모드이며  connect-stadalone모드는 1개의 프로세스로 동작하는 connect이다. connect 프로세스가 구성을 저장할 위치, 작업할당 바업, 오프셋 및 작업 조각 저장 위치를 결정하는 방법이 달라지게 되기 때문에 실행할 모드에 맞는 설정파일을 수정하면된다.

### 3. kafka connect 실행
```sh
bin\windows\connect-distributed.bat -daemon config\connect-distributed.properties
```
default 포트번호는 8083번.

### 4. connector 확인
```sh
# kafka connect 실행확인
curl -s "http://ip:8083"

# 사용할 수 있는 플러그인 확인
curl -X GET -s "http://ip:8083/connector-plugins"

# kafka connector 확인
curl -X GET -s "http://ip:8083/connectors"
```
위 명령어는 curl을 사용해도 되지만 postman으로 확인한다면 응답을 더 이쁘게 볼 수 있다.

플러그인에 우리가 설치한 debezium이 있어야 하며, connector에는 아직 없는것이 정상이다.

### 5. DB 접근권한 설정
MySQL기준으로 binlog에 debezium이 접근이 가능해야하기 때문에 이를 위한 설정을 해주어야 한다.
#### 1. log_bin 활성화
```sql
show variables like 'log_bin';
```
위 변수가 `on`상태여야 한다.

만일 off라면 mysql 실행시 `--log-bin=ON`과 같은 옵션으로 주거나 `my.cnf`의 mysqld 섹션에 옵션을 설정해주면 된다.

### 2. binlog level이 low-level
```sql
show variables like 'binlog_format';  # ROW 여야 한다.
```

### 3. binlog접근 권한 계정 생성
```sql
grant select, reload, super, replication slave, replication client on *.* to 계정아이디@'%' identified by '비밀번호';

flush privileges;

```

### 4. connector 생성
```sh
echo '
{
    "name" : "mysql-kafka-connect",
    "config":{
        "connector.class" : "io.debezium.connecotr.mysql.MySqlConnector",
        "database.hostname": "localhost",
        "database.port" : "3306",
        "database.user" : "db 계정아이디",
        "database.password" : "비밀번호",
        "database.server.name" : "서버 이름",
        "database.history.kafka.bootstrap.servers" : "localhost:9092",
        "database.history.kafka.topic" : "topic 이름",
        "include.schema.changes" : "true" | "false",
        "database.whitelist" : "접근할 table 명",
        "database.serverTimezone" : "Asia/Seoul"
    }
}
'|curl -X POST -d @- http://localhost:8083/connecotrs --header "content-Type:application/json"
```
위 형식을 postman을 이용해 body로 전달하면 좀더 편하게 요청을 보낼 수 있으며 더많은 옵션이 존재하는데 이는 공식홈페이지에 친절하게 설명이 모두 나와있다. 

```sh
# kafka connector 확인
curl -X GET -s "http://ip:8083/connectors"
```
정상적으로 connector가 등록되었다면 위 명령으로 생성한 connector를 확인 해볼 수 있다.

### 번외. 
```sh
# kafka connector 설정확인
curl -X GET -s "http://ip:8083/connectors/test-connector/config"

# kafka connector 상태확인
curl -X GET -s "http://ip:8083/connectors/test-connector/status"

# kafka connector 삭제
curl -X DELETE -s "http://ip:8083/connectors/test-connector"
```