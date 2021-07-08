컨트롤러가 이벤트를 등록하면 이 엡트에 관심이 있는 클래스가 자신이 해야할 일을 실행하는 기술로 이때 컨트롤러는 자신이 발생시킨 이벤트를 누가 어떻게 사용하는지 알지 못한다. (느슨한 결합)

## 장점
1. 컨트롤러 코드 간결
1. 이벤트 처리 로직을 유연하게 확작하거나 축소할 수 있다.
1. 사용자에게 빠른 UI응답을 제공한다. (무겁고 시간이 오래 걸리는 일은 이벤트로 던져 다른 클래스에서 처리)

<br><br>

## Controller
```php
class ArticlesController extends Controller{
    public function store(\App\Http\Requests\ArticlesRequest $request){
        $article = \App\User::find(1)->articles()->create($request->all());
        if(!$article){
            return back()->with('flash_message','글이 저장되지 않았습니다.')->withInput();
        }

        var_dump('이벤트를 발생');
        event('article.created', [$article]);
        var_dump('이벤트 발생 완료');

        return redirect(route('articles.index'))->with('flash_message','작성하신 글이 저장되었습니다.');
    }
}
```
`event()`메서드를 이용해서 이벤트를 fire할 수 있고 이때 메서드의 첫번째 인자로 `이벤트 이름`을 두번째로 `이벤트 데이터`를 정의해주면 된다.

## 이벤트 수신
### 1. 라우터 이용
```php
Event::listen('article.created', function ($aticle){
    var_dump($article->toArray());
});
```

<br>

### 2. 이벤트 레지스트리
```php
class EventServiceProvider extends ServiceProvider{
    protected $listen = [
        Registered::class => [
            SendEmailVerificationNotification::class,
        ],
    ];

    public function boot()
    {
        parent::boot();

        \Event::listen('article.created',function ($article){
            var_dump($article->toArray());
        });
    }
}
```
라우팅 정의 파일에 모든 이벤트 처리 로직을 담게 되면 가독성이 떨어지고 무거워지기 때문에 이벤트도 전용으로 처리하는 클래스가 존재하는데 바로 `app/Providers/EventServiceProvider.php`이다. 수신할 이벤트와 처리 로직을 boot()메서드에 작성하면 된다. 

메서드 내에서 Event파사드를 이용해서 로직을 정의하면 된다.

<br><br>

### 3. 이벤트 리스너 클래스


```php
class ArticlesEventListener
{
    public function __construct()
    {
        //
    }

    public function handle(\App\Models\Article $article)
    {
        var_dump($article->toArray());
    }
}

//EventServiceProvider
public function boot()
    {
        parent::boot();

        \Event::listen('article.created',function ($article){
            \App\Listeners\ArticlesEventListener::class
        });
    }
```
라우트 정의 파일에서 콜백함수를 컨트롤러로 옮겼듯이 이벤트 처리로직도 별도의 리스너로 분리할 수 있는데 `php artisan make:listener ArticlesEventListener`로 생성하면 App/Events/ 밑에 리스너가 생성이되고 Provider도 리스너 파사드를 호출하면 handle()메서드가 동작하여 이벤트를 동작한다.

<br>

#### 이벤트 클래스
```php
class ArticleCreated
{
    use Dispatchable, InteractsWithSockets, SerializesModels;

    public $article;

    public function __construct(\App\Modles\Article $article)
    {
        $this->article = $article;
    }

    public function broadcastOn()
    {
        return new PrivateChannel('channel-name');
    }
}

//Controller
public function store(\App\Http\Requests\ArticlesRequest $request){
    event(new \App\Events\ArticleCreated($article));
}

//Provider
public function boot{
    parent::boot();
    \Event::listen(
        \App\Evetns\ArticleCreated::class,
        \App\Listeners\ArticlesEventListener::class
    );
}

//Listener
class ArticlesEventListener
{
    public function handle(\App\Events\ArticlesEvent $event)
    {
        var_dump($event->article->toArray());
    }
}
```
이 이벤트 클래스는 전달할 데이터를 담고있으며 일종의 DTO이다. DTO이기 때문에 다른 클래스가 이 프로퍼티에 접근할 수 있도록 public으로 선언해주면 된다. 컨트롤러에서 이 선언한 Event인스턴스를 생성하여 event()메서드로 던져주고 이벤트 레지스트리(Provider)에 새로만든 이벤트 채널을 등록해주면 된다.

listen()메서드의 첫번째 인자로 지정한 이벤트가 발생하면, 두번째 인자의 클래스(listener)에게 이벤트 처리를 위임하는 형태이다. 이때, Listener의 handle()메서드의 인자는 Event채널로 바꿔주어야 하고 event객체내부에 모델이 들어있는 것이기 때문에 한번더 체이닝을 거쳐 접근을 해주어야 한다.

#### +번외)
`tail -f storage/logs/laravel.log`명령어로 라라벨 로그를 쉽게 확인할 수 있다.

<br><br>

## 라라벨 내장 이벤트 채널
이벤트를 꼭 `컨트롤러`에서만 던져야 하는 것은 아니고 어디서든 던질 수 있으며, 라라벨 프레임워크에서도 이벤트를 fire하는데 `사용자 인증`,`캐시`,`콘솔`,`db`,`메일` 등의 기능에서 던지고 있다.

### 마이그레이션/모델
```php
class CreateAuthorsTable extends Migration
{
    public function up()
    {
        Schema::create('users', function (Blueprint $table) {
            $table->timestamp('last_login')->nullable();
        });
    }

    public function down()
    {
        Schema::dropIfExists('users');
    }
}
```
엘로퀀트 모델은 시각과 관련된 프로퍼티를 `카본(Carbon\Carbon)`인스턴스로 반환하여  `App\Models\User::find(1)->created_at->diffForHumans();`와 같이 사용하면 현재 시간으로부터 몇시간 전인지와 같은 시간 계산에 필요한 편리한 API를 제공한다. 이 외에도 [Carbon 문서](https://github.com/briannesbitt/Carbon)에서 많은 api를 확인 할 수 있다.