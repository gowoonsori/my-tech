# Custom Serialize

기본적인 도메인들은 자바 빈 스펙을 따르기 때문에 `BeanSerializer`에 의해서 `Serialize/Deserialize`가 가능 하다.(ObjectMapper)

하지만 Error와 같이 빈 스펙을 따르지 않아 불가능하거나 Custom Serialize를 구현하고 싶다면, `@JsonComponent`와 `JsonSerialzer<>`를 상속받아 `serialize`를 overriding 해주자.

```java
@JsonComponent
public class LongToStringSerializer extends StdSerializer<Long> {

    @Override
    public void serialize(Long val, JsonGenerator jsonGenerator, SerializerProvider serializerProvider) throws IOException {
        jsonGenerator.writeString(val.toString());
    }
}
```

```java
@JsonComponent
public class ErrorsSerializer extends JsonSerializer<Errors> {
    @Override
    public void serialize(Errors errors, JsonGenerator gen, SerializerProvider serializerProvider ) throws IOException {
        gen.writeFieldName("errors"); //error객체 이름
        gen.writeStartArray();        //error가 여러개 일 수 있으니 Array형태
        errors.getFieldErrors().forEach( e -> {
            try{
                gen.writeStartObject();
                gen.writeStringField("field",e.getField());
                gen.writeStringField("objectName",e.getObjectName());
                gen.writeStringField("code",e.getCode());
                gen.writeStringField("defaultMessage",e.getDefaultMessage());
                Object rejectedValue = e.getRejectedValue();
                if(rejectedValue != null){
                    gen.writeStringField("rejectedValue",rejectedValue.toString());
                }
                gen.writeEndObject();
            }catch (IOException ex){
                ex.printStackTrace();
            }
        });
        errors.getGlobalErrors().forEach(e->{
            try{
                gen.writeStartObject();
                gen.writeStringField("objectName",e.getObjectName());
                gen.writeStringField("code",e.getCode());
                gen.writeStringField("defaultMessage",e.getDefaultMessage());
                gen.writeEndObject();
            }catch (IOException ex){
                ex.printStackTrace();
            }
        });
        gen.writeEndArray();
    }
}

```
