# 팩토리 메서드 패턴
## 해결하려는 문제
인스턴스를 생성하는 책임을 구체적인 클래스가 아니라 추상적인 인터페이스로 감싸 해당 인터페이스에서 생성하게끔 하여 확장에 용이하게 하기 위함

### Before
```java
public static void main(String[] args) {
        Ship whiteship = ShipFactory.orderShip("Whiteship", "keesun@mail.com");
        System.out.println(whiteship);

        Ship blackship = ShipFactory.orderShip("Blackship", "keesun@mail.com");
        System.out.println(blackship);
}

public class ShipFactory {
    public static Ship orderShip(String name, String email) {
        // validate
        if (name == null || name.isBlank()) {
            throw new IllegalArgumentException("배 이름을 지어주세요.");
        }
        if (email == null || email.isBlank()) {
            throw new IllegalArgumentException("연락처를 남겨주세요.");
        }

        prepareFor(name);

        Ship ship = new Ship();
        ship.setName(name);

        // Customizing for specific name
        if (name.equalsIgnoreCase("whiteship")) {
            ship.setLogo("\uD83D\uDEE5️");
        } else if (name.equalsIgnoreCase("blackship")) {
            ship.setLogo("⚓");
        }

        // coloring
        if (name.equalsIgnoreCase("whiteship")) {
            ship.setColor("whiteship");
        } else if (name.equalsIgnoreCase("blackship")) {
            ship.setColor("black");
        }

        // notify
        sendEmailTo(email, ship);

        return ship;
    }

    private static void prepareFor(String name) {
        System.out.println(name + " 만들 준비 중");
    }

    private static void sendEmailTo(String email, Ship ship) {
        System.out.println(ship.getName() + " 다 만들었습니다.");
    }

}
```

### After
```java
public class Client {

    public static void main(String[] args) {
        Client client = new Client();
        client.print(new WhiteshipFactory(), "whiteship", "keesun@mail.com");
        client.print(new BlackshipFactory(), "blackship", "keesun@mail.com");
    }

    private void print(ShipFactory shipFactory, String name, String email) {
        System.out.println(shipFactory.orderShip(name, email));
    }
}

```

## 적용할 수 있는 상황
1. 작업해야 하는 객체의 정확한 타입과 종속성을 아직 모르는 경우 사용가능하다.
2. 라이브러리/프레임워크 사용자에게 내부 요소를 확장하는 방법을 제공할때 사용 가능
   - 단일 팩토리 메서드로 줄이고 이를 재정의 할 수 있도록 제공하는 방법으로 적용
3. 매번 새로 생성하는 것이 아닌 기존의 객체를 재사용하여 리소스를 절약하려는 경우
    - DB connection / file system / network resource 와 같이 객체 생성에 리소르를 많이 사용하는 경우에 적용

## 장점
1. client와 객체간의 결합을 피할 수 있다.
2. SPR 
3. OCP

## 단점
1. 패턴을 구현하기 위해 새로운 하위 클래스를 계속 생성하다보면 코드가 오히려 더 복잡해질 수 있다.
