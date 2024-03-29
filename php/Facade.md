애플리케이션의 `서비스 컨테이너`에서 사용가능한 클래스들에 `정적` 인터페이스로 라라벨은 대부분의 라라벨기능에 접근하는 많은 파사드를 제공하고 서비스 컨테이너에 등록된 클래스들에 대한 일종의 `정적 프록시` 역할을 수행하여 정적 메소드보다 간결한 문법과 테스트의 용이성, 코드의 유연성을 유지하는 장점을 제공한다.

## 동작 방식
`\Gate::denies(..)`에서 \Gate는 어디에서 왔을까?
- `\`로 시작하는 것은 글로벌 네임스페이스를 의미하는데 프로젝트의 루트 디렉토리에 있다는 것은 아니다. 라라벨은 app을 시작할 때 `class_alias` 함수를 이용해서 `config/app.php`파일에 잇는 aliases항목에 정의 되어 있는 클래스들의 별칭을 글로벌 네임스페이스에 등록한다.

즉, \Gate는 `Illuminate\Support\Facades\Gate::class`이다. 

그런데 Gate클래스에 가보면 denies()는 정의되어 있지 않는데 동작하는 것을 볼 수 있는데 이는 부모클래스인 `Facade`에 보면 `__callStatic()`이라는 static 메서드가 정의되어있다. 이 메서드는 정의되어있지 않은 static메서드가 호출되면 동작하는 `매직 메서드`로 이때문에 동작하는 것이다.

__callStatic()에서 static::getFacadeRoot()로 인스턴스를 가져오고 그 인스턴스에서 원래 실행했던 메서드를 실행하는 것이다. getFacadRoot()메서드를 다시 봐보면 `static::resolveFacadeInstance()`로 첫번째 파라미터인 `static::getFacadeAccessor()`의 인스턴스를 서비스 컨테이너로 가져온다. getFacadeAccessor()는 각 파사드 클래스에서 오버라이드하는 메서드로 `Gate`가 유일하게 가지고 있는 메서드가 바로 이 메서드이기 때문에 Gate클래스의 메서드에 의해 denies()메서드를 찾는 방식으로 동작한다.