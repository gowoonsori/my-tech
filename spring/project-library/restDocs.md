# Spring REST Docs

Spring MVC Test를 이용해서 REST API 문서의 조각(`snippets`)을 생성하는데 도움을 주는 라이브러리

기본적으로 `Asciidoctor`를 사용하여 html파일을 생성하고, 원하는 경우 Markdown을 사용할 수 있다.

API를 정의하는데 사용하는 다른 라이브러리는 `Swagger`가 있다.

## Swagger와의 차이점

`Swagger`는 API를 `테스트` 해볼 수 있는 `화면을 제공`하고 `실제 코드`에 어노테이션을 `추가`해야하지만 `Spring Rest Docs`는 테스트코드를 통해 생성되므로 실제코드에는 영향이 없다.

## 사용법

- MockMvc, WebTestClient등에 사용이 가능하며 test에 사용하는 mockMvc를 만들때 documentationConfiguration을 사용하여 생성하고 MockMvc로 테스트 중 andDo를 이용하여 생성

- Spring Boot에서는 간단히 `@AutoConfigureRestDocs`만 붙여주면 사용이 가능하다.

Test내용이 바뀌거나 다시 실행할때마다 Override하여 문서가 다시 작성된다.

## 메서드

- andDo(document(“doc-name”, snippets))

  - snippets

    - links()
    - requestParameters() + parameterWithName()
    - pathParameters() + parametersWithName()
    - requestParts() + partWithname()
    - requestPartBody()
    - requestPartFields()
    - requestHeaders() + headerWithName()
    - requestFields() + fieldWithPath()
    - responseHeaders() + headerWithName()
    - responseFields() + fieldWithPath()
    - ...

      ```java
      this.mockMvc.perform(post("/api/events")
                  .contentType(MediaType.APPLICATION_JSON)
                  .accept(MediaTypes.HAL_JSON)
                  .content(this.objectMapper.writeValueAsString(event)))
              .andDo(print())
              .andExpect(status().isCreated())
              .andExpect(jsonPath("id").exists())
              .andExpect(header().exists(HttpHeaders.LOCATION))
              .andExpect(header().string(HttpHeaders.CONTENT_TYPE,"application/hal+json;charset=UTF-8"))
              .andExpect(jsonPath("free").value(false))
              .andExpect(jsonPath("offline").value(true))
              .andExpect(jsonPath("eventStatus").value(EventStatus.DRAFT.name()))
              .andExpect(jsonPath("_links.self").exists())
              .andExpect(jsonPath("_links.query-events").exists())
              .andExpect(jsonPath("_links.update-event").exists())
              .andDo(document("create-event",
                      links(
                           linkWithRel("self").description("link to self"),
                           linkWithRel("query-events").description("link to query-events"),
                           linkWithRel("update-event").description("link to update-event")
                      ),
                      requestHeaders(
                              headerWithName(HttpHeaders.ACCEPT).description("accept header"),
                              headerWithName(HttpHeaders.CONTENT_TYPE).description("content type header")
                      ),
                      requestFields(
                          fieldWithPath("name").description("Name of Event"),
                          fieldWithPath("description").description("Description of Event"),
                          fieldWithPath("beginEnrollmentDateTime").description("등록시작기간 of Event"),
                          fieldWithPath("closeEnrollmentDateTime").description("등록마감기간 of Event"),
                          fieldWithPath("beginEventDateTime").description("시작기간 of Event"),
                          fieldWithPath("endEventDateTime").description("종료기간 of Event"),
                          fieldWithPath("location").description("location of Event"),
                          fieldWithPath("basePrice").description("BasePrice of Event"),
                          fieldWithPath("maxPrice").description("MaxPrice of Event"),
                          fieldWithPath("limitOfEnrollment").description("등록 제한 of Event")
                      )
                      ,responseHeaders(
                              headerWithName(HttpHeaders.LOCATION).description("location header"),
                              headerWithName(HttpHeaders.CONTENT_TYPE).description("content type header")
                      ),
                      responseFields(
                              fieldWithPath("id").description("identifier of Event"),
                              fieldWithPath("name").description("Name of Event"),
                              fieldWithPath("description").description("Description of Event"),
                              fieldWithPath("beginEnrollmentDateTime").description("등록시작기간 of Event"),
                              fieldWithPath("closeEnrollmentDateTime").description("등록마감기간 of Event"),
                              fieldWithPath("beginEventDateTime").description("시작기간 of Event"),
                              fieldWithPath("endEventDateTime").description("종료기간 of Event"),
                              fieldWithPath("location").description("location of Event"),
                              fieldWithPath("basePrice").description("BasePrice of Event"),
                              fieldWithPath("maxPrice").description("MaxPrice of Event"),
                              fieldWithPath("limitOfEnrollment").description("등록 제한 of Event"),
                              fieldWithPath("offline").description("오프라인인지 of Event"),
                              fieldWithPath("free").description("무료인지 of Event"),
                              fieldWithPath("eventStatus").description("eventStatus of Event"),
                              fieldWithPath("_links.self.href").description("link to self"),
                              fieldWithPath("_links.query-events.href").description("link to query-events"),
                              fieldWithPath("_links.update-event.href").description("link to update-event")
                      )
                      ));
      ```

