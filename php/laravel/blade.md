## Blade
라라벨의 템플릿 언어인 동시에 html 컴파일 엔진으로 php스크립트로 컴파일 한 후 다시 html로 컴파일하게 된다. 이때 확장자는 `.blade.php`이며 `resources/views`의 하위에 존재해야 한다.

<br><br>

## 변수를 이용한 문자열 보간
```php
<p>{{$gretting or "hello" }}</p>
```
`<?= isset($gretting) ? "{gretting} : 'Hello';>`와 같은 문법으로 이중 중괄호`{{}}`를 통해 문자열 보간이 가능하고 블레이드는 기본적으로 xss공격으로부터 보호하기 위해 특수문자를 이스케이프하는데 이스케이프를 하지 않고자 하면 `{!! $var !!}`문법을 이용하면 된다.


<br><br>

## 주석
html의 주석 형식인 `<!-- 주석 -->`도 이용 가능하고 블레이드 주석 형식인 `{{--주석--}}` 형식도 이용이 가능하다. 차이점은 html형식은 응답되는 html까지 남아있는 반면 블레이드 주석 형식은 php로 컴파일되는 타이밍에 사라져 응답되는 html에는 남아 있지 않는다.

<br><br>

## 제어 구조
```php
@if($itemCount = count($items))
    <p>{{$itemCount}} 종류의 과일이 있습니다. </p>
@else
    <p>없습니다.</p>
@endif
```
블레이드는 `@`을 이용하여 모든 제어구조를 정의한다.

`@unless(조건식)` : @if(!조건식) 과 같은 문법이다.

<br><br>

## 반복문
### @foreach
```php
<ul>
    @foreach($items as $item)
        <li>{{$item}}</li>
    @endforeach
</ul>
```
php같이 @foreach를 이용하여 간단하게 나타낼 수 있고 for, while도 이용가능하다.

<br>

### @forelse
```php
<ul>
    @forelse($items as $item)
        <li>{{$item}}</li>
    @empty
        <li>없습니다. </li>
    @endforelse
</ul>
```
php에는 없는 `forelse`로 `@if`와 `@foreach`의 결합이다. view에서 넘어온 값이 있으면 @forelse를 실행하고 없으면 @empty를 실행한다.

<br><br>

## 템플릿 상속
각 부분부분을 컴포넌트화 하여 중복을 제거하기 위한 방법

### @yield
```php
<!doctype html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <title> 예제 </title>
</head>
<body>
    @yield('content')
</body>
</html>
```
yield는 나를 상속받는 자식이 가진 content라고 이름 붙인 섹션의 내용을 여기에 출력하겠다는 의미

<br>

### @extends와 @section
```php
@exends('layout.master')

@section('content')
    <p>hi</P>
@endsection
```
자식 템플릿은 @extends를 이용하여 부모템플릿을 상속받을 수 있고 @section부분으로 컨텐트를 정의할 수 있다. `@endsection`대신에 `@stop`을 사용할 수도 있다.

<br>

### @include
@extends키워드가 없는 순수 html조각을 `조각 뷰`라고 하고 이 조각 뷰에서도 블레이드의 기능을 모두 사용할 수 있다.
해당 조각 뷰를 다른 템플릿에서 가져다 사용하려면 `@include()`를 이용해 사용할 수 있다.

<br>

## 상속시 문제점
계층구조로 section을 상속하다보면 section이름이 중복되는 경우가 존재한다. 이때 가장 먼저 드는 해결방법이 이름을 조금수정해 여러개의 section을 만드는 방법이지만 이는 구조도 지저분해지고 section이 많아져 관리가 힘들어질 수 있다.

<br>

```php
@section('script')
    @parent
    <script>
        alert("footer");
    </script>
@endsection
```

`@parent`키워드로 이 문제를 해결 할 수 있는데, 원래 중복되는 이름의 경우 제일 depth가 깊은 section만 수행이 되는 반면에 @parent를 사용하면 아래 구문을 실행하기전 중복된 부모section을 먼저 수행한다.


```php
@section('script')
    <script>
        alert("footer");
    </script>
    @parent
@endsection
```
이는 footer먼저 수행하고 부모section을 수행한다.