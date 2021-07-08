php는 기본적으로 오류가 발생해도 오류를 발생시키고 다음 코드를 계속 실행하는데 라라벨은 php보다 엄격해서 오류도 예외로 바꾸어 던지고 코드 실행을 멈춘다. 이렇게 발생한 모든 예외는 `전역 예외 처리기`가 잡는데 `app/Exceptions/Handler.php`파일이 이 처리기이다.

이 처리기는 두가지 일을 수행하는데 `report(Exception $e)`메서드는 예외를 보고하는 메소드로 이메일이나 버그 추적시트멩으로 예외 내용을 잘 포장해서 보고하는 로직을 작성한다. `parent::report($e)`는 라라벨 로그에 예외를 기록하는 일을 수행한다. `render($request, Exception $e)` 메서드는 예외를 화면에 표시하는 메서드이다.

```php
//Handler.php
public function render($request, Exception $e){
    if(app()->environment('production')){
        if($e instanceof \Illuminate\Database\Eloquent\ModelNotFoundException){
            return response(view('errors.notice',[
                'title'=>'찾을 수 없습니다.',
                'description' => '죄송합니다! 요청하신 페이지가 없습니다.'
            ]), 404);
        }
    }

    return parent::render($request, $e);
}
```