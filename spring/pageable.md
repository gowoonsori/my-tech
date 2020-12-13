# Pageable

페이징, 정렬을 하기 위해 스프링 데이터 JPA가 제공하는 인터페이스

```java
@GetMapping
    public ResponseEntity queryEvents(Pageable pageable, PagedResourcesAssembler<Event> assembler){
        Page<Event> page = this.eventRepository.findAll(pageable);
        var pagedResources = assembler.toModel(page, e-> new EventResource(e));
        pagedResources.add(new Link("/docs/index.html#resources-events#resources-events-list").withRel("profile"));
        return ResponseEntity.ok(pagedResources);
    }
```

위와 같이 Repository에서 find시에 Pageable을 변수를 넣어주면 Repository는 JPARepository를 상속받고 이는 PagingAndSortingRepository를 상속받고 있어 find에 pageable속성을 넣어 줄 수 있다.

그러면 쿼리문의 `page`,`size(default =20)`,`sort(필드며,정렬 기준(ASC/DESC)`속성으로 pagination할 수 있다.

# PagedResourcesAssembler

pagination을 수행 한 json데이터에 link를 삽입해주기위해 resource로 변환 해주는 클래스

내부적으로 RepresentationModelAssembler을 상속받고 있어 page한 데이터를 객체로 바꾸고 객체에 링크를 추가 해줄 수 있다.

```java
 var pagedResources = assembler.toModel(page, e-> new EventResource(e));
        pagedResources.add(new Link("/docs/index.html#resources-events#resources-events-list").withRel("profile"));
```
