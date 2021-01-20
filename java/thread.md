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

## 병행성 (Concurrency) == 동시성

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

여러개의 쓰레드가 동작하며 병행성을 수행하기 위해 시분할을 하여 스케줄링을 통해 스레드를 동작 시키는데 이를 위해, 자바는 쓰레드 클래스에 어떤 쓰레드를 더 `중요하게` 생각하여 동작시킬지 지정하여 더 많은 `작업시간`을 갖도록 할 수 있게 해주는 `멤버 변수`를 갖고 있다.

우선순위의 범위는 `1~10`이며 숫자가 높을수록 우선순위가 높고, 메인 메서드를 수행하는 쓰레드의 우선순위가 5이므로 main메서드 내에서 생성하는 쓰레드의 우선순위는 기본값이 5가 된다.

쓰레드의 우선순위는 `상대적`인 값으로 절대적이 값이 아니다

## 메서드

```java
thread.setPriority(1~10);
thread.setPriority(Thread.MIN_PRIORITY); //1
thread.setPriority(Thread.NORM_PRIORITY); //5
thread.setPriority(Thread.MAX_PRIORITY);  //10
```

## 순환할당 (Round Robin) 방식

스케줄링 방식에는 우선순위방식 말고도 RR방식도 있는데 이 방식은 스레드마다 사용할 시간을 할당(Time slice)해서 정해진 시간만큼 돌아가며 실행하는 방식으로 `JVM`에 의해 결정되기 때문에 개발자가 임의로 수정할 수 없다.

<br><br>

# Main 쓰레드

우리가 자바프로젝트를 처음 시작했을때나 c,c++와 같이 처음 작성하는 `main()`메서드를 실행하면 시작되는 스레드로 `main메서드의 코드 흐름`이다.

main 쓰레드를 통해 다른 쓰레드를 생성하기 때문에 메인스레드가 없다면 멀티스레드는 당연히 구현할 수 없다.

## single process single thread

![single process single thread](/java/image/spst.PNG)

## single process multi thread

![single process multi thread](/java/image/spmt.PNG)

## multi process single thread

![multi process single thread](/java/image/mpst.PNG)

## multi process multi thread

![multi process multi thread](/java/image/mpmt.PNG)

<br><br>

# 동기화

멀티 스레드로 동작하는 프로그램에서 한 스레드가 작업하는 중에 사용하는 데이터들을 다른 스레드가 간섭하지 못하도록 막는 것이다.

동기화를 시키지 않는다면 여러개의 스레드가 번갈아가며 동작할 경우, 어떤 스레드가 먼저 실행될지 알 수 없기 때문에 개발자가 의도하지 않는 동작이 발생할 수 있기 때문에 멀티스레드프로그래밍에서는 중요한 문제이다.

주요 개념들

- 임계 구역 (Critical Section) : 여러개의 스레드가 공유하는 데이터 블럭으로 하나의 스레드만 접근가능하도록 지정하는 것이 목표이다.

- 상호 배제 (Mutual Exclusion,Mutex) : 임계 구역을 헌 시점에서 한개의 스레드만 사용할 수 있도록 다른 스레드의 접근을 제어하는 기법

- 동기화 : 상호배제의 한 형태로 상호배제를 수행하기 위해 프로세스의 처리 순서를 결정하는 기법 (Semaphore)

- 기아 상태 (starvation) : 다른 쓰레드에게 우선순위가 밀려 자원을 계속 할당받지 못하는 상태

- 공정성(fairness) : 모든 쓰레드가 공평하게 작업을 수행하는 것

## Synchronized 이용

임계영역을 설정하는데 사용하는 키워드로 메서드 전체를 임계영역으로 지정하거나 특정한 영역을 임계영역으로 지정하는 방법이 있다.

```java
1. 메서드 전체를 임계 영역으로 지정
  public synchronized void cal()  {
    ...
  }

2. 특정한 영역을 임계 영역으로 지정
  synchronized(객체의 참조변수)  {
    ...
  }
```

쓰레드는 synchronized가 호출된 시점부터 해당 코드블럭이 포함된 객체의 lock을 얻어 작업을 수행하다가 종료되면 lock이 반환되고 이는 모두 자동으로 이루어지기 때문에, 개발자는 임계영역만 설정 해주면된다.

객체는 lock을 하나씩 가지고 있고 설정한 객체의 lock을 가지고있는 쓰레드만 임계영역에 접근이 가능하고 다른 스레드는 대기 상태에 들어가기 때문에 임계영역은 좁히는 것이 좋다.

메서드에 synchronized를 걸면 그 메서드가 포함된 객체(this)에 lock을 거는 것과 같다.

객체 없이 호출하는 static 메서드의 경우 해당 class에 lock을 걸면서 함수간에 lock이 공유되어 동시에 호출되는 것을 막아 동기화문제가 해결된다.

## Locks

Java 5에 추가된 패키지로 `java.util.concurrent`가 있는데 이 패키지에서 동기화를 위해 다양한 클래스들을 제공한다.

