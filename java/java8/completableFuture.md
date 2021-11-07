# CompletableFuture

## Java에서의 Concurrent

1. 멀티 프로세싱 ( ProcessBuilder )
1. 멀티 스레딩 ( Thread/Runnable )

### 동시성(Concurrency) vs 병렬성(Parallelism)

> 동시성? 싱글코어에서 멀티 스레드를 동작시키기 위한 방식으로 멀티 태스킹을 위해 여러개 스레드가 번갈아가면서 실행. 한마디로 동시에 실행되는 것처럼 보이는 것.
>
> 멀티스레드로 동시성을 만족시킬수 있는 거지 동시성이 멀티스레드는 아님. 코틀린의 코루틴은 싱글스레드로 동시성을 만족

> 병렬성? 2개이상의 task가 있을때 각 task가 물리적인 시간으로 동시에 실행이 가능. 멀티코어에서 멀티스레드를 동작시키는 방식으로 한개 이상의 스레드를 포함하는 각 작업들이 물리적인 시간으로 완전 동시에 수행하는 것. (이때 동시 작업은 멀티코어가 될수도 네트워크를 이용한 분산컴퓨팅이 될 수 있다.)

병렬성을 만족하면 동시성도 만족, 동시성을 만족한다고 병렬성 만족x

## 멀티 스레드

### 멀티 스레드 생성

#### 1. Thread 를 상속받아 클래스로 정의

```java
public static void main(String[] args) {
    MyThread thread = new MyThread();
    thread.start();

    System.out.println("Hello");
}

static class MyThread extends Thread {
    @Override
    public void run() {
        System.out.println("Hello");
    }
}
```

#### 2. Thread 생성자에 파리미터로 Runnalbe 인터페이스 구현하여 생성

```java
//1
public static void main(String[] args) {
        Thread thread = new Thread(new Runnable() {
            @Override
            public void run() {
            System.out.println("Hello thread");

            }
        });
        thread.start();

        System.out.println("Hello");
}

//2
public static void main(String[] args) {
        Thread thread = new Thread(() -> { System.out.println("thread hello")});
        thread.start();

        System.out.println("Hello");
}
```

<br>

### 스레드 주요 기능

- 현재 스레드 멈춰두기 (sleep) : 다른 스레드가 처리하도록 기회를 주지만 락을 걸진 않아 데드락이 걸릴 수 있다.
- 다른 스레드 깨우기 (interrupted) : 다른 스레드를 깨워서 InterruptedException을 발생 시킨다. 예외가 발생했을 때 할 일을 코딩하기 나름이다.
- 다른 스레드 기다리기 (join) : 다른 스레드가 끝날때까지 기다린다.

<br>

### 스레드의 현재 문제

- 스레드가 많아 지면 많아 질 수록 코딩으로 관리하기가 매우 힘들다 ( Interrupt, join에 대한 예외처리할 코드가 기하급수적으로 많아진다.)

<br><br>

## Executors

고수준의 Concurrency 프로그래밍

- 스레드를 만들고 관리하는 작업을 애플리케이션에서 분리하여 Executors에 위임

### 하는 일

- 스레드 만들기 : 스레드 풀을 만들어 관리

  - ExecutorService executorService = Executors.newSingleThreadExecutor() : 한개의 스레드를 갖는 ExecutorService
  - ExecutorService executorService = Executors.newFixedThreadPool(int threads) : 매개변수 숫자만큼의 스레드를 갖는 서비스 생성
  - ExecutorService executorService = Executors.newWorkStealingPool(int pallelism) : ForkJoinPool의 work stealing 기법의 멀티프로세스 풀 생성

- 스레드 관리 : 스레드 생명주기를 관리

  ```java
  public static void main(String[] args) {
      ExecutorService executorService = Executors.newSingleThreadExecutor();
      executorService.submit(() -> {
          System.out.println("Thread hello");
      });

      executorService.shutdown();
  }
  ```

  ExecutorService는 작업을 실행하고나면 다른 작업이 들어올때까지 계속 대기하고 있기 때문에 명시적으로 종료를 시켜줘야 한다.

  종료 함수에는 shutdown(),shutdownNow()가 있는데 shutdown()은 `graceful한 종료`라하며 반드시 스레드의 작업이 마치고 나서 종료를 하며 shutdownNow()는 작업현황에 상관없이 종료하는 메서드이다.

- 작업 처리 및 실행 : 스레드로 실행할 작업을 제공할 수 있는 API 제공
  - 작업 실행 : submit
  - 스케줄링 : scheduleAtFixedRate()와 같은 메서드

<br><br>

## Callable / Future

Callable은 Runnable과 거의 대부분이 일치하지만 return타입이 존재한다는 점의 차이점이 있어 이를 이용해 작업이 끝났을때의 값을 반환받을 수 있다.

