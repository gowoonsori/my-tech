# 브릿지 패턴
구현부분에서 `추상적인 부분`과 `구현 부분`을 분리하여 서로 독립적으로 변경/확장이 가능하게 하는 패턴

```java
public class KakaoMapApi{
    public void drawMap(int x,int y){
        System.out.println(x + "와 " + y + "로 지도 그리기");
    }
}

public class NaverMapApi {
    Integer x;
    Integer y;

    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }

    public void drawMap(){
        if(x == null || y == null) System.out.println("에러");
        System.out.println(x + "와 " + y + "로 지도 그리기");
    }
}
public class KakaoPage {
    private int x;
    private int y;
    private KakaoMapApi mapApi = new KakaoMapApi();

    public KakaoPage(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public void drawPage(){
        mapApi.drawMap(x,y);
    }
}

public class NaverPage {
    private int x;
    private int y;
    private NaverMapApi mapApi = new NaverMapApi();

    public NaverPage(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public void drawPage(){
        mapApi.setX(x);
        mapApi.setY(y);
        mapApi.drawMap();
    }
}
```

```java
public class ModifiedKakaoPage {
    private int x;
    private int y;
    private NaverMapApi mapApi = new NaverMapApi();

    public KakaoPage(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public void drawPage(){
        mapApi.setX(x);
        mapApi.setY(y);
        mapApi.drawMap();
    }
}
```

## 

```java
public interface MapApi {
    public void drawMap(int x, int y);
}
public class NaverMapApi implements MapApi{
    private NaverMapApi mapApi = new NaverMapApi();

    @Override
    public void drawMap(x,y) {
        mapApi.setX(x);
        mapApi.setY(y);
        mapApi.drawMap();
    }
}

public class KakaoMapApi implements MapApi{
    private KakaoMapApi mapApi = new KakaoMapApi();

    @Override
    public void drawMap() {
        mapApi.drawMap(x,y);
    }
}

public interface Page {
    public void drawPage();
}
public class Page implements Page{
    private int x;
    private int y;
    private MapApi mapApi;

    public NaverPage(int x, int y,MapApi mapApi) {
        this.x = x;
        this.y = y;
        this.mapApi = mapApi;
    }

    public void drawPage(){
        mapApi.drawMap(x,y);
    }
}
```