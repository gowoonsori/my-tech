# 기본 명령어

### ◾ rm

파일이나 디렉토리를 삭제

- i : 삭제할지 확인 메시지
- f : 확인하지 않고 바로 삭제 (-f를 명시하지 않아도 default)
- r : 하위에있는 파일,디렉토리들 모두 삭제

<br>

### ◾ cp

파일이나 디렉토리 복사

- r : 디렉토리 복사

<br>

### ◾ mv

파일을 이동하는 명령어인데 이동하면서 이름을 재설정할 수 있어 rename할때도 사용

<br>

### ◾ mkdir

디렉토리 생성

- p : 지정한 부모디렉토리가 존재하지 않아도 부모디렉토리까지 생성

<br>

### ◾ 파일 출력

- cat : 파일의 내용 모두 출력
- head : 위의 10행만 출력
- tail : 아래의 10행만 출력

  - 숫자 : head와 tail옵션으로 숫자를 지정하면 10행이 아닌 지정한 행의 내용을 출력

- more/less : 페이지 단위로 출력

  - spacebar : 다음페이지
  - B : 맨 앞페이지
  - Q : 종료
  - 화살표, pageup, pagedown : less부터 가능

<br><br>

## 사용자 관리

사용자 정보는 /etc/passwd 를 열어보면확인이 가능하고 각 행의 의미는 다음과 같다.

`사용자이름 : 암호 : 사용자ID : 그룹ID : 추가정보 : 홈디렉토리 : 기본 셸`

암호가 x로 표시되어있는 것은 /etc/shadow에 비밀번호가 저장되어있다는 의미이고 이 파일을 열어보아도 암호는 해쉬화 되어있어서 알 수 없다.

<br>

### ◾ adduser

새로운 사용자를 추가해주는 명령어

```sh
adduser user1

adduser --home /home/myDir user1  #홈 디렉토리 지정
adduser --shell /bin/zsh user1    #기본 셸 지정
```

<br>

### ◾ passwd

사용자의 비밀번호 변경

```sh
passwd user1
```

<br>

### ◾ usermod

사용자의 속성 변경

```sh
usermod --home /home/myDir user1  #홈 디렉토리 지정
usermod --shell /bin/zsh user1    #기본 셸 지정
```

<br>

### ◾ userdel

사용자 삭제

```sh
userdel user1
userdel -r userdel  #홈 디렉토리까지 삭제
```

<br>

### ◾ change

사용자의 암호를 주기적으로 변경하도록 설정

```sh
change -E 2023/12/01 user1  #만료일 지정
change -M 30 user1          #최대 30일까지 사용가능
```

<br><br>

## 파일/디렉토리 소유와 허가

### ◾ chmod

파일의 읽기쓰기실행권한을 own/group/other에 다르게 부여

<br>

### ◾ chown

파일의 소유자를 지정

<br>

### ◾ chgrp

파일의 소유그룹을 지정

<br>

### ◾ 링크

링크에는 `하드 링크`와 `심볼릭 링크` 두개가 존재하는데 하드링크는 원본 파일과 같은 `아이노드`를 사용하게 되고 심볼릭링크는 새로운 아이노드를 생성해 이 아이노드는 원본파일을 가리키는 포인터가 저장되어있어 원본파일을 가리키는 링크를 생성하게된다.

```sh
touch baselink
ln baselink hardlink    #하드링크 생성
ln -s baselink softlink #심볼릭링크 생성
ls -il                  #아이노드번호와 파일정보 출력
```

하드링크는 원본파일의 데이터블럭을 그대로 사용하기 때문에 크기가 동일하고 심볼릭링크는 원본 파일 포인터를 가지고있기 때문에 크기가 작다.

하드링크는 디렉토리내에 원본파일이 사라져도 이상이 없지만, 심볼릭링크는 디렉토리내에 원본파일이 사라지면 링크가 끊기게 된다.

> 아이노드
>
> 리눅스의 파일시스템에서 사용하는 자료구조로 파일의 소유권, 허가, 종류, 실제 대이터의 위치 등의 정보가 들어있고 모든파일이나 디렉토리는 각자 1개씩의 아이노드가 존재한다.

<br><br>

## 패키지 관리

### ◾ dpkg

apt-get이전의 패키지관리자

<br>

### ◾ apt-get

dpkg를 확장한 패키지관리자

`/etc/apt` 에 설정파일들이 존재하고 `source.list`파일에 패키지 파일을 검색하는 네트워크 주소가 들어있다.

<br><br>

## 파일 압축

### ◾ xz

```sh
xz 파일이름         ## 파일이름.xz로 압축
xz -d 파일이름.xz   ## 파일 압축 해제
xz -l 파일이름.xy   ## 압축 진행상황 출력
xz -k 파일이름.xy   ## 압축 후 기존 파일 삭제 x

```

<br>

### ◾ bzip | gzip | zip/unzip

<br><br>

## 파일 묶기

여러개의 파일을 한개의 파일로 묶는 명령어로 프로그램을 통해서 우리가 윈도우에서 압축하는 것은 사실은 먼저 파일을 하나로 묶은 후 압축하는 것이다.

리눅스에서는 이를 따로 관리하며, 편의성을위해 한번에 할 수 있는 옵션도 존재는 한다.

<br>

### ◾ tar

tar확장자로 묶고 푸는 명령어

- c : 새로운 묶음 생성
- x : 묶인 파일을 품
- t : 풀기전에 묶인 경로를 보여준다.
- C : 지정된 디렉토리에 압축을 푼다.
- f(필수) : 묶음 파일 이름 지정
- v : 파일이 묶이거나 풀리는 과정을 보여준다.
- J : tar + xz
- z : tar + gzip
- j : tar + bzip2

```sh
tar cvf my.tar 디렉토리     #묶기
tar cvfJ my.tar 디렉토리    #묶기 + xz압축
tar cvfz my.tar 디렉토리    #묶기 + gzip압축
tar cvfj my.tar 디렉토리    #묶기 + bzip2압축

tar tvf my.tar             #파일 확인

tar xvf my.tar               #파일 풀기
tar Cxvf /home/ubuntu my.tar #지정 경로에 풀기
tar xfJ my.tar               #xz압축해제 + tar풀기
```

<br><br>

## 파일 검색

### ◾ find

find `경로` `옵션` `조건` `action`

- name : 이름
- user : 소유자
- perm : 허가권
- size: 크기
- exec : 후의 다른 명령어 실행

```sh
find /etc -name "*.conf"    #/etc밑에 .conf인 확장자 검색
find ~ -perm 777            # 홈 디렉토리에 777허가권 파일 검색

find ~ -size 10k -exec ls -l {} \;  # 홈디렉토리에 파일 크기가 10인 파일을 상세히 출력
```

-exec앞의 명령줄이 {}안에 들어가게 되어 실행된다.

<br>

### ◾ which

절대 경로를 포함한 path에 설정된 디렉토리에서만 검색한다.

<br><br><br>

---

### Reference

이것이 우분투 리눅스다 - 우재남
