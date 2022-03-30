# 긴 매개변수 목록

함수에 매개변수가 많을수록 함수의 역할을 이해하기 어려워진다. 

- 어떤 매개변수를 다른 매개변수를 통해 알아낼 수 있다면, `매개변수를 질의 함수로 바꾸기`사용
- 연관된 많은 매개변수가 같이 공통적으로 넘겨진다면 `매개변수 객체 만들기` 적용
- 어떤 객체에서 데이터를 가져와 이 데이터를 여러 매개변수로 넘기고있다면 `객체를 통째로 넘기기` 적용
- 매개변수가 플래그로 사용된다면 `플래그 인수 제거하기`


## 매개변수를 질의 함수로 바꾸기
매개변수에 값을 전달하는 것은 `함수를 호출하는 쪽`의 책임.  가능하면 함수를 호출하는 쪽의 책임을 줄이고 함수 내부에서 책임을 갖도록 하는 것이 좋다.

```java
//AsIs
public double getFinalPrice() {
    double basePrice = this.quantity * this.itemPrice;
    int discountLevel = this.quantity > 100 ? 2 : 1;
    return this.discountedPrice(basePrice, discountLevel);
}

private double discountedPrice(double basePrice, int discountLevel) {
    return discountLevel == 2 ? basePrice * 0.9 : basePrice * 0.95;
}

//ToBe
public double getFinalPrice() {
    double basePrice = this.quantity * this.itemPrice;
    return this.discountedPrice(basePrice);
}

private double discountedPrice(double basePrice) {
    return discountLevel() == 2 ? basePrice * 0.9 : basePrice * 0.95;
}

private int discountLevel() {
    return this.quantity > 100 ? 2 : 1;
}
```

## 플러그 인수 제거하기
플래그를 사용하는 함수는 그렇지 않은 함수와 목적에서 그 차이를 파악하기 힘들다.

```java
//AsIs

//Shipment
public LocalDate deliveryDate(Order order, boolean isRush) {
    if(isRush) {
        int deliveryTime = switch (order.getDeliveryState()) {
            case "WA", "CA", "OR" -> 1;
            case "TX", "NY", "FL" -> 2;
            default -> 3;
        };
        return order.getPlacedOn().plusDays(deliveryTime);
    } else {
        int deliveryTime = switch (order.getDeliveryState()) {
            case "WA", "CA" -> 2;
            case "TX", "NY", "OR"  -> 3;
            default -> 4;
        };
        return order.getPlacedOn().plusDays(deliveryTime);
    }
}

//Client
LocalDate placedOn = LocalDate.of(2021,12,15);
Order orderFromWA = new Order(placedOn, "WA");

Shipment shipment = new Shipment();

shipment.deliveryDate(orderFromWA,true);
shipment.deliveryDate(orderFromWA,false);



//ToBe

//Shipment
public LocalDate rushDeliveryDate() {
    int deliveryTime = switch (order.getDeliveryState()) {
        case "WA", "CA", "OR" -> 1;
        case "TX", "NY", "FL" -> 2;
        default -> 3;
    };
    return order.getPlacedOn().plusDays(deliveryTime);
}

public LocalDate regularDeliveryDate() {
    int deliveryTime = switch (order.getDeliveryState()) {
        case "WA", "CA" -> 2;
        case "TX", "NY", "OR"  -> 3;
        default -> 4;
    };
    return order.getPlacedOn().plusDays(deliveryTime);
}

//Client
LocalDate placedOn = LocalDate.of(2021,12,15);
Order orderFromWA = new Order(placedOn, "WA");

Shipment shipment = new Shipment();

shipment.rushDeliveryDate(orderFromWA);
shipment.regularDeliveryDate(orderFromWA);
```

## 여러 함수를 클래스로 묶기
비슷한 매개변수 목록을 여러 함수에서 사용하고 있다면 메소드들을 모아서 클래스로 만들고 필요한 매개변수들을 클래스내 state로 이동함으로써 매개변수를 줄일 수 있다.