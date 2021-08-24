[Index API](https://www.elastic.co/guide/en/elasticsearch/client/java-rest/current/_index_apis.html)

인덱스를 `생성`, `삭제`, `존재여부`, `status`(open/close) 여부, `shrink`(샤드 축소), `split`(샤드 확장), `refresh`(루씬의 flush로 이 작업이 수행되어야 세그먼트 파일이 생성돼 새로운 doc이 검색이 가능해진다. 커널에서 시스템 캐시에 파일만 생성/주기적으로 자동 호출 된다.), `flush`(루씬의 commit으로 dixc에 영속성으로 저장외되는 단계)
, `forcemerrge`(루씬의 merge로 여러개의 세그먼트를 합치는 작업으로 memory,disk등을 절약하고 인덱싱을 새로 최적화하여 수행), `rollover`(active index가 오래됬거나 크기가 커벼 빈 인덱스를 만들고 교체가 필요할때 사용)

## GetIndex

```java
GetIndexRequest request = new GetIndexRequest("*");
GetIndexResponse response = client.indices().get(request,RequestOptions.DEFAULT);
```

client의 index의 정보를 client.indices().get()을 통해 조회할 수 있으며 이때 첫번째 인자로 GetIndexRequest()를 통해 특정 index를 리정할 수 있고 `*`을 주어지면 모든 index를 조회한다. (/\_cat/indices 와 동일)

### GetIndexResponse

내부 필드로 `mappings`,`aliases`,`settings`,`defaultSettings`,`dataStreams`,`indices` 가 존재하고 getter를 통해 조회가 가능하다.

#### 1. settings

```JSON
{
    "posts_index" :{
        "index.analysis.analyzer.default_analyzer.tokenizer":"custom_nori",
        "index.analysis.analyzer.default_analyzer.type":"custom",
        "index.analysis.tokenizer.custom_nori.decompound_mode":"mixed",
        "index.analysis.tokenizer.custom_nori.type":"nori_tokenizer",
        "index.creation_date":"1628747766121",
        "index.number_of_replicas":"1",
        "index.number_of_shards":"1",
        "index.provided_name":"posts_index",
        "index.routing.allocation.include._tier_preference":"data_content",
        "index.uuid":"XiDS1v2oRw6EAumynNOvMw",
        "index.version.created":"7130499"
    }
}
```

```java
response.getSettings().get("posts_index").get("index.uuid");
response.getSetting("posts_index","index.uuid");
```

index들의 id, 생성일자, analyzer등과 같은 세팅정보가 Map의 형태로 포함되기 때문에 getSettings()에서 get()을 이중으로 사용하여 값을 조회하거나 getSetting()메서드를 이용해서 세팅정보를 조회할 수 있다.

#### 2. indices

조회한 index들의 이름들을 String[]형태로 포함하고있는 필드

```java
response.getIndices();  //[posts_index]
```

#### 3. aliases

`response.getAliases()`

```json
{
  "posts_index": [
    {
      "posts_index_write": {}
    }
  ]
}
```

index의 별칭들의 정보를 저장하고있는 필드로 `/_cat/aliases`를 이용하여 조회한것과 비슷하다. 이도 Map형태로 저장을 하고 있으며 key로는 index명, value로는 aliases의 메타정보필드 list 가 들어있다.

#### +) /\_cat/indices

위의 명령어나 `?v`를 추가해 column을 포함해 정보를 조회하고 싶다면 lowClient를 이용해 조회할 수도 있다.

```java
Response response = client.getLowLevelClient().performRequest(new Request("GET","/_cat/indices?v"));
String indicies = EntityUtils.toString(response.getEntity(), "UTF-8");

/* response 형식
health status index       uuid                   pri rep docs.count docs.deleted store.size pri.store.size
yellow open   posts_index XiDS1v2oRw6EAumynNOvMw   1   1        119           26    147.9kb        147.9kb
*/

String[] lines = indices.split("\n");
String[] columns = lines[0].split("\\s+");

JsonArray jsonArray = new JsonArray();
for(int i=1; i < lines.length; i++){
    JsonObject jsonObject = new JsonObject();

    String[] states = lines[1].split("\\s+");
    for(int j=0; j < columns.length; j++){
    jsonObject.addProperty(columns[j],states[j]);
    }
    jsonArray.add(jsonObject);
}
JsonObject jsonObject = new JsonObject();
jsonObject.add("indices",jsonArray);

return ResponseEntity.ok(jsonObject.toString());
```

응답이 문자열로 위와 같이 오기 때문에 json형태의 답을 원하면 별도로 파싱을 하여 사용하거나 EntityUtils이 아닌 getContent()메서드를 이용해서 InputStream으로 한 줄 씩 읽어 파싱해서 사용가능하다.
