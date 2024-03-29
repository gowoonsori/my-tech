# 엔디안
데이터를 저장하면 메모리에 저장이 되는데 이때 그냥 저장하는 것이 아닌 데이터(바이트)를 어떻게 저장하냐에 따라 크게 두가지로 나뉘어 저장이 된다.

> 엔디안? 배열형식으로 되어있는 메모리블럭에 데이터를 배열하는 방법

## 빅 엔디안

MSB(Most Significant Byte) 부터 메모리 앞의 주소에 저장하는 방식

![bigEndian](/common/image/bigEndian.PNG)

예를 들어 `0x12FF34`라는 데이터가 있을 때 데이터가 메모리에 앞에서부터 12 / FF / 34 순서대로 저장되는 방식이다.

보통 메모리는 1블럭에 1byte를 갖고 16진수는 1자리수에 4bit를 필요로 하기 때문에 메모리의 1블럭에 숫자 2개씩 들어가게 되고 Big Endian은 데이터 앞에서부터 메모리의 앞의 자리에 삽입되는 방식이다.

주로 네트워크의 `ip주소`같은 곳에 쓰이고 있다.

빅엔디안은 사람이 읽고쓰기 편하게 앞에서부터 저장이 되기 때문에 디버깅도 쉬울수 있다는 장점이 존재하지만 32bit 빅엔디안의 환경에서 0x12의 12의 데이터bit를 사용하려고 할때 0x12는 `00 00 00 12`으로 표시되고 이를 꺼내쓰기 위해서는 앞의 3byte를 날리는 등의 작업이 필요로 하다.

또한 가산기와 같이 하위 숫자부터 더해 올림을 해주어야하는 등의 작업은 오히려 불편해진다.

네트워크 통신은 빅엔디언 방식을 사용하기 때문에 ip주소가 192.168.0.1이라면 그대로 앞에서부터 192(c0), 168(a8), 0(00), 1(01)로 읽고 쓰면 되고 데이터 전송을 할때는 꼭 빅엔디안에 맞춰 전송을 해야한다.

대표적인 빅엔디안으로 `JVM`도 있다. JVM은 다른 아키텍쳐와다르게 `레지스터`기반이 아닌 `JVM 스택`기반으로 동작하는데 플랫폼간의 독립성을 유지하기 위함과 네트워크 전송 시 유리한 빅엔디안 방식을 사용한다.

<br><br>

## 리틀 엔디안

LSB(Least Significant Byte) 부터 메모리 앞의 주소에 저장하는 방식

![littleEndian](/common/image/littleEndian.PNG)

똑같이 `0x12FF34`라는 데이터가 있을 때 이번에는 반대로 뒤의 숫자부터 메모리의 앞에 저장되는 방식이고 주로 `인텔, AMD`의 아키텍쳐가 리틀 엔디안으로 동작한다.

사람이 보기 불편할 수 도 있지만, 32bit의 0x12를 표현할때 `12 00 00 00`순으로 저장이 되기 때문에 메모리 앞에서 바로 꺼내사용할 수 있고, 수치계산시에 하위 숫자(메모리의 상위에 위치한 데이터)부터 계산하기 때문에 올림을 계산하기 수월하다는 장점이 있다.

하지만, 숫자의 비교에 있어서는 빅엔디안보다는 느릴 수 있다.

<br><Br>

## 바이 엔디안 (Bi Endian)

ARM과 같은 아키텍쳐는 제조사가 설계할때 둘 중 선택할 수 있게 설계되었다.

예를 들어 ARM아키텍쳐를 이용해 제조하는 `퀄컴`은 둘 중 선택하여 제조를 하고 `설명서`에 어떤 엔디안을 사용했는지 명시한다.

<br>

## 미들 엔디안

한가지만 선택하여 설계한 것이 아닌 2바이트 단위는 빅엔디안, 2바이트 안의 1바이트는 리틀 엔디안으로 설계하는 것과 같이 한번에 두개를 동시에 사용하는 방식이다.

---

## Reference

https://duzi077.tistory.com/201

https://d2.naver.com/helloworld/1230
