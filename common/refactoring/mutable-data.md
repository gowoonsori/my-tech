# 가변 데이터
최근 함수형 프로그래밍 언어는 데이터를 변경하지 않고 복사본을 전달하는 방식으로 Mutable한 속성을 보장한다. 하지만 그 외의 언어는 데이터 변경을 허용하고 있어 변경되는 데이터를 사용할 때는 발생할 수 있는 리스크를 관리할 수 있는 방법을 적용하는 것이 좋다.

## 변수 쪼개기
어떤 변수가 여러번 재할당 되어도 되는 경우
- 반복문에서 순회하는데 사용하는 변수/인덱스
- sum과 같은 값을 축적시키는데 사용하는 변수

위와 같은 경우를 제외한 경우에 재할당 되는 변수가 있다면 해당 변수는 여러 용도로 사용되는 것이며 변수를 분리해야 더 이해하기 좋은 코드를 만들 수 있다.
- 변수 하나당 하나의 책임을 지도록 만들기
- 상수를 활용하기

```java
//AsIs
public void updateGeometry(double height, double width) {
    double temp = 2 * (height + width);
    System.out.println("Perimeter: " + temp);
    this.perimeter = temp;

    temp = height * width;              //temp라는 변수가 중복되서 사용되고 있는데 permiter인지 area인지 후에 식별이 어려워질 수 있다.
    System.out.println("Area: " + temp);
    this.area = temp;
}

//Tobe
public void updateGeometry(double height, double width) {
    double perimeter = 2 * (height + width);
    System.out.println("Perimeter: " + perimeter);
    this.perimeter = perimeter;

    double area = height * width;
    System.out.println("Area: " + area);
    this.area = area;
}
```

## 질의 함수와 변경 함수 분리하기
명령-조회 분리 규칙
- 어떤 값을 리턴하는 함수는 사이드 이팩트가 없어야 한다. (내부 값을 변경하지 않아야 하고, 다른 행동을 수행하면 안된다.)

## Setter 제거하기
Setter를 제공하는 것은 내부 상태가 변경될 수 있다는 것을 의미한다. 객체 생성시 처음 설정된 값이 변경될 필요가 없다면 해당 값을 설정할 수 있는 생성자를 만들고 Setter를 제거해서 변경될 수 있는 가능성을 제거하기.

```java
//AsIs
public class Person {
    private int id;
    private String name;

    Person(int id, String name){this.id = id, this.name = name;}

    public String getName(){return this.name;}
    public int getId(){return this.id;}
    public void setName(String name){this.name = name;}
    public void setId(int id){this.id = id;}
}

//ToBe
//만일, id는 변경되지 않는 값이라고 하면 setter는 없애기
public class Person {
    private int id;
    private String name;

    Person(int id, String name){this.id = id, this.name = name;}

    public String getName(){return this.name;}
    public int getId(){return this.id;}
    public void changeName(String name){this.name = name;}  //setter도 단순히 set~ 으로 명명하는 것보다는 보다 이해하기 쉬운 명시적인 이름으로 작명해주는 것이 바랍직하다.
}
```

## 파생 변수를 질의 함수로 바꾸기
계산해서 알아낼 수 있는 변수는 제거
- 계산 자체가 데이터의 의미를 잘 표현하는 경우가 존재
- 해당 변수가 어디선가 잘못된 값으로 수정될 수 있는 가능성을 제거할 수 있다.

계산에 필요한 데이터가 변하지 않는 값이라면, 계산의 결과에 해당하는 데이터 역시 불변 데이터이기 때문에 변수를 유지할 수 는 있다.

```java
//AsIs
public class Discount {
    private double discountedTotal;
    private double discount;
    private final double baseTotal;

    public Discount(double baseTotal) {
        this.baseTotal = baseTotal;
    }

    public double getDiscountedTotal() {
        return this.discountedTotal;
    }

    public void setDiscount(double number) {
        this.discount = number;
        this.discountedTotal = this.baseTotal = this.discount;  //discountedTotal은 baseTotal과 discount의 영향을 받는 값으로써 변수로 할당한다면 discount가 바뀔때마다 상태를 변경해주어야 한다.
    }
}

//ToBe
public class Discount {
    private double discount;
    private final double baseTotal;

    public Discount(double baseTotal) {
        this.baseTotal = baseTotal;
    }

    public double getDiscountedTotal() {
        return this.baseTotal = this.discount; 
    }

    public void setDiscount(double number) {
        this.discount = number;
    }
}
```

## 여러 함수를 변환 함수를 묶기
관련있는 파생 변수를 만들어내는 함수가 여러곳에서 만들어지고 있다면 `변환 함수`를 통해 한 곳으로 모으기

소스 데이터가 변결될 수 있는 경우에는 `여러 함수를 클래스로 묶기`를 사용