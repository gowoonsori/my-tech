# MySQL 연결

## dependency 추가

```xml
<dependency>
  <groupId>org.springframework.boot</groupId>
  <artifactId>spring-boot-starter-data-jpa</artifactId>
</dependency>
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
</dependency>
```

spring-boot-starter-data-jpa : JPA/Hibernate 의존성

## properties 추가

```
spring.datasource.username= username
spring.datasource.password=password
spring.datasource.url=jdbc:mysql://localhost:3306/rest_study?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&characterEncoding=UTF-8&serverTimezone=Asia/Seoul&allowPublicKeyRetrieval=true&useSSL=false

spring.jpa.hibernate.ddl-auto=create-drop
spring.jpa.properties.hibernate.jdbc.lob.non_contextual_createion=true
spring.jpa.properties.hibernate.format_sql=true

logging.level.org.hibernate.SQL=DEBUG
logging.level.org.hibernate.type.descriptor.sql.BasicBinder=TRACE
```

- spring.jpa.hibernate.ddl-auto : DB 초기화 전력으로
  - none : 자동생성하지 않는다.
  - update : 변경된 스키마를 적용하고 제거는 하지 않는다.
  - validate : 변경된 스키마가 있는지 확인만 하고 변경이 있다면 종료
  - create : 시작될때만 drop하고 다시 생성
  - create-drop : 시작과 종료에 모두 drop
- spring.jpa.properties.hibernate.format_sql=true

  사용된 sql문을 formatting하여 보기 편하게 만들어주는 옵션

- logging.level.org.hibernate.SQL=DEBUG
- logging.level.org.hibernate.type.descriptor.sql.BasicBinder=TRACE

  사용된 sql문을 로깅하기 위한 옵션

## Test는 H2 를 사용하기 위한 설정

`test`에 `resoruces/application-test.properties`를 만들어 application.properties와 중복되는 부분은 override하여 실행되게 설정

`Project Structure` -> `Modules` -> `Test Resource Folders`에 새로 만든 `resoruces/application-test.properties`를 추가

```
spring.datasource.username=sa
spring.datasource.password=
spring.datasource.url=jdbc:h2:mem:testdb
spring.datasource.driver-class-name=org.h2.Driver

spring.datasource.hikari.jdbc-url=jdbc:h2:mem:testdb

spring.jpa.properties.hibernate.dialect=org.hibernate.dialect.H2Dialect
```

## DB 사용자 정보

application.properties를 기본적으로 git에 올리고 있다면 db 사용자 정보가 유츌이 될 수 있으므로 따로 properties를 만들고 .gitignore로 적용하자.

jdbc.properties

```
spring.datasource.username=id
spring.datasource.password=pass
spring.datasource.url=jdbc:mysql://localhost:3306/rest_study?useUnicode=true&useJDBCCompliantTimezoneShift=true&useLegacyDatetimeCode=false&characterEncoding=UTF-8&serverTimezone=Asia/Seoul&allowPublicKeyRetrieval=true&useSSL=false
```

후에 build시에 이 properties도 적용시켜줘야 db에 연결이 가능하므로 `@PropertySource(value = { "classpath:jdbc.properties" })`을 main 메서드에 붙여주자.
