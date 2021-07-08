blade에 추가할 수 있는 부분
- {!! csrf_field() !!} : crsf공격을 막기 위해 _token키를 가진 숨은 필드를 만드는 도우미 함수인데, 이 함수가 출력한 html태그를 이스케이프하지 않기 위해 `{!! !!}`문법을 사용
- <intput type="text" name="title" id="title" value="{{old('title')}}"> = old() : 유효성 검사에 실패해서 이 페이지로 다시 돌아왔을 때 사용자가 입력했던 값을 유지하기 위한 도우미 함수로 세션에 인자로 넘긴 키가 없으면 null을 반환한다.

<br>

## Controller 작성

### 1. 기본방법
```php
class ArticlesController extends Controller{
    public function store(Request $request){
        $rules = [ 
            'title' => ['required'],
            'content' => ['required', 'min:10'],
        ];

        $validator = \Validator::make($request->all(), $rules);
        if($validator->fails()){
            return back()->withErrors($validator)->withInput();
        }

        $article = \App\User::find(1)->articles()->create($request->all());
        if(!$article){
            return back()->with('flash_message','글이 저장되지 않았습니다.')->withInput();
        }

        return redirect(route('articles.index'))->with('flash_message','작성하신 글이 저장되었습니다.');
    }
}
```
- $rules : 유효성 검사를 위한 규칙을 정의할 배열로 연관된 배열로 표현하거나 `required|min:10`처럼 문자열로 표현해도 된다.
    - [유효성 검사 공식 문서](https://laravel.com/docs/validation)
    - [유효성 검사 한글 공식 문서](https://laravel.kr/docs/validation)

- $validator : \Validator::make())메서드로 유효성 검사를 수행할 수 있는데 첫번째 인자는 검사의 대상이 되는 폼 데이터이고, 두번째가 규칙이다.
    - $validator()->passes() : 검사 성공시 true
    - $validator()->fails() : 검사 실패시 true

- back() : 이전 페이지로 리다이렉션 하는 메서드로 `redirect(route('articles.create'))`와 같다.
    - withErrors() : 유효성 검사기 인스턴스를 인자로 받아 검사 실패 이유를 세션에다 저장하는 메서드
    - withInput() : 폼 데이터를 세션에 저장하는 역할로 view의 old()함수는 이 메서드가 저장한 데이터를 읽는다.
    - with() : 인자로 받은 key-value 쌍을 세션에 저장하는 역할로 사용자에게 `피드백`을 제공하기 위해 사용


<br>

### 입력폼에 따른 오류메시지 설정
```php
class ArticlesController extends Controller{
    public function store(Request $request){
        $rules = [ 
            'title' => ['required'],
            'content' => ['required', 'min:10'],
        ];

        $massages = [
            'title.required' => '제목은 필수 입력 항목입니다.',
            'content.required' => '본문은 필수 입력 항목입니다.',
            'content.min' => '본문은 최소 :min 글자 이상이 필요합니다.',
        ]

        $validator = \Validator::make($request->all(), $rules, $massages);
        if($validator->fails()){
            return back()->withErrors($validator)->withInput();
        }

        $article = \App\User::find(1)->articles()->create($request->all());
        if(!$article){
            return back()->with('flash_message','글이 저장되지 않았습니다.')->withInput();
        }
        
        return redirect(route('articles.index'))->with('flash_message','작성하신 글이 저장되었습니다.');
    }
}
```
$validator의 값에는 영어값이 저장되어 에러가 영어로 표시되는데 전역 언어 설정을 한글로 바꾸어도 영어로 표시된다. 이는 유효성 검사 오류를 표시하는 언어 파일이 없어서이다. 이는 위코드와 같이 make()메서드의 세번째 인자로 메시지를 정의한 배열을 주면 한글로 표시되는 것을 볼 수 있다.


<br>
<br>

### 2. 트레이트 메서드 이용
```php
class ArticlesController extends Controller{
    public function store(Request $request){
        $rules = [ 
            'title' => ['required'],
            'content' => ['required', 'min:10'],
        ];

        $massages = [
            'title.required' => '제목은 필수 입력 항목입니다.',
            'content.required' => '본문은 필수 입력 항목입니다.',
            'content.min' => '본문은 최소 :min 글자 이상이 필요합니다.',
        ]

        $this->validate($request->all(), $rules, $massages);
      
        $article = \App\User::find(1)->articles()->create($request->all());
        if(!$article){
            return back()->with('flash_message','글이 저장되지 않았습니다.')->withInput();
        }
        
        return redirect(route('articles.index'))->with('flash_message','작성하신 글이 저장되었습니다.');
    }
}
```
상속받은 Controller는 `Illuminate\Foundation\Validation\ValidatesRequests`트레이트를 임포트 하고 있는데 이 클래스의 `validate()`메서드를 이용해서 1번의 방법인 `\Validator::make()`와 같은 역할을 수행할 수 있다.

<br><br>

### 3. 폼 리퀘스트 클래스 이용
`php artisan make:request ArticlesRequest` 명령어로 폼 리퀘스트 클레스를 만들면 `app/Http/Requests`디렉토리 밑에 생성이 된다.

```php
//ArticleRequest
class ArticleRequest extends FormRequest
{
    public function authorize()
    {
        return true;
    }

    public function rules()
    {
        return [ 
            'title' => ['required'],
            'content' => ['required', 'min:10'],
        ];
    }

    public function messages(){
        return [
            'required' => ':attribute는 필수 입력 항목입니다.',
            'min' => ':attribute는 최소 :min글자 이상이 필요합니다.',
        ];
    }
    
    public function attributes(){
        return [
            'title' => '제목',
            'content' => '본문',
        ];
    }
}

//ArticlesController
class ArticlesController extends Controller{
    public function store(\App\Http\Requests\ArticlesRequest $request){
        $article = \App\User::find(1)->articles()->create($request->all());
        if(!$article){
            return back()->with('flash_message','글이 저장되지 않았습니다.')->withInput();
        }

        return redirect(route('articles.index'))->with('flash_message','작성하신 글이 저장되었습니다.');
    }
}
```
- authorize() : 사용자가 이 클래스를 주입받는 메서드에 접근할 권한이 있는지를 검사하여 서비스를 보호하는 일을 수행
- rules() : 역할들 정의
- messages() : 오류메시지들 정의
- attributes() : 오류 메시지에 표시할 필드 이름을 사용자가 커스텀하여 바꿀 수 있고 이 메서드가 존재하지 않으면 필드 이름을 default로 오류메시지에 표시된다.

Controller의 메서드에서는 매개변수로 `Request`가 아닌 우리가 정의한 `Request`를 주입시켜주면 메서드내에서 유효성검사 로직이 빠져도 검사가 수행되는 것을 볼 수 있다.