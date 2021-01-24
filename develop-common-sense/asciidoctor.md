# Asciidoc

이 문서를 작성하고 있는 `Mark down`문법과 비슷하게 문서 작성을 위한 경량 마크업 언어이다.

`Spring Rest Docs`를 보다 잘 수행하기 위해 `Asciidoc`문법을 공부하고 남겨놓기 위해 작성하게 되었다.

`Mark Down`문법에 익숙해져 있기 때문에 보다 쉬운 습득을 위해 `Mark Down`과 비교하며 작성을 했다.

<br><br>

# 문법

## 제목

MD와 다르게 제목에 3가지 분류가 존재한다.

### 문서 제목

`= `으로 시작하여 문서 제목과 문서에 관련된 내용들 (저자, 날짜, 버전 등)을 표시가 가능하다.

```
= 문서제목
Doc Writer <문서 작성자>
v1.0, 2021-01-01

According to https://asciidoctor.org/ ...
```

기본 문서 타입은 `article`로 `book`일 경우에는 레벨 0의 문서 제목은 `한개`만 존재가능하다.

### 문서 속성 (:word:)

MD에는 없는 기능으로 일종의 `전역변수`와 같이 사용되는 기능이다.

```
:var: 10

variable is {var} //variable is 10으로 출력

:var!:
```

`!`을 사용해 속성을 해제도 가능하다.

```
:imagesdir:
:iconsdir:
:stylesdir:
:scriptsdir:
```

위와 같은 속성을 이용해 파일의 기본 경로값도 수정이 가능하다.

### 섹션 제목 (=)

`MD`의 `#`와 같은 기능을 수행한다.

```
= 문서 제목 level0
== level1
=== level2
==== level3
===== level4
====== level5
```

<br><br>

## 줄바꿈 (+)

Asciidoc도 MD와 마찬가지로 문단을 공백의 한 줄로 구분하기 때문에 공백이 없다면 한 문단으로 이어서 출력이 된다.

같은 문단 안에서 줄바꿈을 하고 싶을때 사용하는 것으로 `MD`의 `<br>`과 같다.

`[%hardbreaks]`를 문단앞에 사용하면 해당 문단은 `엔터(줄바꿈)`키가 그대로 인식되어 적용된다.

<br><br>

## 경고

|   구문    | 사용 목적 |
| :-------: | :-------: |
|   NOTE    |   참고    |
|    TIP    |    팁     |
| IMPORTANT |   중요    |
|  CAUTION  |   주의    |
|  WARNING  |   경고    |

<br><br>

## 글자 강조 (Text formating)

|  구문  |  사용 목적  |
| :----: | :---------: |
| \`(\`) | 인라인 코드 |
| \*(\*) |    강조     |
| \_(\_) |   Italic    |

MarkDown에서는 인라인 코드는 **\`word\`** , 강조는 **\*\*word \*\***, Italic은 **\*word \*** 이나 **\_word \_**으로 특수기호의 개수에 따라 기능이 달라졌지만 `Asciidoc`은 개수는 상관없이 `종류`에따라 기능이 구분된다.

<br><br>

## 블럭

### 코드 블럭

MD 의 **\`\`\` code \`\`\`**와 같은 기능을 수행하는 것으로 Asciidoc에서는 **\-\-\-\- code \-\-\-\-** 와 같이 사용하면 된다.

`[source]`블럭을 사용해서 코드를 강조할 수도 있다.

````
MardDown

    ```js
    console.log("Hello")
    ```
Asciidoc

    [source,javascript,linenums]
    ----
    console.log("Hello")
    ----

    [source,java]
    ----
    include::helloworld.java[]
    ----
````

`linenums`옵션을 통해 줄 번호도 표시가 가능하고 외부 소스코드 `include`가 가능하다

### 인용문 (인용 블럭)

MD의 `>`와 같은 기능으로 **\_\_ 인용 문 \_\_**와 같이 사용할 수 있다.

<br><br>

## 표 (Table)

MD보다는 표는 조금더 간편하게 작성이 가능한 것 같다.

`|===`으로 표의 시작과 끝 블럭을 표시하고 각 컬럼은 `|`을 이용한다.

```
[%header,cols=2*,]
|===
|col1 |col2 |col3

|data1
|date2
|data3

|===


[%header,cols="3,4,5"]
|===
|col1 |col2 |col3

|data1
|date2
|data3

|===
```

위와 같이 `header`옵션으로 헤더를 표현할 수 있고 `col`옵션으로 col 너비를 조정이 가능하다.

```
[%header,format=csv]
|===
data1, data2, data3
data4, data5, data6
|===