- Relaxed\* : 모든 필드에 대해 기술 하지 않아도 문서화를 시켜주기 위한 prefix

  문서 일부분만 테스트 할 수 있다는 장점이 있지만, 정확한 문서화가 불가능 하다.

- Processor
  - preprocessRequest(prettyPrint())
  - preprocessResponse(prettyPrint())
    ```java
    configurer.operationPreprocessors().withRequestDefaults(prettyPrint()).withResponseDefaults(prettyPrint());
    ```

## Customize

json형태를 한줄로 포맷팅하지 않은 채로 response하기 때문에 보기가 매우 불편하기 때문에 보기 편하게 foramatting하여 출력하게 RestDocksMockMvcConfigurationCustomizer 구현한 빈을 등록(내부에 prettyPrint 이용)하여 사용하고 Test클래스에 `@Import(RestDocsConfiguration.class)`을 통해 생성한 커스텀 설정을 적용해야 사용이 가능하다.

```java
@TestConfiguration //Test에만 사용하는 configuration이다.
public class RestDocsConfiguration {

    @Bean
    public RestDocsMockMvcConfigurationCustomizer restDocsMockMvcConfigurationCustomizer(){
        return new RestDocsMockMvcConfigurationCustomizer() {
            @Override
            public void customize(MockMvcRestDocumentationConfigurer configurer) {
                configurer.operationPreprocessors()
                        .withRequestDefaults(prettyPrint())
                        .withResponseDefaults(prettyPrint());
            }
        }
    }
}
//replace기능 이용하여 람다로 바꾸면
@TestConfiguration
public class RestDocsConfiguration {

    @Bean
    public RestDocsMockMvcConfigurationCustomizer restDocsMockMvcConfigurationCustomizer(){
        return configurer -> configurer.operationPreprocessors().withRequestDefaults(prettyPrint())
                .withResponseDefaults(prettyPrint());
    }
}
```

## build

- build하기 위해 dependecny 추가

```xml
<plugin>
                <groupId>org.asciidoctor</groupId>
                <artifactId>asciidoctor-maven-plugin</artifactId>
                <version>1.5.8</version>
                <executions>
                    <execution>
                        <id>generate-docs</id>
                        <phase>prepare-package</phase>
                        <goals>
                            <goal>process-asciidoc</goal>
                        </goals>
                        <configuration>
                            <backend>html</backend>
                            <doctype>book</doctype>
                        </configuration>
                    </execution>
                </executions>
                <dependencies>
                    <dependency>
                        <groupId>org.springframework.restdocs</groupId>
                        <artifactId>spring-restdocs-asciidoctor</artifactId>
                        <version>2.0.5.RELEASE</version>
                    </dependency>
                </dependencies>
            <plugin>
                <artifactId>maven-resources-plugin</artifactId>
                <version>2.7</version>
                <executions>
                    <execution>
                        <id>copy-resources</id>
                        <phase>prepare-package</phase>
                        <goals>
                            <goal>copy-resources</goal>
                        </goals>
                        <configuration>
                            <outputDirectory>
                                ${project.build.outputDirectory}/static/docs
                            </outputDirectory>
                            <resources>
                                <resource>
                                    <directory>
                                        ${project.build.directory}/generated-docs
                                    </directory>
                                </resource>
                            </resources>
                        </configuration>
                    </execution>
                </executions>
            </plugin>
            <plugin>
                <groupId>org.springframework.boot</groupId>
                <artifactId>spring-boot-maven-plugin</artifactId>
            </plugin>
```

- main패키지 아래 asciidoc 폴더를 만들어 `index.adoc`파일 생성

- maven의 package로 build

  빌드하면 `asciidoctor-maven-plugin`이 asciidoc파일을 html로 만들어 genreated-docs 아래 `index.html`이 생성된다.

  `maven-resources-plugin`에 따라 build된 generated-docs에 생성한 파일을 build의 static파일 아래 생성해줌으로써 spring boot특성을 이용해 서버실행시 url로 접근이 가능하다.

<br><Br>

---

## Reference

https://docs.spring.io/spring-restdocs/docs/2.0.5.RELEASE/reference/html5/

https://narusas.github.io/2018/03/21/Asciidoc-basic.html
