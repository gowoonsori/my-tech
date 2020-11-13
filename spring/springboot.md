# Spring Boot

Spring Framework를 기반으로한 프로젝트로써 최소한의 설정으로 스프링 플랫폼과 서드파티 라이브러리들을 사용할 수 있도록 해준다.

<br>

## 특징

- 내장형 톰캣, 제티 혹은 언더토우를 내장하여 war파일로 배포할 필요가 없음

- 기본설정이 자동으로 되어 있으며, 자주 사용하는 프로젝트 조합이 미리 준비

- 의존성 관계 자동 관리

- 상용화에 필요한 통계, 상태 점검 및 외부설정을 제공

- 설정을 위한 XML 코드를 생성하거나 요구하지 않음

<br>

## 파일 구조 (Gradle)

```
project
    └ src
        └ main
            └ java
                └ 프로젝트명
                    └ Application.java
            └ resources
                └ static
                └ templates
                └ application.properties
        └ test
    └ gradle
    └ build.gradle

```

- Application.java : 프로젝트 생성시 기본적으로 생성되는 main java파일 (controller 부분)

- resources : 정적 파일들이 위치하며, 각종 spring boot 설정들이 모여있는 디렉토리로 Mybatis, css, js, html, log4j2-sping.xml등 존재

  - templates : templete engine 사용시 view 코드들을 위치하기 위한 공간 ( templete engine으로 thymeleaf가 있다.)

  - static : css, js, html파일이 위치한다.

  - application.properties : 공통 properties나 database설정

<br><br>

---

## Reference

설명 - https://zetawiki.com/wiki/%EC%8A%A4%ED%94%84%EB%A7%81%EB%B6%80%ED%8A%B8_SpringBoot
