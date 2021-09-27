# socialiteproviders 이용하는 방법

socialite를 이용하여 커스텀 provider를 만들어 적용하려고 할때 그냥 적용하는 것은 복잡할 수 있는데 `socialiteproviders/manager`라는 벤더를 이용하면 커스텀적용이 쉽게 가능하다.

확실한 구조를 알고싶다면 `socialiteproviders/naver`와 같은 다른 서비스의 oauth 벤더를 다운받아 뜯어보면 되고 현재 작성하는 글도 다른 서비스의 구조를 뜯어 비슷하게 적용한 사례이다.

우선 `socialiteproviders/manager`를 설치해주면된다.

## 1. 환경 설정 해주기

```php
//config/services.php
return [

    //...

'saramin' => [
        'client_id' => env('SARAMIN_ID'),
        'client_secret' => env('SARAMIN_SECRET'),
        'redirect' => env('SARAMIN_CALLBACK'),
    ],

    //...
];

//config/app.php
'providers' => [
    //...
    \SocialiteProviders\Manager\ServiceProvider::class,
],

'aliases' => [
    //...
    'Socialite' => Laravel\Socialite\Facades\Socialite::class,
]
```

위와 같이 services.php와 app.php에 추가해주고 `.env`에 가서 services.php의 3개의 항목에 대해 정보를 기입해주어야 한다.

## 2. Provider 추가

```php
class SaraminProvider extends AbstractProvider
{

    public const IDENTIFIER = 'SARAMIN';
    private const OAUTH_URL = 'url';
    private const GATEWAY_URL = 'url';

    protected $scopes = [
        "openid",
        "scopes",
        //...
    ];

    protected $scopeSeparator = ' ';

    /**
     * {@inheritdoc}
     */
    protected function getAuthUrl($state): string
    {
        return $this->buildAuthUrlFromBase(
            self::OAUTH_URL . '/oauth/authorize',
            $state
        );
    }

    /**
     * {@inheritdoc}
     */
    protected function getTokenUrl(): string
    {
        return self::OAUTH_URL . '/oauth/token';
    }

    /**
     * {@inheritdoc}
     * @throws \GuzzleHttp\Exception\GuzzleException
     */
    protected function getUserByToken($token)
    {
        $response = $this->getHttpClient()->get(
            self::GATEWAY_URL . '/api/user/oauth/user',
            [
                'headers' => [
                    'Accept' => 'application/json',
                    'Authorization' => 'Bearer ' . $token,
                ],
            ]);
        return json_decode($response->getBody(), true);
    }

    /**
     * {@inheritdoc}
     */
    protected function mapUserToObject($user): User
    {
        return (new User())->setRaw($user)->map([
            'id' => Arr::get($user, 'sub'),
            'name' => Arr::get($user, 'name'),
            'email' => Arr::get($user, 'email'),
        ]);
    }
}
```

## 3. ProviderManager 생성

```php
class SaraminExtendSocialite
{
    public function handle(SocialiteWasCalled $socialiteWasCalled)
    {
        $socialiteWasCalled->extendSocialite('saramin', \App\Oauth\SaraminProvider::class);
    }
}

```

saramin의 socialite가 불렸을때 생성한 Provider를 실행할 수 있도록 Provider를 생성해주어야 한다.

## 4. EventServiceProvider의 listen에 ProviderManager 추가

```php
//...
protected $listen = [
        Registered::class => [
            SendEmailVerificationNotification::class,
        ],
        \SocialiteProviders\Manager\SocialiteWasCalled::class => [
            'App\Oauth\SaraminExtendSocialite@handle',
        ],
    ];
```

## 5. Controller 생성

```php
class SocialController extends Controller
{

    /**
     * Handle social login process.
     *
     * @param Request $request
     * @param string $provider
     * @return \Symfony\Component\HttpFoundation\RedirectResponse
     */
   public function execute(Request $request, string $provider){
       //인증서버로 redirect
        if (! $request->has('code')){
            return $this->redirectToProvider($provider);
        }

        //token을 가지고 있다면 token서버로 redirect
       return $this->handleProviderCallback($provider);
   }

    /**
     * Redirect the user to the Social Login Provider's authentication page.
     *
     * @param string $provider
     * @return \Symfony\Component\HttpFoundation\RedirectResponse
     * @throws BadRequestException
     */
   protected function redirectToProvider(string $provider): \Symfony\Component\HttpFoundation\RedirectResponse
   {
       switch ($provider){
           case 'saramin' :
               return Socialite::driver($provider)
                   ->redirect();
           default:
               throw new BadRequestException("잘못된 요청입니다.");
       }
   }

    /**
     * Obtain the user information from the Social Login Provider.
     *
     * @param string $provider
     * @return Application|Redirector|RedirectResponse
     * @throws UnauthorizeException
     * @throws InternalServerException
     */
   protected function handleProviderCallback(string $provider){
       $socialData = Socialite::driver($provider)->user();

      //인증 로직...

       return redirect('/success');
   }
}

```

위와 같이 Controller까지 생성해준후 web.php에 라우터만 등록을 시켜주면 적용이 된다!!

<br><br>

# Socialiteproviders가 아닌 Socialite만 이용한 방법

### 1. 설정파일과 Provider 생성

첫번째의 방법과 거의 동일하나 app.php에서 providers의 정보만 수정해주면 된다.

```php
//수정 전
\SocialiteProviders\Manager\ServiceProvider::class,

//수정 후
Laravel\Socialite\SocialiteServiceProvider::class,
```

### 2. AppServiceProvider에 사람인Provider 등록

```php
//AppserviceProvider 클래스 내부
public function boot(){
    $socialite = $this->app->make('Laravel\Socialite\Contracts\Factory');
        $socialite->extend(
            'saramin',
            function ($app) use ($socialite) {
                $config = $app['config']['services.saramin'];
                return $socialite->buildProvider(SaraminProvider::class, $config);
            }
        );
}
```

boot()메서드는 다른 서비스 프로바이더들이 등록된 이후에 호출되기 때문에 Socialite에 위와 같이 접근하여 Provider를 추가해줄 수 있다.
