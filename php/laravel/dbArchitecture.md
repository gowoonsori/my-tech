# posts와 tags 합쳐 조회하는 방법

### Eloquent이용

1. $post->with('tags')->get()
2. $post->get()->load('tags)

두 쿼리 모두 post를 select 후 post_tag와 tags를 join하여 컬렉션으로 조회한다.

### 쿼리빌더 작성

```sql
select posts.*, GROUP_CONCAT(t.title separator ', ') as tag_title
from posts
left join post_tag pt on posts.id = pt.post_id
left join tags t on pt.tag_id = t.id
group by  posts.id;
```

group_concat함수를 이용하여 posts내에 tag정보를 string으로 치환하여 가져온 후 response하기 전에 조금 데이터를 손보는 방법

<br>

# users likes tags 합쳐 조회 하는 방법

### Eloquent이용

1. $user->with(['likes','likes.tags'])->get()
   user select / users-likes-posts join하여 select / posts-post_tag-tags join하여 select 총 3번의 쿼리 발생

### 쿼리 빌더 작성

```sql
select posts.*, GROUP_CONCAT(t.title separator ', ') as tag_title
from posts
left join post_tag pt on posts.id = pt.post_id
left join tags t on pt.tag_id = t.id
where posts.id in (
    select p.id
    from users u
    left join likes l on u.id = l.user_id
    left join posts p on p.id = l.post_id
)
group by  posts.id;
```

5번의 join을 통해 한번의 쿼리로 수행

=> 현재는 Eloquent로 수행을 하고 데이터가 많아지고 네트워크를 많이타 쿼리속도가 느려진다면 역정규화를 고려해보거나 db종류를 고려해보자.

## 고민해볼 점

1. 한개의 DB에서 너무 많은 쿼리 호출로 네트워크 병목이 발생한다면 샤딩을 통해 나누어 저장할 수도 있다.

1. posts와 tags정보를 역정규화로 테이블을 합치는 방법

   현재 FTS의 index에 데이터를 저장할때 posts와 tags를 따로 저장하지 않고 posts저장할때 종속적으로 tags를 저장하고 있다.

   -> 만약에 tags를 따로 저장하게 되면 이를 조회하는 과정은 tags index에서 tag id를 찾아내게 되고 이 id를 이용해 posts를 조회하게 될텐데 이 posts에는 또 tags들의 정보들이 없기 때문에 다시 tags를 로딩하는 결과가 발생한다.

   그래서 posts와 tags를 한 index에 같이 집어넣고 검색엔진에서 key값을 이용해 tag와 문구내용(content)를 다르게 검색하는 방법으로 이용하고 있다. 이처럼 FTS에도 tags를 posts와 같이 저장하고 조회를 수행한다면 굳이 테이블을 나누지 않고 한개의 컬럼내에 string으로 표현해도 똑같은 기능을 수행할 수 있을 것 같다.

   그러면 앞에서 말했던 post-tag간의 join하는 문제의 한 depth가 사라져 위의 고민도 해결 될 수 있을 것 같다.
