## TNT search

설치 방법은 공식 홈페이지에 있어 생략

## N:M관계시 관계 테이블 정보까지 인덱스에 저장하는 방법

```php
 public function toSearchableArray (): array {
        $array = $this->toArray();
        $tags = $this->tags->toArray();
        $tagInfo = '';
        foreach ($tags as $tag){
            $tagInfo = $tagInfo . ' , ' . $tag['title'];
        }
        $array['tags'] = $tagInfo;
        return array(
            'id' => $array['id'],
            'content' => $array['content'],
            'tags' => $array['tags']
        );
    }
```

toSearchableArray()메서드를 이용해서 index에 저장하는 형태를 정의 할 수 있는데 `$this->tags->toArray()`와 같이 연관된 테이블을 조회할 수 있다. N에서 1을 불러오는 경우라면 그대로 바로 적용해도 되지만 1->N 이거나 N:M관계시에는 이중배열이 $tags에 저장이 된다.

하지만 return되는 배열은 일차원배열을 return해야 하기 때문에 `json_encode()`로 일괄 문자열으로 바꿔버려주어야 한다. 이때, implode()를 사용하면 2차원 배열이기 때문에 convert가 되지 않는다.

나는 실제로 쓸모있는 데이터는 tags의 title만 index에 저장되면 되기 때문에 foreach를 이용해 문자열로 serialize해주어 index에 저장되게 해주었다.

```php
//문구 등록
$this->userService->createPost($user, $post);

//tag null이 아니라면 tag 등록과 연결
$tagsRequest = $request['tags'];
if(!empty($tagsRequest)){
    $tags = $this->tagService->createTag($tagsRequest);
    $this->postService->connectWithTags($post, $tags);
}
$post->searchable();
```

post를 save할때 index에 저장된다고 공식문서에서 그랬으니 잘 저장되겠지 싶겠지만 실제로는 문제가 발생한다.

N:M의 관계를 위와 같이 eloquent를 이용해 저장하려고 한다면 post를 저장하고 tags를 저장하고 그다음에서야 post_tag를 저장한다.

그게 뭐가 문제야 싶겠지만 잘 보면 이해할 수 있다. save()을 보면 tags와 연관관계가 맺어지기 전에 호출된다. 그렇기 때문에 index에 tags정보가 저장되지 않는 것이다. post저장하기전에 tags와 관계를 맺으려고 하면 post가 저장되지 않아서 테이블id가없어 관계가 맺어지지 않는다.

이때는 모든 로직을 수행하고 `$post->searchable()`을 수행하여 다시 index에 저장해주면된다. searchable()메서드는 index에 있는 정보라면 수정을 없다면 삽입을 수행한다. 하지만 `shouldBeSearchable()`에서 필터링이 되어 index에 저장하지 않기로 했던 모델도 이 메서드를 수행하면 index에 저장이 되기 때문에 주의해서 사용해야한다.

<br>

## N:M 조회

위와 같이 설정을 했다면 index에는 저장이 되어 search()메서드로 잘 검색이 된다. 하지만 아래와 같이 사용하려고 하면 연관테이블 정보가 검색되지 않는다.

```php
class SearchController extends Controller
{
    public function search(Request $request){
        $keyword = $request->query('keyword');
        $posts = Post::search($keyword)->get();
       return ApiUtils::success($posts);
    }
}
```

이유에 대해 한참 헤매면서 고민을 했는데 이유는 단순했다. 로직이 index에서 정보를 조회해서 그 정보를 그대로 출력해주는 것이 아니라 먼저 search()메서드와 get()메서드를 통해 keyword를 index에서 조회하여 table의 key를 찾는다. 그래서 select 쿼리가 한 번 발생한다.

내용의 탐색만 tntsearch의 index필드를 이용하여 빠르게 검색할 뿐 그 이후는 eloquent와 사용법이 같은 것이었다. Eloquent는 기본이 지연로딩이기 때문에 연관테이블의 정보가 없는 것이다.

tag정보까지 조회하기 위해서는 아래와 같이 return문을 수정해주면된다.

```php
return ApiUtils::success($posts->load('tags'));
```

load()로 tags테이블을 조회하여 반환하면 tag정보까지 잘 반환이 되며 지연로딩시 posts테이블과 tags/post_tag 테이블을 조인하여 조회하기 때문에 select쿼리가 한번 더 발생한다.