### API

#### 1. 결과 가져오기 (get)

```java
public static void main(String[] args) throws ExecutionException, InterruptedException {
    ExecutorService executorService = Executors.newSingleThreadExecutor();

    Callable<String> hello = () -> {
        Thread.sleep(2000L);
        return "Hello";
    };

    Future<String> result = executorService.submit(hello);

    result.get();

    executorService.shutdown();
}
```

get()함수는 blocking call 방식이라 스레드의 작업이 아직 끝나지 않았다면 기다린 후에 리턴값을 받아오고 다음 줄을 실행하게 된다.

#### 2. 작업 상태 확인 (isDone())

작업이 끝났다면 true 반환

#### 3. 작업 취소 (cancel())

- 취소 했으면 true, 못했으면 false 반환
- 파라미터로 true를 주면 현재 진행중인 스레드를 interrupt 하고, false를 주면 작업이 끝날때까지 기다리고 취소한다.

#### 4. 여러작업 동시에 실행 (invokeAll())

```java
public static void main(String[] args) throws ExecutionException, InterruptedException {
        ExecutorService executorService = Executors.newFixedThreadPool(4);

        Callable<String> hello = () -> {
            Thread.sleep(2000L);
            return "Hello";
        };

        Callable<String> world = () -> {
            Thread.sleep(3000L);
            return "World";
        };

        Callable<String> hi = () -> {
            Thread.sleep(1000L);
            return "Hi";
        };

        List<Future<String>> result = executorService.invokeAll(List.of(hello,world,hi));

        for(Future<String> r : result){
            System.out.println(r);
        }

        executorService.shutdown();
    }
```

결과를 Future List로 받아오기 때문에 동시에 실행한 작업중 제일 오래 걸리는 작업의 시간만큼 걸리게 된다.

#### 5. 가장 먼저종료된 작업 반환받기 (invokeAny())

```java
public static void main(String[] args) throws ExecutionException, InterruptedException {
    ExecutorService executorService = Executors.newFixedThreadPool(4);

    Callable<String> hello = () -> {
        Thread.sleep(2000L);
        return "Hello";
    };

    Callable<String> world = () -> {
        Thread.sleep(3000L);
        return "World";
    };

    Callable<String> hi = () -> {
        Thread.sleep(1000L);
        return "Hi";
    };

    String result = executorService.invokeAny(List.of(hello,world,hi));

    executorService.shutdown();
}
```

가장 먼저끝난 작업의 결과물을 반환받는 메서드인데 이때 반환은 blocking call이기 때문에 Future이 아닌 일반 객체타입을 반환받는다.

<br>

### Future의 문제점

1. Future를 외부에서 취소시키거나, get()에 타임아웃을 실행하는등 완료작업을 수행할 수 없다.
1. get()이라는 blocking call을 사용하지 않고서는 작업이 끝났을때 콜백을 실행할 수 없다.
1. 여러 Future를 조립할 수 없다.
1. 예외처리용 API를 제공하지 않는다.

<br><br>

## CompletableFuture

자바에서 비동기 프로그래밍을 가능케하는 인터페이스

### API

#### 1. 비동기로 작업 실행

원하는 쓰레드 풀을 사용해서 실행할 수 있다. 기본적으로는 ForkJoinPool.commonPool()로 Executors를 사용할 수도 있다.

```java
ExecutorService executorService = Executors.newFixed(ThreadPool(4));
CompletableFuture<String> future = CompletableFuture.supplyAsync(() -> { System.out.println("Hello " + Thread.currentThread().getName());
    return "Hello";
    }, executorService).thenApply((s) -> {
        System.out.println(Thread.currentThread().getName());
        return s.toUpperCase();
    },executorService);
```

콜백함수들의 두번째 매개변수로 스레드 풀을 전달하면 해당 스레드풀을 이용하여 작업을 수행할 수 있다.

- runAsync() : 리턴값이 없는 경우

  ```java
  CompletableFuture<Void> future = CompletableFuture.runAsync(() -> { System.out.println("Hello " + Thread.currentThread().getName());
  });

  future.get();
  ```

- supplyAsync() : 리턴값이 있는 경우

  ```java
  CompletableFuture<String> future = CompletableFuture.supplyAsync(() -> { System.out.println("Hello " + Thread.currentThread().getName());
  return "Hello";
  });

  System.out.println(future.get());
  ```

#### 2. 콜백 제공

콜백 자체를 또다른 스레드에서 실행할 수 있다.

- thenApply(Function) : 리턴값을 받아서 다른 값으로 바꾸는 콜백

  ```java
  CompletableFuture<String> future = CompletableFuture.supplyAsync(() -> { System.out.println("Hello " + Thread.currentThread().getName());
  return "Hello";
  }).thenApply((s) -> {
      System.out.println(Thread.currentThread().getName());
      return s.toUpperCase();
  });

  System.out.println(future.get());
  ```

