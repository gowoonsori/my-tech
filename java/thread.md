# Thread란?

쓰레드라는 개념을 이해하기 위해서는 `프로세스`와 `병행성(Concurrency)`의 개념을 알면 더 좋을 것같다.

## 프로세스

프로세스의 사전적 의미는 컴퓨터에서 실행되고 있는 컴퓨터 프로그램을 말한다. 여러 개의 프로세서를 사용하는 것을 `멀티 프로세싱`이라고 하며, 같은 시간에 여러 개의 프로그램을 띄우는 시분할 방식을 멀티태스킹 이라고 한다.

### 특징

- 프로그램이 실행되는 단위
- 모든 프로그램은 실행 될 때 하나 이상의 프로세스를 갖는다.
- 각 프로세스는 다른 프로세스의 변수나 자료 구조에 접근할 수 없다.
- 각 프로세스는 별도의 주소공간에서 실행된다.
- 컴퓨터 메모리에 적재되어 실행되어 있는 프로그램을 말한다.
- 프로세스의 상태는 생성, 실행, 준비, 대기, 종료가 있다.

## 병행성 (Concurrency)

`병렬성`과 헷갈릴 수 있는데 병행성은 `동시에 실행되는 것 처럼 보이는 것`으로 싱글코어에서는 `시분할기법`으로 수행할 수 있고 멀티코어에서는 물리적으로 병렬로 동작할 수 있다.

`병렬성(Parallelism)`은 `실제로 동시에 작업이 처리되는 것`으로 멀티코에에서만 동작이 가능하다.

## 쓰레드

프로세스의 특정한 수행 경로로 프로세스가 할당 받은 자원을 이용하는 실행의 단위라고 할 수 있다.

하나의 프로세스에서 여러개의 스레드를 사용하는 것을 `멀티 스레딩`이라고 한다.

### 특징

- 프로세스 내에서 스택/레지스터만 각각 할당 받고 나머지 메모리 영역은 공유한다.
  스택은 각각 할당하는 이유 : 스레드는 한 기능을 수행하는 독립적인 단위로써 최소한의 메모리 영역(스택)은 각각 할당해야 독립적으로 수행이 가능하다.

<br><br>

# Thread 클래스와 Runnable 인터페이스

자바에서 쓰레드를 작성하는 방법에는 `Thread 클래스`와 `Runnable 인터페이스`를 사용하는 두가지 방법이 있다.

## Thread 클래스 extends

```java
public class Example {
  public static void main(String[] args){
    ExampleThread th1 = new ExampleThread();
    Thread th2 = new Thread(){
      @Override
      public void run(){
        System.out.println("thread2");
      }
    }

    th1.start();
    th2.start();
  }

  class ExampleThread extends Threads{
    @Override
    public void run(){
      System.out.println("Thread 1");
    }
  }
}
```

Thread 클래스를 확장하여 생성하는 방법으로는 thread클래스를 상속받아 생성하는 방법인 `th1`과 `th2`와 같이 익명 객체를 사용하여 생성하는 방법 2가지 가 존재하고 두번째방법인 `익명 클래스`를 이용하는 방법은 쓰레드가 오직 한번만 수행 될때 사용하는 방법이다.

## Runnable 인터페이스 implements

```java
public class Example {
  public static void main(String[] args){
    Runnable r = new ExampleThread();
    Thread th1 = new Thread(r);
    //Thread th1 = new Thread(new ExampleThread());

    Thread th2 = new Thread(()->{
      System.out.println("thread2");
    });

    th1.start();
    th2.start();
  }

  class ExampleThread implements Runnalbe{}
    @Override
    public void run(){
      System.out.println("Thread 1");
    }
  }
}
```

Runnable 인터페이스를 이용한 Thread생성방법도 두가지가 존재한다.

1. Runnalbe 인터페이스를 implements한 class를 생성자 매개변수로 이용하여 생성하는 방법
2. Runnable 인터페이스는 run메서드밖에 존재하지 않는 점을 이용하여 `람다`를 이용해 바로 run메서드를 정의하여 생성하는 방법

## 차이점

1. Thread 클래스를 extends하는 방법은 class를 상속받는 것인 만큼 Thread의 다른 메서드들을 이용이 가능하지만 다른 class를 상속받지 못하지만, Runnable 인터페이스를 구현하는 것은 다른 class를 상속받을 수 있고 조금 더 `객체 지향적`이다.

2. Thread클래스를 상속받는 class는 run 메서드가 종료되면 가비지 컬렉션이 되기 때문에 재사용이 불가능하지만, Runnable 인터페이스를 구현한 방법은 Thread 클래스는 가비지 컬랙션이 되더라도 구현체는 가비지 컬랙션이 되지 않기 때문에 재사용이 가능하다.

3. Runnable 인터페이스를 구현한 경우 Thread클래스의 메서드를 이용하고 싶다면 Thread 클래스의 static 메서드인 currentThread()를 호출하여 쓰레드의 참조를 얻어야 사용이 가능하다.

```java
class ThreadA extends Thread  {
public void run() {
  System.out.println(getName());
}

class ThreadB implements Runnable {
  public void run() {
    System.out.println(Thread.currentThread().getName());
  }
}
```

<br><br>

# 쓰레드의 상태

