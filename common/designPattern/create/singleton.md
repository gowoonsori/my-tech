## 목적
1. 인스턴스를 오직 한개만 만들기 위함
2. 한개만 만든 객체에 대해 글로벌하게 접근이 가능해야함


## 구현 방법

- Eager Initialization (사전 초기화) : 클래스 로딩시에 인스턴스를 생성하는 방법 ( 클래스 내부에서 인스턴스를 생성)

  인스턴스를 실제로 사용하지 않는다몀 불필요한 연산과 메모리 낭비

    ```java
    public class Settings{
        private static final Settings INSTANCE = new Settings();

        private Settings(){}

        public static Settings getInstance() {
            return INSTANCE;
        }
    }
    ```
  

- Lazy Initialization (지연 초기화) : 인스턴스를 실제로 사용할 시점에서 인스턴스를 생성하는 방법으로 인스턴스를 실제로 사용하지 않는다면 메모리와 연산량을 아낄 수 있으나 이중 객체 생성 문제 발생할 가능성이 높다.

    ```java
    public class Settings{
        private static Settings instance;

        private Settings(){}

        public static Settings getInstance() {
            if(instance == null){
                instance = new Settings();
            }
            return instance;
        }
    }
    ```

    여러개의 스레드가 getInstance를 거의 동시에 접근하여 객체를 얻는 상황이 발생한다고 한다면, instance가 null 인지 검사하는 부분에서 조건이 걸리지 않아 여러개의 객체를 생성하는 문제가 발생할 수 있다. 이를 해결하기 위해서는 동시에 접근을 하지못하도록 lock을 걸어야 하기 때문에 synchronized 키워드를 사용하면 확정으로 한개만 생성할 수 있다.  

    ```java
    public class Settings{
        private static Settings instance;

        private Settings(){}

        public static synchronized Settings getInstance() {
            if(instance == null){
                instance = new Settings();
            }
            return instance;
        }
    }
    ```
    하지만 lock을 걸고 회수하는 것도 모두 자원을 소비하는 것이기 때문에 성능상 불이익이 있을 수 있다.

    - 최적화 
        - Double Check Locking : 스레드를 학부생때 배운내용으로 동기화 과정에서 lock의 범위는 최소한으로 하는 것이 좋다고 배웠었다. lock의 범위가 넓어질 수록 락이 걸릴 필요가 없는 경우도 포함되어 스레드가 대기하는 부분이 많아지고 그만큼 비용이 들기 때문이다.
  
            ```java
            public class Settings{
                private static volatile Settings instance;

                private Settings(){}

                public static Settings getInstance() {
                    if(instance == null){
                        synchronized ( Settings.class ){
                            if(instance == null){
                                instance = new Settings();
                            }
                        }
                    }
                    return instance;
                }
            }
            ```
            
            위처럼 instance가 생성되었는지를 두번 체크함으로써 lock의 범위를 줄여 필요없는 동기화 과정을 줄일 수 있다.


        - static inner 클래스 : static inner 클래스를 활용하면 위의 double check locking처럼 getInstance가 호출되는 타이밍에 inner cl
  
            ```java
                public class Settings{
                private static Settings instance;

                private Settings(){}

                private static class SettingsHolder {
                    private static final Settings INSTANCE = new Settings();
                }

                public static synchronized Settings getInstance() {
                    return SettingsHolder.INSTANCE;
                }
            }
            ```