- thenAccept(Consumer) : 리턴값으로 리턴없이 다른 작업을 처리하는 콜백

  ```java
  CompletableFuture<Void> future = CompletableFuture.supplyAsync(() -> { System.out.println("Hello " + Thread.currentThread().getName());
  return "Hello";
  }).thenAccept((s) -> {
      System.out.println(s + Thread.currentThread().getName());
  });

  future.get();
  ```

- thenRun(Runnable) : 리턴값을 받지 않고 다른 작업을 처리하는 콜백

  ```java
  CompletableFuture<Void> future = CompletableFuture.supplyAsync(() -> { System.out.println("Hello " + Thread.currentThread().getName());
  return "Hello";
  }).thenRun(() -> {
      System.out.println(Thread.currentThread().getName());
  });

  future.get();
  ```

#### 3. 조합하기

- thenCompose() : 두 작업이 서로 연관관계가 있어 이어서 실행하도록 조합

  ```java
  public static void main(String[] args) throws ExecutionException, InterruptedException {
      CompletableFuture<String> hello = CompletableFuture.supplyAsync(() -> { System.out.println("Hello " + Thread.currentThread().getName());
          return "Hello";
      });

      CompletableFuture<String> future = hello.thenCompose(Example::getWorld);
      System.out.println(future.get());
  }

  private static CompletableFuture<String> getWorld(String message) {
      return CompletableFuture.supplyAsync(() -> {
          System.out.println("World " + Thread.currentThread().getName());
          return message + "World";
      });
  }
  ```

- thenCombine() : 두 작업을 독립적으로 실행하고 다 종료 했을때 콜백 실행

  ```java
   public static void main(String[] args) throws ExecutionException, InterruptedException {
      CompletableFuture<String> hello = CompletableFuture.supplyAsync(() -> { System.out.println("Hello " + Thread.currentThread().getName());
          return "Hello";
      });

      CompletableFuture<String> world = CompletableFuture.supplyAsync(() -> { System.out.println("World " + Thread.currentThread().getName());
          return "World";
      });

      CompletableFuture<String> future = hello.thenCombine(world, (helloReturn,worldReturn) -> {
          return helloReturn + " " + worldReturn;
      });

      System.out.println(future.get());
  }
  ```

- allOf() : 여러 작업을 모두 실행하고 모든 작업 결과에 콜백 실행

  ```java
  CompletableFuture<String> hello = CompletableFuture.supplyAsync(() -> { System.out.println("Hello " + Thread.currentThread().getName());
      return "Hello";
  });

  CompletableFuture<String> world = CompletableFuture.supplyAsync(() -> { System.out.println("World " + Thread.currentThread().getName());
      return "World";
  });

  List<CompletableFuture<String>> futrues = List.of(hello,world);
  CompletableFuture[] futuresArray = futures.toArray(new CompletableFuture[futures.size()]);

  CompletableFuture<List<String>> results = CompletableFuture.allOf(futuresArray).thenApply(v -> futures.stream().map(CompletableFuture::join).collect(Collectors.toList()));

  results.get().forEach(System.out.println);
  ```

- anyOf() : 여러 작업중에 가장 빨리 끝난 하나의 결과에 콜백 실행

  ```java
  CompletableFuture<String> hello = CompletableFuture.supplyAsync(() -> { System.out.println("Hello " + Thread.currentThread().getName());
      return "Hello";
  });

  CompletableFuture<String> world = CompletableFuture.supplyAsync(() -> { System.out.println("World " + Thread.currentThread().getName());
      return "World";
  });

  CompletableFuture<Void> future = CompletableFuture.anyOf(hello,world).thenAccept(System.out::println);
  ```

#### 4. 예외처리

- exceptionally(Function)

  ```java
  boolean throwError = true;

  CompletableFuture<String> hello = CompletableFuture.suuplyAsync(()-> {
      if(throwError){
          throw new IllegalArgumentException();
      }

      System.out.println("Hello " + Thread.currentThread().getName());
      return "Hello";
  }).exceptionally(ex -> {
      System.out.println(ex);
      return "Error";
  });
  ```

- handle(BiFunction)

  ```java
  boolean throwError = true;

  CompletableFuture<String> hello = CompletableFuture.suuplyAsync(()-> {
      if(throwError){
          throw new IllegalArgumentException();
      }

      System.out.println("Hello " + Thread.currentThread().getName());
      return "Hello";
  }).handle((result,ex) -> {
      if(ex != null) {
          System.out.println(ex);
          return "Error";
      }
      return result;
  });
  ```

  Error가 있을때와 정상적인 종료일때 모두 핸들링할 수 있는 메서드이다.
