# 오류 검출과 오류 정정

## 오류 검출
데이터 전송 과정중 데이터 손실이나 오류가 생겼는지 검사하는 것

<br><br>

### 오류 검출 방법

<br>

#### 패리티 비트

---

`후진 오류 수정(BEC)방법`중에 하나로 `송신측`에 `재전송 요청`을 통해 수정하는 방법

데이터 비트에 `패리티 비트`라는 검사를 위한 비트 1개를 추가하여 오류가 있는지 검사하기 위한 비트

<br>

- 종류
  - 짝수 패리티
    <br>전체 비트에서 1의 개수가 짝수가 되도록 패리티 비트를 추가 하는 것
    <br>(1의 개수가 홀수라면 1을 추가, 짝수라면 0을 추가)
  - 홀수 패리티
    <br>전체 비트에서 1의 개수가 홀수가 되도록 패리티 비트를 추가 하는 것
    <br>(1의 개수가 짝수라면 1을 추가, 홀수라면 0을 추가)

<br>

`빅엔디안`방식이라면 앞에 `리틀 엔디안`방식이라면 데이터 비트 처음에 추가하게 된다.

예를 들어 `리틀엔디안` 방식으로 `1111111`의 비트셋을 갖는 데이터를 전송한다면, **짝수 패리티**는 `11111111`, **홀수 패리티**는 `11111110`을 전송하게 된다.

수신측은 이 데이터를 받고 패리티 비트 값과 데이터의 1의 개수를 비교하여 값에 오류가있는지 없는지 검사하는 방법이다.

`패리티 비트`는 대게 아주 먼 거리 통신시 사용하고있고, 근거리
통신시에는 `체크섬`을 이용한다.

<br><br>

#### 체크섬 ( Check Sum ) = 검사합

---

`후진 오류 수정(BEC)방법`중에 하나로 `송신측`에 `재전송 요청`을 통해 수정하는 방법

`중복 검사`의 한가지 형태로 통신중에 데이터의 에러를 검출하는 방법중 하나이다.
<br>어렸을때 수학시간에 배웠던 검산하는 방법과 같은 원리이다.

<br>

- 방법

  1. 송신자는 전송할 모든 데이터를 `16비트` 단위로 구분하고 이 값을 모두 더한다.<br>
     더하는 과정에서 `캐리값`이 발생하면 이는 버리지 않고 값에 더해준다.
  1. 더한 값을 `1의 보수`를 취해준다.
  1. 위의 결과로 나온 값을 `체크섬`이라하며, 이를 데이터와 같이 전송해준다.

  - 수신자는 받은 데이터를 `1,2의 과정`을 통해 나온 값과 데이터와 같이 전송 받은 `체크섬`값을 확인하여 전달받은 데이터에 오류가 있는 지 검사하게 된다.

<br>

`CRC(순환 중복 검사)`와 같다고 오해할 수 도 있지만, CRC는 나눗셈을(가환환의 나눗셈 (XOR))에 기반해 얻어지는 값이기에 엄밀히 말하면 다르다고 할 수 있다.

<br><br>

#### 순환 중복 검사 (CRC)

#### 블록합 (Block Sum)

<br><br>

## 오류 정정

오류를 감지하고 원본 데이터를 다시 복원하는 것.

<br><br>

### 오류 정정 방법

<br>

#### 반복을 통한 정정

---

같은 값을 여러번 보내어 각 자리수마다 가장 많이 전송받은 값을 원본데이터라고 통계적으로 추측할 수 있다는 점을 이용한 방법.

<br>

- 문제점
  1. 누군가가 의도적으로 오류를 발생시킬시 잘못된 데이터를 인식할 수 있다.
  1. 데이터의 양이 커지면 비용이 많이 커지게 된다.

<br><br>

#### 리더던시 (Redundancy)

---

데이터의 신뢰도를 높이기 위해 `잉여 정보`를 보내는 방법.
<br>이때, `잉여 정보`를 `리더던시`라 한다.

<br>

- 방법
  - 송수신측은 데이터와 맵핑시킬 `코드 워드`들을 `미리 약속`한다.
  - 이 약속에 따라 데이터를 `변환`하여 전송한다.
  - 데이터를 수신후 오류가 발생했다고 한다면, 해석 할 수 없는 코드를 약속에 근거해 `가장 근접`한 코드로 `해석`한다.

<br><br>

#### 해밍 코드

---

`전진오류수정(FEC)`방법중 하나로 수신 측에서 수정하는 방법.

데이터 전송/메모리 액세스 등 경우에 `최대 2비트 오류를 감지`하거나 `1비트 오류를 수정`할 수 있는 방법

`패리티 비트`를 여러개 끼워넣어 오류를 검출/정정 하는 방법

이때도 패리티 비트는 짝수 or 홀수 패리티 비트를 이용할 수 있다. 이는 송수신자가 서로 약속하에 사용을 하면된다.

<br>

- 방법

  1. 2^p >= P + M +1 을 만족하는 p를 찾는다.
     <br>이때 p는 패리티 비트의 개수, m은 데이터의 비트 개수이다.

  1. 데이터의 비트 단위 중 2의 거듭제곱에 위치한 모든 비트를 패리티 비트로 사용한다.

  1. 각 패리티 비트는 각자 할당된 공간의 데이터를 검사후 짝수/홀수 패리티 비트 규칙에 맞게 체크 비트를 설정한다.

  1. 1,2,3에 의해 생성된 데이터+체크 비트를 전송 후 수신자는 다시 검사해보며, 오류가 있는지 검출 하고 오류가 난 자리를 확인하여 수정한다.

  ( 패리티 비트가 검사하는 공간의 데이터 규칙과, 자세한 설명은 여기를 [참고](https://m.blog.naver.com/ggggamang/221113176831)하자)

<br><br>

#### 상승 코드

---

`전진오류수정(FEC)`방법중 하나로 수신 측에서 수정하는 방법.

<br><br>

#### 정지 후 대기(Stop and Wait)

---

`후진 오류 수정(BEC)방법`중에 하나로 `송신측`에 `재전송 요청`을 통해 수정하는 방법

<br><br>

#### GBN ( Go Back N )

---

`후진 오류 수정(BEC)방법`중에 하나로 `송신측`에 `재전송 요청`을 통해 수정하는 방법

<br><br>

#### 선택적 반복 (Selective Repeat)

---

`후진 오류 수정(BEC)방법`중에 하나로 `송신측`에 `재전송 요청`을 통해 수정하는 방법