> 주요 기능
>
> - Locks : 상호 배제를 사용할 수 있는 클래스
> - Synchronizers : 동기화를 처리하는 클래스 제공 (Semaphore, CountDownLatch, CyclicBarrier, Phaser, Exchanger)
> - Atomic : 동기화가 되어있는 변수 제공
> - Executors : 쓰레드 풀 생성, 쓰레드 생명주기 관리와 같은 기능 제공
> - Queue : Thread-safe한 Queue 제공

### java.util.concurrent.locks

해당 패키지에 상호 배제를 위한 Lock API들이 정이 되어있고, synchronized 도 lock을 이용한 동기화인만큼 동일한 메커니즘으로 동작한다.

내부적으로 synchronized를 사용해 구현되었고, 더욱 더 유연하고 정교하게 처리하기 위해 사용되고 직접 lock을 걸고 푸는 작업을 수행해야 한다.

- Interface

  - Lock : 공유자원에 한번에 한 쓰레드만 read/write를 수행 가능

  - ReadWriteLock : 공유 자원에 여러개의 쓰레드가 read할 수 있지만 write는 한 쓰레드만 수행 가능

  - Condition : wait()과 notify()를 쓰레드의 종류로 구분하지 않고, 공유객체의 waiting poll에 몰아 넣고 각 쓰레드를 위한 Condition을 만들어 각각의 waiting pool에서 따로 기다리도록 한다.

    wait(),notify(),notifyAll() 대신 await(),signal(),signalAll()을 사용한다.

- Interface의 구현체

  - ReentrantLock : Lock의 구현체로 임계영역의 시작,졸료 지점을 명시 할 수 있게 해준다.

  - ReentrantReadWriteLock : ReadWriteLock의 구현체
  - StampLock : JDK 1.8부터 추가되었고, 다른 lock과 달리 Lock인터페이스를 구현하지 않고 lock을 걸거나 해지할때 스탬프(long타입 정수값)를 사용한다.

- 주요 메서드
  - lock() : Lock 인스턴스에 lock을 건다.
  - lockInterruptibly() : 현제 쓰레드가 interrupted 상태가 아닐때 Lock 인스턴스에 잠금을 걸고 interrupted상태라면 Exception을 발생시킨다.
  - tryLock() : 즉시 Lock인스턴스에 잠금을 시도하고 성공여부를 boolean 타입으로 반환한다.
  - tryLock(long timeout, TimeUnit timeUnit) : 잠금 실패시 false를 반환하는 것이 아닌 주어진 시간동안 기다린다.
  - unlock() : Lock인스턴스의 잠금을 해제한다.
  - newCondition() : 현제 Lock 인스턴스와 연결된 Condition 객체를 반환한다.

## Synchronized 와 Lock의 차이점

`Synchronized`는 `암시적인(implicit) lock`이라고 하여 불공정 문제가 발생 할 수 있어 쓰레드 순서를 보장하지 않지만 `Lock`은 순서를 지정할 수 있어 `명시적인(explict) lock`이라고 한다.

`Synchronized`는 lock을 자동 획득/반환해주기 때문에 `코드가 간결하다는 장점`이 있고, `Lock`은 ReentrantLock을 이용하면 생성자 인자를 통해 공정/불공정을 설정 할 수 있어 공정한 lock을 사용할 경우 자원 할당을 위해 경쟁이 발생했을 때 오래 기다린 스레드에게 lock을 제공하여 `기아 문제를 해결`할 수 있다.

<br><br>

## volatile

멀티 코어 프로세서는 코어마다 별도의 캐시를 갖고 있는데 변수 앞에 `volatile` 키워드를 붙이면 코어가 변수의 값을 읽어올 때 캐시가 아닌 메모리에서 읽어오기 때문에 캐시와 메모리간의 불일치를 해결할 수 있다.

JVM은 데이터를 4byte 단위로 처리하기 때문에 int나 이보다 작은 타입의 데이터는 한번에 읽거나 쓰는 것이 가능하나 그보다 큰 데이터 타입이라면 하나의 명령어로 값을 읽거나 쓸 수 없다.
<br>때문에 변수의 값을 읽는 과정에서 다른 쓰레드가 끼어들 틈이 있기 때문에 변수를 읽고 쓰는 문장을 synchronized블럭으로 감싸거나 변수를 volatile을 붙여 선언하는 방법으로 캐시와 메모리간 불일치 문제를 해결 할 수 있다.

상수에는 volatile를 붙일 수 없어 변수에 final을 같이 쓸 수 없다. <br> _(상수는 변하지 않는 값이기 때문에 thread-safe하기 때문에)_

# 데드락

교착상태라고도 하며 상호 배제에 의해 나타나는 문제로, 둘 이상의 스레드가 데이터를 점유한 상태에서 서로 다른 스레드가 점유하고 있는 데이터를 요구하게되어 끝없이 기다리는 상태

