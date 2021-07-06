Route에서 설명한 view()메서드를 통해 view를 반환 할 수 있는데 이때 몇가지 규칙이 존재한다.

1. view들의 파일 경로는 resources/view 하위
1. 하위 디렉토리에 있는 뷰 파일은 `.`으로 참조할 수 있다. (`/`도 가능)
    - `view('errors/503')` | `view('errors.503')`
1. view 파일의 형태는 `파일이름.blade.php`나 `파일이름.php`와 같은 모양이다.
1. 뒤에 확장자 없이 파일이름만 view()의 인자로 넘긴다.

<br><br>

## 데이터 바인딩
### with()
```php
Route::get('/', function(){
    return view('welcome')->with('name','Foo');
});
```
view메서드를 통해 반환된 뷰인스턴스에 with()메서드를 체인하여 데이터를 바인딩 할 수 있다.

<br>

### view()
```php
Route::get('/', function(){
    return view('welcome',[
        'name'=>'Foo',
        'greeing' => '안녕하세요'
    ];
});
```
view()함수에 두번째 인자로 넘기는 방법을 통해서도 바인딩 할 수 있으며 이방법을 더 많이 사용한다.