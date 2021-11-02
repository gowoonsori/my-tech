# Date/Time

## 새로 추가 된 이유
### 1. java.util.Date 클래스는 mutable하여 thread safe 하지 않다.
```java
Date date = new Date();
long time = date.getTime();
System.out.println(date); //Tue Nov 02 17:34:03 KST 2021

Thread.sleep();
Date date2 = new Date();
System.out.println(date2); //Tue Nov 02 17:34:06 KST 2021
date2.setTime(time); 
System.out.println(date2); //Tue Nov 02 17:34:03 KST 2021
```
Date객체를 보면 setTime()과 같은 메서드로 내부값을 변경할 수 있는 mutable하여 멀티스레드 환경에 적합하지 않다.

2. 클래스 이름이 명확하지 않다. (Date인데 시간까지 다룬다.)
Date 라는 클래스인데 getTime()과 같이 시간까지 다룬다.

3. 타입 안정성이 없고 월이 0부터 시작하거나 등등 버그 발생의 여지가 많다.
```java
Date date = new Date(-10000,1,1,1,1);
System.out.println(date); //Thu Feb 01 01:01:00 KST 8101

//Date
 public Date(int year, int month, int date, int hrs, int min) {
        this(year, month, date, hrs, min, 0);
}
```
타입을 int로 받기 때문에 숫자면 모두 다 받을 수 있고 그에 따라 이상한 값이 올 수가 있다.

<br>

## 특징
### 기존 API
- java.util.Date
- java.util.Calendar
- java.text.SimpleDateFormat

### 추가된 API
- java.time.Instant : 기계시간
- java.time.LocalDate : 날짜(시간x), 타임존x
- java.time.LocalTime : 시간(날짜x), 타임존x
- java.time.LocalDateTime : 날짜/시간, 타임존x
- java.time.ZonedDateTime : 날짜/시간, 타임존o
- java.time.DateTimeFormatter 
- java.time.Duration
- java.time.Period
- java.time.TemporalAdjuster

<br>

## 사용 예

### 1. Instant
```java
Instant instant = Instant.now();
System.out.println(instant); //2021-11-02T14:07:19.218304100Z  (기준시 UTC 기준)

ZonedDateTime zonedDateTime = instant.atZone(ZoneId.systemDefault());
System.out.println(instant); //2021-11-02T23:08:45.188601700+09:00[Asia/Seoul]  (현재 KTC 기준)
```
### 2. LocalDate/LocalTime/LocalDateTime/ZonedDateTime
```java
LocalDateTime now = LocalDateTime.now();    //서버의 시스템 zone 기준
System.out.println(now);

LocalDateTime of = LocalDateTime.of(1982, Month.JULU, 15,0,0,0);

ZonedDateTime nowInKorea = ZonedDateTime.now(ZoneId.of("Asia/Seoul"));
System.out.println(nowInKorea); 
```
### 3. DateTimeFormatter
```java
//formatting
LocalDateTime now = LocalDateTime.now();
DateTimeFormatter formatter = DateTimeFormatter.ISO_DATE_TIME;
System.out.println(now.format(formatter));      //2021-11-02T23:28:51.388655
formatter = DateTimeFormatter.ofPattern("MM.dd.yyyy");
System.out.println(now.format(formatter));      //11.02.2021

//parsing
LocalDate parse = LocalDate.parse("08.12.2021",formatter);
System.out.println(parse);
```
DateTimeFormatter은 ofPattern()을 이용해 특정 패턴을 지정할 수 있고 미리 정의된 포맷터들이 존재하는데 이 형식을 이용하고자하면 굳이 새로 정의해줄 필요가 없다. 정의된 포맷터들은 [여기](https://docs.oracle.com/javase/8/docs/api/java/time/format/DateTimeFormatter.html)를 참고

또 Date/Time타입의 parse()메서드를 통해서 특정 문자열을 Date/Time 타입으로 파싱할 수 있다.

### 4. Duration / Period
```java
//Period
LocalDate today = LocalDate.now();
LocalDate thisYearBirthDay = LocalDate.of(2022, Month.FEBRUARY,7);

Period period = Period.between(today, thisYearBirthDay);
System.out.println("생일까지 남은 기간 : " + period.getYears() + " 년 " + period.getMonths() + "월 " + period.getDays() + "일" );  //생일까지 남은 기간 : 0 년 3월 5일

Period p = today.until(thisYearBirthDay);
System.out.println("생일까지 남은 기간 : " + p.getYears() + " 년 " + p.getMonths() + "월 " + p.getDays() + "일" );  //생일까지 남은 기간 : 0 년 3월 5일

//Duration
Instant now = Instant.now();
Instant plus = now.plus(10,ChronoUnit.SECONDS);
Duration between = Duration.between(now,plus);
System.out.println(between.getSeconds());   //10
```
Period는 사람이 사용하는 날짜/시간의 기간을 측정, Duration은 초단위(나노,밀리)로 반환을 하기 때문에 주로 기계용 시간간의 기간을 측정하는데 사용할 수 있다.


<br>

## 추가
### Immutable 한 Date/Time
```java
LocalDateTime now = LocalDateTime.now();
Lonow = now.plusDays(1);


//LocalDateTime의 plusDays() 메서드
public LocalDateTime plusDays(long days) {
    LocalDate newDate = date.plusDays(days);
    return with(newDate, time);
}

private LocalDateTime with(LocalDate newDate, LocalTime newTime) {
    if (date == newDate && time == newTime) {
            return this;
    }
    return new LocalDateTime(newDate, newTime);
}
```
Date/Time의 모든 객체는 mutable한 속성의 단점을 해결하고자 Immutable한 속성을 갖고 설계가 되었는데 이 때문에 메서드를 이용해 날짜,시간을 변경하면 위에 정의된 함수처럼 새로운 객체를 만들어 반환하고 있다.



<br><Br>

---
## Reference

https://codeblog.jonskeet.uk/2017/04/23/all-about-java-util-date/