데이터베이스 트랜젝션에서도 발생하는데 한 트랜잭션에서 한 레코드에 업데이트를 수행할 때, 이 레코드는 업데이트를 위해 다른 트랜잭션의 접근을 막도록 lock을 거는데 다수의 트랜젝션이 동시에 레코드를 업데이트하려한다면 데드락에 빠질 위험이 있다.

## 데드락 발생 조건(이유)

1. Mutual Exclusion(Mutex) : 자원에 동시 접근 불가능
1. Hold & Wait : 점유하고 기다리기 (자원을 점유한채로 다른 스레드의 자원을 반납받길 기다리는 것)
1. No Preemption : 자원을 강제로 뺐어오지 못함
1. Circular Wait : 순환 형태로 대기

## 데드락 해결 방법

1. 데드락 예방 : 데드락 발생 조건 4가지를 원천 봉쇄하는 방법
1. 데드락의 회피 : 자원이 어떻게 요청될지에 대한 추가정보를 제공하도록 요구하는 것으로 자원 할당상태를 검사하는 방법
1. 데드락 탐지 & 회복 : 데드락이 발생했을때 해결하는 방법
1. 데드락 무시 : 아주 적은 확률로 데드락이 발생한다면, 무시하는 방법

무시하거나 재실행하는 편이 자원적으로 더 이득을 볼 수도 있기 때문에 수행하는 방법

## 데드락 방지 방법들

1. 락 정렬 : 모든 락이 항상 같은 순서로 획득된다면 데드락은 발생하지 않기 때문에 효과적이나 락의 순서를 알고 있는 상태에서만 사용이 가능하다. (데드락 예방)

1. 락 타임 아웃 : 락을 획득하기 위해 기다리는 시간을 정해놓고 시간이 지난 후에는 락을 다시 시도하는 방법 (데드락 탐지&회복)

같은 락을 획득하려는 다른 모든 쓰레드에게 기회를 주는 것이기 때문에 공정성 문제가 발생하게되고, 데드락 뿐만이 아닌 작업을 처리중에도 타임아웃이 발생할 수 도 있다.

1. 데드락 감지 : 자료구조를 이용하여 쓰레드가 락을 획득하면 저장하고 이를 이용해 데드락을 감지하고 데드락이 발생했다면, 락을 해제하는 방법

1. Atomic Variable : volatile 키워드나 java.util.concurrent.atomic 클래스를 이용하여 원자 변수를 사용하는 방법

<br><br>

# 쓰레드 풀

쓰레드를 미리 만들어 필요할때 사용하고 반납할 수 있도록 하는 풀장의 개념

`java.util.concurrent.Executors`에서 스레드풀 관련 API를 제공한다.

## 장점

- 스레드를 생성/수거하는데 비용이 적다.
- 위의 이유로 다수의 사용자 요청을 처리할때 빠르게 대응 가능하다.

## 단점

- 사용하는 양보다 많이 생성해두면 메모리 낭비가 된다.
- 노는 스레드가 발생할 수 있다.

## 쓰레드 풀의 구조

1. Task의 요청을 받는 Queue
1. 실제 쓰레드를 생성하고 관리하는 manager
1. Queue 안에서 Task를 꺼내와 실제 쓰레드위에 동작시켜 결과를 얻는 부분

## 생성 메서드

1. Executors.newFixedThreadPool(10) : 최대 쓰레드를 10개까지 만드는 풀
1. Executors.newCachedThreadPool() : 쓰레드 수의 제한을 두지 않는 풀로 쓰레드 시작 요청이 들어올때 생성하고 종료시에 바로 죽지않고 짧은 시간(1분)동안 살아있는 방법의 풀
1. Executors.newSingleThreadExecutor() : 하나의 쓰레드를 생성하는 풀로 쓰레드 작업중에 예외상황이 발생한 경우 예외처리를 위한 쓰레드용으로 많이 사용한다.
1. Executors.newScheduledThreadPool() : 일정 주기마다 반복해야하는 스레드를 여러개 생성하기 위한 풀

[적정 스레드풀의 사이즈는 어떻게 알까?](https://yaaam.tistory.com/entry/%EC%8A%A4%EB%A0%88%EB%93%9C-%ED%92%80Thread-Pool-%EC%8A%A4%EB%A0%88%EB%93%9C-%ED%92%80%EC%9D%98-%EC%A0%81%EC%A0%95-%ED%81%AC%EA%B8%B0%EB%8A%94-%EC%8A%A4%EB%A0%88%EB%93%9C-%ED%92%80%EC%9D%98-%EC%A0%81%EC%A0%88%ED%95%9C-%EC%82%AC%EC%9D%B4%EC%A6%88%EB%8A%94)

<br><br><br>

---

## Reference

https://nesoy.github.io/articles/2018-09/OS-Concurrency-Parallelism

https://ryan-han.com/post/java/java-thread/

https://zbomoon.tistory.com/12

https://widevery.tistory.com/28

https://goscala.tistory.com/171

https://tourspace.tistory.com/54