|   상태    |   열거 상수   |                                  설명                                  |
| :-------: | :-----------: | :--------------------------------------------------------------------: |
| 객체 생성 |      NEW      |                스레드 객체 생성 (start()메서드 호출 전)                |
| 실행 대기 |   RUNNABLE    |              스케줄링 되지 않아 실행을 기다리고 있는 상태              |
| 일시정지  |    WAITING    |                  다른 스레드의 notify를 기다리는 상태                  |
| 일시정지  | TIMED_WAITING |                     주어진 시간 동안 기다리는 상태                     |
| 일시정지  |    BLOCKED    | 사용하고자 하는 객체의 락이 풀릴 때 까지 기다리는 상태 ( 동기화 문제 ) |
|   종료    |  TERMINATED   |                            실행을 마친 상태                            |

## Start와 run

start()는 NEW상태의 스레드를 RUNNABLE상태로 만들어주는 메서드로 실행될 수 있는 대기 큐에 넣어주는 역할(call stack 생성)

run()은 스레드가 스케줄러에 의해 실제로 실행될때 실행할 메서드이고 start()없이 run만 실행하게 된다면 override된 메서드를 그대로 호출할 뿐 해당 Thread는 RUNNABLE상태가 아니기 때문에 `메타데이터`가 `실행대기 큐`에 들어있지 않아 원하는 대로 동작하지 않는다.

## 쓰레드 상태 제어 메서드

![쓰레드 상태 메서드](/java/image/thread_method.PNG)
[사진 출처](https://widevery.tistory.com/28)

### Thread 클래스에 정의

|             메서드              |                                                                                                                        설명                                                                                                                         |
| :-----------------------------: | :-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------: |
|           interrupt()           |                                                                                 일시정지상태의 스레드에서 Interrupt 예외를 발생시켜 작업을 멈추라고 요청하는 메서드                                                                                 |
|          interrupted()          |                                                                                             interrupt()가 호출되었는지 알려주는 메서드 (되었다면 true)                                                                                              |
| join((long millis),(int nanos)) |                                               동작중인 작업을 멈추고 다른 스레드가 지정 시간동안 작업 수행하도록 넘겨주는 메서드로 시간을 지정하지 않으면 다른 스레드가 작업을 마칠때 까지 기다린다.                                                |
| sleep(long millis, (int nonos)) | 일정 시간동안 스레드를 멈추게 하는 메서드로 `일시정지`상태로 만들고 `interrupt()`가 호출되면 `실행 대기`상태로 만든다.<br>sleep은 `항상 실행중인 스레드`에 대해 작동하기 때문에 static으로 선언되어 있어 `Thread.sleep(1000)`과 같이 사용해야 한다. |
|             yield()             |                                                                                            스레드 자신에게 주어진 시간을 다음 스레드에게 양보하는 메서드                                                                                            |

### Object 클래스에 정의

특정 객체에 대한 것이므로 위의 메서드롸 다르게 Object클래스에 정의되어 있어 모든 객체에서 호출이 가능하고 `동기화 블록`내에서만 사용할 수 있다.
|메서드 | 설명|
|:---:|:---:|
|notify()| 일시정지 상태의 스레드중 다른 스레드를 깨우는 메서드로 RUNNABLE상태로 만든다.|
|notifyAll()| `waiting pool`안에 있는 모든 스레드를 깨우는 메서드로 깨어난 스레드들은 다시 경쟁을 통해 실행된다.<br>호출된 객체의 waiting pool내의 스레드들을 모두 깨우는 것|
|wait()| notify()나 notifyAll()을 기다리는 메서드 |
|wait(long timeout,(int nanos))| 지정된 시간동안만 기다리는 메서드|

<br><br>

# 쓰레드의 우선순위

<br><br>

# Main 쓰레드

<br><br>

# 동기화

한 스레드가 작업하는 중에 사용하는 데이터들을 다른 스레드가 간섭하지 못하도록 막는 것이다.

<br><br>

# 데드락

<br><br>

# 쓰레드 풀

쓰레드를 미리 만들어 필요할때 사용하고 반납할 수 있도록 하는 풀장의 개념

## 장점

- 스레드를 생성/수거하는데 비용이 적다.
- 위의 이유로 다수의 사용자 요청을 처리할때 빠르게 대응 가능하다.

## 단점

- 사용하는 양보다 많이 생성해두면 메모리 낭비가 된다.
- 노는 스레드가 발생할 수 있다.

[적정 스레드풀의 사이즈는 어떻게 알까?](https://yaaam.tistory.com/entry/%EC%8A%A4%EB%A0%88%EB%93%9C-%ED%92%80Thread-Pool-%EC%8A%A4%EB%A0%88%EB%93%9C-%ED%92%80%EC%9D%98-%EC%A0%81%EC%A0%95-%ED%81%AC%EA%B8%B0%EB%8A%94-%EC%8A%A4%EB%A0%88%EB%93%9C-%ED%92%80%EC%9D%98-%EC%A0%81%EC%A0%88%ED%95%9C-%EC%82%AC%EC%9D%B4%EC%A6%88%EB%8A%94)

<br><br><br>

---

## Reference

https://nesoy.github.io/articles/2018-09/OS-Concurrency-Parallelism

https://ryan-han.com/post/java/java-thread/

https://zbomoon.tistory.com/12

https://widevery.tistory.com/28

https://goscala.tistory.com/171
