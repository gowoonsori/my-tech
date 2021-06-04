# Maven

프로젝트에서 사용하는 수많은 라이브러리와 라이브러리에 종속관계에 있는 라이브러리들까지 자동으로 관리해주는 도구로 프로젝트의 전체적인 라이프사이클을 관리하는 도구로 빌드까지 수행

<br>

## 라이프 사이클 종류

- 기본(Default)

  1. compile : 프로젝트의 소스코드를 컴파일
  1. test : 유닛 테스트를 수행하는 단게로 (이를 실패시 빌드 실패로 처리)
  1. package -> 산출물 생성 (실제 컴파일된 소스코드와 리소스들을 jar등의 배포릉 위한 패키지로 만드는 단계)
  1. install -> 로컬 저장소 배포 (패키지를 로컬 저장소에 설치)
  1. deploy -> 원격 저장소 배포 (만들어진 패키지를 원격저장소에 release)

- clean

  1. clean : 이전 빌드에서 생성된 파일들을 삭제

- site
  1. site -> 문서 사이트 생성 (프로젝트 문서를 생성)
  1. site-deploy -> 서버 배포

<br>

각 라이프 사이클 안에 `phase`가 존재한다 각 phase를 통해 maven명령을 내릴 수 있고 중간 단계의 phase를 실행 했다면 이전 단계의 라이프사이클 모두 자동으로 실행된다.
<br>(ex. `mvn install`, `Run As`, `Maven clean`등)

> Phase는 build 라이프 사이클 각각의 단게를 의미하며 의존관계를 가지고 있어서 이전의 단계의 Phase가 모두 수행되어야 한다.
>
> Maven에서 제공하는 모든 기능은 플러그인 기반으로 동작
>
> 각각의 Phase는 어떤 일을 할지 정의하지 않고 어떤 플러그인의 Goal을 실행할지 설정

<br>

각 phase에는 plugin이 존재하여 이 `plugin`에서 수행가능한
명령을 `goal`이라고 한다.
<br>(ex. `mvn plugin:goal`형태로 `jar:jar`, `resource:testResource` 등의 형태 )

> 하나의 플러그인에서 여러작업을 수행할 수 있도록 지원하며, 플러그인에서 실행할 수 있는 각각의 기능을 Goal이라고 한다.

<br><br>

## pom.xml

Project Object Model의 약자로 `프로젝트 객체 모델 정보`를 담고 있는 파일을 XML형식의 파일로 정의

### 다루는 정보

- 프로젝트 정보 : 이름, 개발자 목록, 라이센스 등
- 빌드 설정 : 소스, 리소스, 라이프 사이클 별 실행할 플러그인 등
- 빌드 환경 : 사용자 환경 별로 달라질 수 있는 프로파일 정보
- POM 연관 정보 : 의존 모듈, 상위 프로젝트, 하위 모듈 등
  - dependency
    - scope : 범위
    - optional : 다른 프로젝트에 의존성이 추가되지 않는다.

[maven과 gradle 차이](https://hyojun123.github.io/2019/04/18/gradleAndMaven/)

<br><br>

## mvn spring-boot:run과 java -jar 차이

보통 mvn은 코드를 빌드,테스트 및 패키징하는데 도와주는 도구로 `올바른 dependecy 버전`을 해결해주거나 `실행가능한 jar/war 파일의 모든 dependecy를 패키지`하고 `java -jar의 -cp옵션이나 경로 지정`을 할 필요가 없다.

하지만 mvn을 통한 실행은 아파치 톰캣의 다운로드와 톰캣의 시작으로 초기화 하고 goal에 맞는 작업을 수행해야하고 만일 `production`에서 실행하게 된다면 `maven 설치`, `jdk`설치, `코드베이스 복사`, `mvn 모든 생명주기 실행`과 같이 시간과 비용적측면에서 모두 낭비가 된다.

develop단계라면 애플리케이션을 실행할때마다 올바른 환경을 구성하고 변수를 설정하는 것은 비효율적이며 둘이상의 서비스를 동시에 실행할 경우는 더더욱 비효울적일 것이다.

이럴때는 maven을 이용하는 것이 더 효율적일 수 있다.

<br><br><br>

---

## Reference

https://www.baeldung.com/spring-boot-run-maven-vs-executable-jar
