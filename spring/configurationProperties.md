# ConfigurationProperties

Spring Boot에서 properties파일에 정의된 프로퍼티중에 해당 `prefix`를 가진 프로퍼티들을 POJO에 맵핑하여 BEAN으로 만들수 있게 해주는 어노테이션

```java
@Component
@ConfigurationProperties(prefix = "my-app")
@Getter @Setter
public class AppProperties {
    @NotEmpty
    private String adminUsername;

    @NotEmpty
    private String adminPassword;
}
```

스프링이 해당 클래스를 bean으로 등록시키게 하기 위해 `@Configuration`이나 `@Component`를 같이 붙여주어야한다.
만약에 붙이지 않는다면 main클래스에 `@EnableCongurationProperties(프로퍼티 크래스명.class)`를 붙여주어야한다.

그러면 아래와 같이 .properties파일에 작성을 하면된다.

```
my-app.admin-username=admin@email.com
my-app.admin-password=admin
```

---

## Reference

https://sgc109.github.io/2020/07/07/spring-boot-configuration-properties/