[%header,format=csv]
|===
include::example.csv[]
|===
```

또한, csv에서 표를 만들어낼 수도 있고 외부 csv파일을 읽어서 표현도 가능하다.

Asciidoc의 Markdown과 다른 가장 큰 장점이 이 `include`인 것 같다.

<br><br>

## 순서없는 리스트

`*` 이나 MD와 같이 `-`을 사용하여 표시하지만 다른 점은 `리스트 깊이`를 표시할 때 `MD`는 `TAB`으로 구분하였다면 `Aciidoc`은 특수기호를 여러번 작성해주면 된다.

```asciidoc
- 1
-- 2
--- 3
---- 4
----- 5
```

중첩은 5개까지 표현이 가능하다.

### 리스트의 제목 표현

MD에는 없는 기능인데 list의 위에 `.`을 사용하면 리스트에 제목을 작성이 가능하고 `.title`과 같이 `.`이후에 공백이 없어야한다.

```
.title
- list1
- list2
```

<br><br>

## 순서있는 리스트

`MD`는 `1. `으로 통일해도 알아서 순서가 자동 증가가 되지만 `Asciidoc`은 순서를 맞게 입력해 주어야 하고 자동증가를 하고 싶다면 `. `으로 시작하면 자동 증가가 된다.

```
1. list1
2. list2

. list1
. list2

4. list4
5. list5

[start=4]
. list4
. list5

[%reversed]
. list2
. list1
```

`start`나 `reversed`를 통해 시작 번호를 설정하거나 역순으로 작성도 가능하다.

```
[arabic]
. 1     // 1.
. 2     // 2.

[loweralpha]
. 1     // a.
. 2     // b.

[lowerroman]
. 1     // i.
. 2     // ii.

[upperalpha]
. 1     // A.
. 2     // B.

[upperroman]
. 1     // I.
. 2     // II.
```

위와 같이 기본은 `arabic`으로 숫자가 표시되며 추가 속성을 지정하여 `알파벳`이나 `로마자`로 표현이 가능하다.

<br><br>

## 이름있는 리스트

MD에는 없는 기능으로 `::`을 이용하면 리스트 구분을 `이름`으로 대신 사용이 가능하다.

`:: `이후에 오는 구문은 `설명문`으로 리스트 오른쪽에 오는 것이 아닌 다음 줄에 위치하게 된다.

`horizontal` option으로 다음 줄이 아닌 `오른쪽`에 위치하게 할 수도 있다.

```
list1:: This is list1
list2:: This is list2

[horizontal]
list1:: This is list1
list2:: This is list2
```

<br><br>

## 목록내에서의 여러 문단 작성

MD에서는 리스트에서 여러 문단을 표시하기 위해서는 `enter`로 구분하고 `들여쓰기`를 한단계 더 깊게 하거나 <br>로 구분하였는 데 `Asciidoc

```
[MD]

- list1 : 첫번째 문장<br>두번째 문장

    새로운 문단 시작

[Asciidoc]

- list1 : 첫번째 문장
+
새로운 문단
+
--
오픈 블럭 시작 구간으로  (-- --)안의 구간은 문단간에 공백을 두면 자동으로 공백이 생성
--

```

<br><br>

## 링크

URL은 `MD`와 같이 자동으로 인식이 되고 이를 막고자 하면 URL앞에 `\`을 붙여 주면된다.

```
:hide-uri-scheme:
https://gowoonsori.site
```

`:hide-uri-scheme:`옵션을 주면 `https://` 와 같은 스키마는 제거되고 보여진다.

특정 단어에 URL을 걸때는 `MD`는 `[word](url)`을 사용했지만 `Asciidoc`은 `link:url[word]`를 사용한다.

```
[블로그](https://gowoonsori.site)  //md

link:https://gowoonsori.site[블로그]  //asciidoc
```

<br><br>

## 이미지

```
![이미지 제목](link)   //md

[link=url]
image::이미지 이름[이미지제목] //asciidoc


[#img-id]
.이미지 제목
[link=이미지 링크]
image::이미지 이름.jpg[이미지 제목,width,height]
```

MD와는 다르게 Asciidoc은 link가 아니라 파일의 경로로 이미지를 첨부하고자 한다면 `:imagesdir:`을 이용해야 한다.

asciidoc의 이미지 파일 기본 경로가 해당 폴더로 되어 있기 때문에 `:imagesdir:`을 이용해 기본 경로를 바꿔주어야 다른 폴더의 이미지에 접근이 가능하다.

또는 이미지 이름을 파일경로와 같이 표현을 하면된다.

```
:imagesdir: ../java/image
image::array1.PNG[array]

or

image::../java/image/array1.PNG[]
```

<br><br>

## include

MD에 비해 월등히 좋은 기능으로 외부 파일을 가져와 보여줄 수 있는 키워드로 외부 문서나 소스코드를 첨부가 가능하다.

```
include::git.md[]

[source,java]
----
include::hello.java[]
----

include::../java/jvm.md[]  ////상대경로 이용한 외부파일 include
```

<br><br><br>

---

### Reference

https://asciidoctor.org/docs/asciidoc-writers-guide/

https://docs.asciidoctor.org/asciidoctor/latest/syntax-highlighting/highlightjs/
