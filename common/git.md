# Git

Git은 [홈페이지](https://git-scm.com/)에 따르면 소규모 프로젝트부터 대규모 프로젝트까지 모든 것을 빠르고 효율적으로 처리하도록 설계된 `무료 오픈 소스` `분산 버전 제어 시스템`이라고 설명되어 있다.

## Github, GitLab, bitbucket

대표적인 Git저장소로 Git을 사용하는 프로젝트를 지원하는 웹호스팅 서비스이다.

<br><br>

# Git 명령어

## 설정/초기화

- config

  - 사용자명 구성 : git config (--global) user.name "name"
  - 이메일 설정 : git config (--global) user.email "email"
  - 설정 정보 조회 : git config (--global) --list
  - 터미널에 표시되는 메시지에 칼라를 표시해줌 : git config --global color.ui “auto”
  - alias 등록 : git config --global alias.`별칭` '!적용할 명령어'
- remote

  - 원격 저장소 추가 : git remote add <remote 별칭> <저장소 url>

    - 원격 저장소 변경 : git remote set-url <remote 별칭> <저장소 url>

    - 원격 저장소 별칭 내역 확인 : git remote -v
    - 원격 저장소 별칭 제거 : git remote rm 원격저장소 별칭

## 기본 명령어

- 새로운 파일 추가 : git add <파일명들이나 '.'>
- commit
  - add한 파일에 대해 commit 메시지 추가 : git commit -m "메시지"
  - 모든 변경된 파일에 대해 commit 메시지 추가 : git commit -am "메시지"
  - 마지막 커밋 고치기 : git commit -m "메시지" --amend
- push : 로컬 저장소에 commit된 파일을 원격저장소에 반영하기
  git push <remote 별칭> <`branch`> 
- pull : 원격저장소에서 로컬 저장소로 가져오기
  git pull <remote 별칭> <`branch`>

  pull은 fetch와 merge가 합쳐진 명령어

- fetch : 원격 저장소에서 합치지 않고 로컬저장소로 가져오기
  git fetch <remote 별칭>
- merge : 다른 branch를 현재 checkout된 브랜치에 merge하는 명령
  git merge <`branch`>

  - merge시 충돌일어났을 때 merge전으로 되돌리기 : git merge --abort

- stash : 하던 작업을 임시로 저장 해두는 명령어
  - git statsh list : stash 목록 확인
  - git stash apply [stash이름] --index : 작업을 다시 가져오기
  - git stash drop [stash이름] : 스택에서 stash 제거 
  - git stash pop : apply + drop 형태
  - git stash show -p | git apply -R : stash 적용한 것을 복구

## 브랜치

- branch : branch를 다루는 명령어

  - branch 생성 : git branch <branch 명>
  - branch 삭제 : git branch -D <branch 명>
  - 로컬 저장소의 branch 조회 : git branch
  - 원격 저장소 branch 조회 : git branch -r
  - 로컬,원격 모두 조회 : git branch -a
  - 새로운 브랜치로 덮어쓰기 : git branch -f <기존 branch> <새로운 branch>

- checkout : branch를 이동하는 명령어

  - branch 이동 : git checkout <branch 명>
    - 원격 저장소의 branch로 checkout하면 소스코드들을 조회하고 변경할 수 있지만, commit/push 할 수 없고 다른 branch로 checkout시에 branch는 로컬에서 사라진다.
  - branch 만들면서 이동 : git checkout -b <branch 명>
  - 특정 branch로부터 새로운 브랜치 생성 : git checkout -b <새로운 branch 명> <특정 branch>

  - 브랜치명 변경 : git checkout -m <기존 브랜치> <새로운 브랜치>

  - 원격 저장소의 특정 branch를 로컬에 가져오기 : git checkout -t <remote별칭/branch명>

    에러가 발생한다면 `git remote update`를 통해 원격 저장소를 최신상태로 갱신

## git 상태 보기

- log

  - 모든 log보기 : git log
  - 패치와 함께 log 표시 : git log -p
  - 특정 개수의 항목만 log 보기 : git log -숫자
  - 특정 시간동안의 log 보기 : git log --since "6 hours"
  - 특정 날짜전까지의 log 보기 : git log --before "2 days"
  - 커밋 내용을 한줄로 압축하여 표시 : git log --oneline

- diff

  - 현재 작업 트리와 인덱스 차이점 보기 : git diff
  - 인덱스와 저장소 차이점 보기 : git diff --cached
  - 작업트리와 저장소 차이점 보기 : git diff HEAD

- status

  - 작업 트리 상태 표시 : git stauts
  - 짧은 형식으로 표시 : git status -s
  - 추적되지 않은 파일도 표시 : git status -u

- reset
  - git add 이후에 변경 내역 되돌리기 : git reset HEAD <file>
  - 특정 commit이후의 모든 내역을 삭제하고 되돌아가기 : git reset --hard <commit 값>

<br><br>

# 좋은 git commit 메시지 작성

- 동명사보다 의미를 잘표현하는 명사를 사용

- 관사 사용 X (a,an,the)
- 부정문 `Don't` 사용

## 좋은 commit 을 위한 영어 단어 목록

- Fix : 수정
  - 오타 수정 : Fix typo
  - A를 수정 : Fix A
  - B의 A를 수정 : Fix A in B
  - B를 위해 A를 수정 : Fix A to B
  - A를 수정해서 B가 된다 : Fix A so that B
  - B처럼 발생하는 A를 수정 : Fix A where B
  - B일때 발생하는 A를 수정 : Fix A when B
- Set : 변수 값을 변경등 작은 수정
- Refactor : 전면 수정
- Improve : 호환성,성능,접근성 등 향상이 있을 때
- Simplify : 코드 단순화
- Update : 잘못된것 수정이 아닌 수정,추가, 보완
  - A를 B로 업데이트 : Update A to B
- Revise : 문서의 개정이 있을 때

- Add : 새롭게 추가하거나 만든 것
  - B를 위해 A를 추가 : Add A for B
  - B에 A를 추가 : Add A to B
- Implement : Add에 비해 더 큰 단위의 코드에 사용 ( 하나의 기능 )
- Make : 기존 동작의 변경
  - A를 B하게 만듬 : Make A B
- Remove : 삭제
  - B에서 A를 삭제 : Remove A from B
- Use : 사용
  - B에 A를 사용 : Use A for B
  - B가 되도록 A를 사용 : Use A to B
  - B에서 A를 사용 : Use A in B
- Correct : 문법의 오류나 타입 변경,이름 변경
- Ensure : 확실히 보장받도록 함
- Prevent : 특정한 처리를 못하게 막음
- Avoid : 특정한 처리를 회피하게 함
- Move : 코드의 이동
- Rename : 이름 변경
- Verify : 특정 기능을 검증
- Pass : 파라미터 넘기는 처리에 사용
  - A를 B로 넘김 : Pass A to B

<br><br><br>

---

## Reference

https://blog.ull.im/engineering/2019/03/10/logs-on-git.html
https://git-scm.com/docs
