# JSON (JavaScript Object Notation)

값이나 객체를 나타내주는 범용 포맷으로 js에서 사용할 목적으로 만들어진 포맷이나 현재 다른 언어에서도 json을 많이 이용하고 있다.

<br>

## JSON 포맷

- 프로퍼티 이름(key)과 값(value)는 큰따옴표로 감싸야한다. _(작은 따옴표 x)_

- new를 사용할 수 없다.

<br>

## 관련 매서드

- JSON.stringify(obj) : 객체를 JSON으로 변환

  - 함수 파라미터

    ```js
    let json = JSON.stringify(value[, replacer, space])
    ```

    - value : 인코딩 하려는 값

      ```js
      let student = {
        name: 'John',
        age: 30,
        isAdmin: false,
        courses: ['html', 'css', 'js'],
        wife: null,
      };
      let json = JSON.stringify(student);

      alert(typeof json); // string
      alert(json);
      /* JSON으로 인코딩된 객체:
      {
          "name": "John",
          "age": 30,
          "isAdmin": false,
          "courses": ["html", "css", "js"],
          "wife": null
      }
      */
      ```

    - replacer : 인코딩 하길 원하는 프로퍼티가 담긴 배열 or 매핑 함수

      > 순환 참조를 다뤄야 하는 경우에 정교하게 조정하기 위해 사용

      ```js
      let room = {
        number: 23,
      };

      let meetup = {
        title: 'Conference',
        participants: [{ name: 'John' }, { name: 'Alice' }],
        place: room, // meetup은 room을 참조합니다
      };

      room.occupiedBy = meetup; // room은 meetup을 참조합니다

      alert(
        JSON.stringify(meetup, function replacer(key, value) {
          alert(`${key}: ${value}`);
          return key == 'occupiedBy' ? undefined : value;
        })
      );

      alert(JSON.stringify(meetup, ['title', 'participants', 'place', 'name', 'number']));
      ```

    - space : 서식 변경 목적으로 사용할 공백 문자 수

      ```js
      let user = {
        name: 'John',
        age: 25,
        roles: {
          isAdmin: false,
          isEditor: true,
        },
      };

      alert(JSON.stringify(user, null, 2));
      /* 
      {
          "name": "John",
          "age": 25,
          "roles": {
              "isAdmin": false,
              "isEditor": true
          }
      }
      */

      alert(JSON.stringify(user, null, 4));
      /*
      {
          "name": "John",
          "age": 25,
          "roles": {
              "isAdmin": false,
              "isEditor": true
          }
      }
      */
      ```

  변환된 string을 JSON으로 `인코딩된` | `직렬화 처리된` | `문자열로 변환된` | `결집된` 객체라고 부른다.

  - 객체, 배열, 원시자료형도 적용할 수 있다.

    > 메서드, key가 심볼형 프로퍼티, 값이 undefiend인 프로퍼티는 무시한다.

    - 객체가 순환 참조가 있다면 변환을 실패한다. _(Error)_

- toJSON() : 객체 내부에 함수가 정의 되어 있으면 `JSON.stringify()`함수 호출시 `toJSON()`이 호출 된다.

- JSON.parse : JSON을 객체로 변환

  - 함수 파라미터

    ```js
    let value = JSON.parse(str, [reviver]);
    ```

    - str : JSON형식의 문자열

    - reviver : 모든 (key,value) 쌍을 대상으로 호출되는 function(key,value)형태의 함수로 값을 변경시킬 수 있다.

      아래와 같이 date를 그대로 parse이용해 객체로 변환시 date정보를 Date 객체가 아닌 문자열로 받았기 때문에 `meetup.date.getDate()`시 에러가 발생한다.

      따라서 아래와 같이 `reviver`를 이용해 객체로 변환시켜줄 수 있다.

      ```js
      let schedule = `{
          "meetups": [
              {"title":"Conference","date":"2017-11-30T12:00:00.000Z"},
              {"title":"Birthday","date":"2017-04-18T12:00:00.000Z"}
          ]
      }`;

      schedule = JSON.parse(schedule, function (key, value) {
        if (key == 'date') return new Date(value);
        return value;
      });

      alert(schedule.meetups[1].date.getDate());
      ```
