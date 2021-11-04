메서드를 오버라이딩 할때 사용했던 `@Override`와 같이 `@` 기호를 사용하는 문법 요소로 Java5부터 등장했다.

단어의 의미인 주석과는 비슷하지만 다른 역할로써 사용되는데 메서드/클래스 등에 의미를 단순히 컴파일러에게 알려주기 위한 표식이 아닌 컴파일타임 이나 런타임에 해석될 수 있다.

<br>

### ◾ 장점

기존의 자바는 `선언적 프로그래밍`방식으로 개발을 하면서 각 계층별 설정 데이터들을 XML에 명시했었는데 서비스의 규모가 클 수록 설정양이 많아지고 도메인 처리의 데이터들이 분산되어 있어 수정이 힘들었다.

어노테이션이 등장하면서 데이터 유효성 검사 등 직접 클래스에 명시해 줄 수 있게되어 수정이 필요할때 쉽게 파악할 수 있게 되었고 어토테이션의 재사용도 가능해졌다.

`AOP(관점 지향 프로그래밍)`을 쉽게 구성할 수 있게 해준다.

<br>

### ◾ 용도

크게 `문서화`, `컴파일러 체크`, `코드 분석과 자동 생성`,`런타임 프로세싱` 용도로 사용될 수 있다.
<br>컴파일 타임에 에러를 발생 시켜 경고하는 목적으로 사용될 수 있고 문서화는 컴파일 시 어노테이션이 붙은 데이터를 수집하여 가능하지만 가장 비중이 낮은 사용법이다.

유효성 검사와 같은 `메타데이터`로써 사용되고 `reflection`을 이용하여 특정 클래스를 주입할 수도 있다.


> **메타 데이터** <br><br>
> "어떤 목적을 가지고 만들어진 데이터" -Karen Coyle-
> <br>한마디로 어떤 데이터를 설명해주는 데이터


> **Reflection** <br><br>
> 반사,투영이 라는 뜻으로 객체를 통해 클래스의 정보를 분석해내는 기법<br>
> ClassName, SuperClass, Constructors, Methods, Fields, Annotations ...


<br>

### ◾ 사용 방법

```java
    @Override
    public ListNode remove(int position) {
        //생략...
    }
    //...

    @Test
    void removeTest() {
        //생략...
    }
```

사용할 클래스, 메서드, 매개변수등 앞에 붙여주기만 하면 된다.

<br>

### ◾ 분류

- Maker 어노테이션 : 멤버 변수가 없고 컴파일러에게 의미를 전달하기 위한 표식으로 사용되는 어노테이션 (ex. `@Override` )

- Single-value 어노테이션 : 멤버로 단일변수를 갖고 데이터를 전달할 수 있는 어노테이션

- Full 어노테이션 : 둘 이상의 변수를 갖는 어노테이션으로 데이터를 `키 = 값`형태로 전달한다.

<br><br>

## 빌트인 어노테이션

Java에 내장되어 있는 어노테이션으로 컴파일러를 위한 어노테이션

<br>

### ◾ Override

현재 메서드가 슈퍼 클래스의 메서드를 오버라이드한 것임을 컴파일러에게 명시해준다.

메서드가 슈퍼클래스에 없다면 에러를 발생시기 때문에 오타와 같은 실수도 잡을 수 있다.

<br>

### ◾ Deprecated

마커 어노테이션으로 다음 버전에 지원되지 않을 수도 있기 때문에 앞으로 사용하지 말라고 경고를 알린다.

![Deprecated](/java/image/deprecated.png)
`@Deprecated`를 붙인 메서드는 IntelliJ에서 사진과 같이 알림을 띄워준다.

<br>

### ◾ SuppressWarning

경고를 제거하는 어노테이션으로 개발자가 의도를 가지고 설계를 했는데 컴파일은 이를 알지 못하고 컴파일 경고를 띄울 수 있기 때문에 이를 제거하는 목적이다.

<br>

### ◾ SafeVarargs

Java 7이상에서 사용가능하고 `제네릭`같은 가변인자 매개변수 사용시 경고를 무시한다


**제네릭**<br><br>
사용할 클래스,메서드 내부에서의 데이터타입을 외부에서 지정하는 기법


<br>

### ◾ FunctionalInterface

Java 8이상에서 사용가능하고 컴파일러에게 `함수형 인터페이스`라는 것을 알리는 어노테이션이다.

**함수형 인터페이스**<br><br>
1개의 추상 메서드만을 갖고 있는 인터페이스로 10주차에 배운 Runnable이 그 예이다.

<br><br>

## 메타 어노테이션

어노테이션에 사용되는 어노테이션으로 어노테이션을 정의(설명)하기 위해 사용된다.

<br>

### ◾ @Retention

어노테이션이 유지되는 기간(`Life Time`)을 설정하는 어노테이션

```java
public enum RetentionPolicy {
    SOURCE,
    CLASS,
    RUNTIME
}
```

- SOURCE : 소스파일에만 존재하고, 클래스파일에는 존재x, 컴파일러에 의해 버려진다.

- CLASS : 클래스파일에는 존재하지만 런타임 시에 유지할 필요 없다는 것을 알리고 이 값이 default이다.

- RUNTIME : 클래스파일에도 존재하고 런타임애 VM에 의해 유지되어 리플랙션을 통해 클래스 파일의 정보를 읽어 처리 가능하다.

<br>

### ◾ @Target

어노테이션이 적용가능한 대상(`동작 대상`)을 지정한다.

만약 다른 타입이 온다면 컴파일 에러를 띄운다.

