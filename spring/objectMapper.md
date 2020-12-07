# Object Mapper

JackSon 라이브러리 내에 존재하며, Json과 상호 변환시 세부 설정이 필요할때 이 객체를 이용하여 설정 할 수 있다.

## Object <-> JSON

객체를 Json형태로 Serialization, DeSerialization 시켜주는 역할을 수행할 수 있게 메서드들이 정의 되어있다.

### writeValue("출력 장치", objcect)

출력장치 (stream out, file, JsonGenrator..)에 객체를 Json형태로 바꿔 출력 해주는 함수

### writeValueAsString(obj)

객체를 Json형태로 바꿔 String으로 return해주는 함수

### writeValueAsBytes(obj)

객체를 Json형태로 바꿔 byte으로 return해주는 함수

### readValue([json,fiel,url], 변환 타입(ex obj.class))

json Parser, file, url을 통해 json형태의 데이터를 obj로 바꿔주는 함수
