# 컴파일러

특정 프로그래밍 언어를 다른 언어로 바꿔주는 일종의 번역기 역할 (주로, 고차원의 원시 코드를 기계어로 번역하는데 사용한다.)

<br>

## 좋은 프로그래밍언어의 조건
1. 언어의 개념이 명확 (Syntax : 문법 구조, semantics : 의미 )

1. 개발자의 생각을 자연스럽게 표현 가능
1. 호환성, 신뢰성, 모듈화, 효율성
1. 확장성

<br>

## cross-compiler
소스코드를 실제로 작성하고 실행한 기계 A가 아닌 다른 기계 B를 목표로하는 코드를 생성하는 컴파일러

## Interpreter
원시코드를 전체 분석하는 컴파일러와 달리 소스코드 한줄한줄을 바로 바로 실행하는 것

## Preprocessor
해석하자면 전처리기로 입력 데인터를 처리해 다른 프로그램의 입력으로 사용되는 출력을 만들어내는 프로그램.

여기서 전처리된 데이터를 `Translator`가 받아 목표로 하는 언어로 변경하게 된다.

<br><br>

## 컴파일러 구조
- Front End : `language`에 독립적인 부분
    1. Lexical Analyzer : 어휘 분석기로 프로그래밍 언어를 컴파일러 내부에서 처리하기 쉬운 정수로 바꾸어주는 기능을 한다. `Scanner`역할

        ex. `>`/`(`와 같은 특수기호들을 `7`,`25`와 같이 미리 정의된 숫자로 바꾸는 역할로 이를 통해 `성능향상`을 꾀할 수 있다.

    2. Syntax Analyzer : 구문 분석기로 각 문장이 구문에 적합한지 분석하는 장치로 프로그램 구조를 `Tree`형태로 출력하고 문법이 틀리다면 `에러`를 출력한다.

        일종의 `Parser`역할

    3. Intermediate Code Generator : 위의 결과물인 트리형태 데이터를 이용해 `유니코드`를 생성

        여기서 `의미(Sementic)`체킹을 수행하고 `유니코드` 즉, 바이트코드로 변환을 해준다.

<br>

- Back End : `meachine` 에 의존적인 부분

    4. Code Optimizer : 코드 최적화해주는 장치로 비효율적인 코드를 효율적인 코드로 바꾸어준다.

        - Meaning Optimization : 의미 최적화 

            - major part : 실행 시간 증가
            - minor part : 코드 크기 감소
        - Criteria for optimization(최적화 기준)

            - 프로그램 의미 보존
            - 평균 속도 향상
        - Local Optimization

            - Constant folding : 상수 전파
            - Eliminating redundant load, store instructions : 중복 제거, 효율적인 저장 방법
            - Algebraic simplification : 대수적(큰 숫자) 간소화
            - Strength reduction : 강도 감소로 비용이 덜 드는 작업으로 대체
        - Global Optimization

            - Common subexpression : 공통 하위 표현식 제거 (동일한 표현식 있는지 검사후 이를 사용)
            - Moving loop invariants : 프로그램의 의미에 영향을 주지 않으면서 루프 본문 밖으로 이동할 수 있는 명령문을 수행
            - Removing unreachable codes : 사용하지 않은 코드(메모리) 제거 (ex. JS나 JAVA의 참조하지 않는 객체는 GC가 제거하는 것)
    5. Target Code Generator : 중간 코드를 이용해 기계 코드로 생성하는 장치

        - 임무 
         
            1. 레지스터 관리
            1. storage 할당
            1. 코드 최적화 (기계에 종속적인 최적화)
            1. instruction(명령) 생성
    
    6. 추가) Error Recovery 
        - Error Handling 
            1. Error repair : error가 발생하면 복구 해주는 것
            2. Error detection : error 감지
            3. Error recovery :  error가 다른 문장에 영향을 미치지 않도록 수적하는 것
            4. Error reporting 
        - Error 종류
            1. Syntax Error
            1. Semantic Error
            1. Run-time Error 

<br><br>

## 컴파일러 자동화 도구
기술이 발전할수록 언어와 기계는 다양해지는데 그때마다 컴파일러를 만들려면 NxM개의 컴파일러가 필요하기 때문에 컴파일러를 자동으로 만들어주는 `Compiler-compiler`가 필요하다.

### LEX 
1975년 M.E.Lesk가 고안

입력 스트림에서 정규표현으로 기술된 토큰들을 찾아내는 도구로 `프로그램을 작성하는데 유용`한 도구이다.

### Parser Generator(PGS)

1. Stanford PGS

    파스칼 언어로 작성됐고 구문 구조를 `AST(Abstract Syntax Tree)`형태로 얻고 이를 포함한 파싱 테이블을 출력한다.

1. Wisconsin PGS
    파스칼 언어로 작성됐고 error Recovery 기능이 있다.

1. YACC(Yet Another Compiler Compiler)
    C언어로 작성됐고 UNIX에서 수행한다.

### Automatic Code Generation
- 3가지 목표

    1. Machine Description : ISP, ISPS, HDL ...
    1. Intermediate language 
    1. Code Generating algorithm (CGA)

        - 패턴 일치 코드 생성
        - Table driven 코드 생성