아래와 같은 ElmentType이라는 enum을 통해 지정한다.
( `@Target(ElemntType.~)와 같이 사용` )

```java

public enum ElementType {
    TYPE,
    FIELD,
    METHOD,
    PARAMETER,
    CONSTRUCTOR,
    LOCAL_VARIABLE,
    ANNOTATION_TYPE,
    PACKAGE,
    TYPE_PARAMETER,
    TYPE_USE,
    MODULE,

    @jdk.internal.PreviewFeature(feature=jdk.internal.PreviewFeature.Feature.RECORDS,essentialAPI=true)
    RECORD_COMPONENT;
}
```

- 기존

  - **TYPE** : Class, Interface(어노테이션 타입 포함), enum, jdk14에 생긴 record
  - **FIELD** : 필드 값(프로퍼티), enum 상수값
  - **METHOD** : 메서드
  - **PARAMETER** : 메서드 파라미터 (매개 변수)
  - **CONSTRUCTOR** : 생성자
  - **LOCAL_VARIABLE** : 지역 변수

  - **ANNOTATION_TYPE** : 어노테이션
  - **PACKAGE** : 자바 패키지

- jdk 1.8 이후 추가

  - **TYPE_PARAMETER** : 타입 매개 변수

  - **TYPE_USE** : 타입 사용
    //jdk 9 이후
  - **MODULE** : 모듈

- jdk 14이후 추가

  - **RECORD_COMPONENT** : Record 컴포넌트

<br>

<br>

### ◾ @documented

어노테이션의 정보가 javadoc의 문서에 포함되도록 하는 어노테이션

<br>

### ◾ @Inherited

자식 클래스에게도 어노테이션이 상속되도록 하는 어노테이션

<br>

### ◾ @Repeatable

어노테이션을 반복적으로 선언할 수 있게 하는 어노테이션

<br><br>

## 커스텀 어노테이션

![annotation](/java/image/annotation.png)

IntelliJ의 새로만들기에서 Annotation으로 지정하여 새로 만들수 있다.

```java
@Target(ElementType.FIELD)
@Retention(RetentionPolicy.RUNTIME)
public @interface CustomeAnnotation {
    String name() default "홍길동";
}
```

만들게 되면 `@interface`의 형태로 만들어지고 위의 `메타 어노테이션`을 붙여 메타 데이터를 표시할 수도 있다.

@interface 안에 매개변수가 없다면 `Maker`, 코드와 같이 한개만 존재한다면 `Single-value`, 두개이상을 갖는다면 `Full`어노테이션으로 구분할 수 있고 매개변수의 default값을 다음과 같이 지정해줄 수 도 있다.

```java
package javaStudy.CustomAnnotation;

public class AnnotationExClass {
    @CustomAnnotation
    private String defaultName;

    @CustomAnnotation(name="철수")
    private String customName;

    public AnnotationExClass() {
        this.defaultName = "이름없음";
        this.customName = "이름없음";
    }

    public String getDefaultName() {
        return defaultName;
    }

    public String getName2() {
        return customName;
    }
}
```

다음과 같이 매개변수 하나는 default로 `길동`을 하나는 `철수`를 어노테이션 값으로 갖게하고 생성자로 매개변수의 값은 `이름없음`으로 생성하는 클래스가 있다고 한다면 아래와 같이 `reflect`를 활용해서 어노테이션 값에 접근할 수 있다.

```java
    @Test
    void annotationTest() {
        AnnotationExClass annotationExClass = new AnnotationExClass();
        System.out.println("defaultName : " + annotationExClass.getDefaultName() + "\ncustomName : " + annotationExClass.getName2());


        Field[] fields = annotationExClass.getClass().getDeclaredFields();
        for(Field field : fields){
            System.out.print(field.getName() +" : ");
            Annotation[] annotations = field.getDeclaredAnnotations();
            for (Annotation annotation : annotations) {
                CustomAnnotation customAnnotation = (CustomAnnotation) annotation;
                System.out.println(customAnnotation.name());
            }
        }
    }
```

결과물을 보면 매개변수의 값은 `이름없음`이지만 각 필드에 할당된 어노테이션의 필드 값은 다른 것을 볼 수 있다.

![result](/java/image/result.PNG)

만일, 어노테이션에 `Retention`을 `RUNTIME`으로 하지 않으면 아래와 같이 런타임시에 동작하는 reflection을 이용해서 값을 불러오지 못한다.

![fail](/java/image/fail.PNG)

<br><br>

## 애노테이션 프로세서

런타임시에 리플랙션을 사용하는 어노테이션과는 달리 컴파일 타임에 이루어진다.

컴파일 타임에 어노테이션들을 프로세싱하는 javac에 속한 빌드 툴로 어노테이션의 소스코드를 분석하고 처리하기 위해 사용되는 훅이다.

보일러플레이트 코드를 제거하는데 도움이 된다.
<br>( `AbstractProcessor`를 implements하여 구현체를 만들 수 있으며 Lombok의 `@Getter`, `@Setter`와 같은 어노테이션을 이용하는 것만으로도 컴파일 타임에 알아서 getter/setter를 만들어주는 방식으로 보일러플레이트 코드 제거 )

<br><br><br>

---

### Reference

https://hiddenviewer.tistory.com/88

https://stackoverflow.com/questions/2146104/what-is-annotation-processing-in-java

http://hannesdorfmann.com/annotation-processing/annotationprocessing101/

https://medium.com/@jason_kim/annotation-processing-101-%EB%B2%88%EC%97%AD-be333c7b913
