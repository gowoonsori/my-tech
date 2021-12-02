# Eureka

로컬의 환경에서는 로드밸런서를 통해 서비스의 `발견`을 수행해왔는데 매핑 규칙을 매번 수동으로 지정하는 것은 Cloud Native architecture에 들어서서 부적합하기 때문에 자신의 서비스를 동적으로 등록하고 스스로 라이프 사이클을 관리할 수 있도록 관리 할 수 있게 해주는 기능이 필요해졌고 이러한 작업을 위해 `서비스 디스커버리 매커니즘`가 생겨났다.

서비스 디스커버리 매터니즘은 다음과 같은 특징를 갖는다.

- 서비스 동적 등록 및 정보 공유

  서비스가 시작될때 위치, 포트등 정보를 레지스트리에 동일한 서비스id로 등록 한다. 등록된 서비스는 클러스터에 있는 다른 노드들에게 전파한다.

- 서비스 동적 발견

  정적으로 서비스를 설정하고 관리하는것이 아닌 레지스트리를 통해 바로 바로 사용가능한 url을 발견하고 매번 정보를 업데이트 한다.

- 상태 모니터링 : 각 서비스(인스턴스)들은 자신의 상태를 레지스트리에게 알린다.

<br><br>

## 구성

1. Eureka Server : Eureka client에 해당하는 마이크로서비스들의 상태정보가 등록되어 있는 레지스트리를 갖는다.

1. Eureka Client : 서비스가 시작될 때 Server에 자신의 정보를 등록해서 30초마다 레지스트리에 ping을 보내 가용상태를 알리고 일정 이상 받지 못하면 Server는 서비스를 레지스트리에서 제외시킨다.

가용상태의 서비스 목록을 확인할 경우 서비스의 이름을 기준으로 탐색하며 로드밸런싱을 위해 Ribbon을 내부적으로 사용한다.

<br>

## @EnableEurekaServer

해당 서비스를 Eureka 서버로 지정하기 위해서 서비스 진입점이 되는 클래스에 해당 어노테이션을 붙여주어야 한다.

<br>

## 기본 환경 설정 (application.yml)

1. eureka.client.register-with-eureka
1. eureka.client.fetch-registry

기본값은 true로 자기자신의 정보를 client로 등록하고 상태를 패칭하는 설정으로 다른 서비스들과 통신을 하기 위해서는 true이어야 한다.

1. eureka.client.service-url.defaultZone : `유레카 서버`의 위치를 명시해주어야 한다.
1. eureka.instance.instance-id : instance id를 설정

   ex) `${spring.cloud.client.hostname}:${spring.application.instance_id:${random.value}}`

<br>
<br>

## 추가) IntelliJ에서 하나의 서비스를 실행시킬때 포트옵션을 다르게 주는 방법

IntelliJ에서 설정

1. application.yml에서 server.port 지정

   - server.port를 0으로 실행시키면 random port로 port가 충돌나지 않도록 알아서 지정해서 실행된다.

     하지만 이 경우에는 서비스id가 동일하게 되면 하나의 인스턴스가 등록된것으로 확인이 되기 때문에 `eureka.instance.instance-id`를 통해 인스턴스 이름을 바꾸어 주어야 한다.

1. run configuration에서 Environments -> JVM option으로 -Dserver.port='9001' 지정
   Terminal에서 설정

1. java실행 옵션으로 설정
   `mvn compile package`를 통해 `jar`패키징 후 `java -jar -Dserver.port=9001 파일경로/jar이름.jar`로 jar파일 실행
1. mvn run 명령어에 옵션으로 설정 후 실행

   `mvn spring-boot:run -Dspring-boot.run.jvmArguments='-Dserver.port=9003'`

<br><Br>

## depenecy 추가

Spring boot 버전을 설정하면 그에 맞는 spring cloud버전이 알아서 설정된다.

### Eureka Server

- maven

```xml
<dependency>
    <groupId>org.springframework.cloud</groupId>
    <artifactId>spring-cloud-starter-netflix-eureka-server</artifactId>
</dependency>
```

- gradle

```gradle
dependencies {
  compile 'org.springframework.cloud:spring-cloud-starter-netflix-eureka-server'
}
```

<br>

### Eureka Client

- maven

```xml
<dependency>
    <groupId>org.springframework.cloud</groupId>
    <artifactId>spring-cloud-starter-netflix-eureka-client</artifactId>
</dependency>
```

- gradle

```gradle
dependencies {
  compile 'org.springframework.cloud:spring-cloud-starter-netflix-eureka-client'
}
```
