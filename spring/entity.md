# Entity

실제 DB 테이블과 매칭될 클래스로 `@Entity`,`@Column`,`@Id` 등의 어노테이션을 이용한다.

DB테이블과 1:1로 매핑 되는 클래스로 DB 테이블의 컬럼만 필드로 가지는 클래스이다. (@Entity 어노테이션으로 명시해 엔티티 클래스임을 지정해서 테이블과 1:1매핑)

주로 DB와 통신을 위해 사용

객체의 일관성을 위해 무분별한 setter은 금지

- @Table : Entity클래스의 이름과 테이블 명과 일치하는 것을 매핑하며, 이름이 다를 경우 @Table(name="")으로 매핑이 가능하다.

- @Id : pimary key를 갖는 변수 선언

  - @GeneratedValue : 해당 Id값을 어떻게 자동으로 생성할지 전략을 선택할 수 있다.

- @Column : 꼭 선언이 필요한 것은 아니지만 지정한 변수명과 DB의 컬럼명을 다르게 해주고 싶다면 @Column(name="")으로 작성하면 된다.

### Enum 값 매핑시 @Enumerated(EnumType.STRING)을 통해 enum 내부 순서가 바뀌었을 때 문제가 생기는 것을 방지

# DTO

데이터 전송 객체로 주로 비동기 처리를 할때 사용된다.

Spring Boot같은 경우 기본으로 JackSon 라이브러리를 제공해 ObjectMapper를 사용해서 객체를 JSON으로 변환 시켜주지만, Spring에서는 의존성을 주입시켜주어야 하고, 내가 원하는 필드만 골라내서 JSON형식으로 파싱후 전송하기 위해 데이터 가공을 위해서 DTO를 생성

비즈니스 로직을 가지고 있지 않은 순수한 데이터 객체로 getter와 setter만 존재한다.

View와의 통신을 위해 사용

# VO

Read Only의 객체로 equals(), hashcode()를 오버라이딩 하는 것이 핵심 역할이다.
