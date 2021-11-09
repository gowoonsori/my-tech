# 프로퍼티 플래그

기본 객체 생성시 value값 과 함께 자동으로 생성되며 세가지의 플래그를 갖는다.

아래의 프로퍼티 플래그 값은 모두 true

- writable : true면 값을 수정 가능

- enumerable : true면 반복문을 사용해 나열 가능

  열거가 불가능한 프로퍼티는 Object.keys에도 배제 된다.

- configurable : true이면 프로퍼티 삭제나 플래그 수정, 추가가 가능, false면 불가능하여 돌이킬 수 없다.

<br>

## 특정 프로퍼티 정보 얻기 / 수정

- Objcect.getOwnPropertyDescripter(obj,propertName) : `프로퍼티 설명자`라는 객체가 반환된다. ( 프로퍼티 설명자에는 프로퍼티 값과 세가지 플래그가 모두 담겨있다. )

- Object.defineProperty(obj, propertyName, descripter(설명자)) : 플래그 변경하는 함수.

  <br>프로퍼티가 존재하면 변경하고 없으면 새로운 프로퍼티를 만들고 모든 플래그 값은 자동으로 false

  ```js
  let user = {};

  Object.defineProperty(user, 'name', {
    value: 'John',
  });

  let descriptor = Object.getOwnPropertyDescriptor(user, 'name', {});
  ```

- Object.defineProperties(obj, descriptors) : 프로퍼티 여러개를 한번에 정의 가능

  ```js
  Object.defineProperties(user, {
    name: { value: 'John', writable: false },
    surname: { value: 'Smith', writable: false },
  });
  ```

- Object.getOwnPropertyDescriptors(obj) : 프로퍼티 설명자를 전부 한꺼번에 가져오기

  ```js
  let clone = Object.defineProperties({}, Object.getOwnPropertyDescriptors(obj));
  ```

  객체를 복사시 for...in과 같이 위와 같은 방법으로 복사가 가능하다.

  for...in은 플래그 정보와 심볼형 프로퍼티는 복사가 안되는 반면에 위 방법은 모두 그대로 복사가 가능하다.

- Object.preventExtensions(obj) : 객체에 새로운 프로퍼티 추가 x
- Object.seal(obj) : 프로퍼티 전체에 configurable : false와 동일 효과
- Object.freeze(obj) : 프로퍼티 전체에 configure : false, wirtable : false와 동일 효과
- Objcet.Extensible(obj) : 새로운 프로퍼티 추가 가능할 경우 true, 아니면 false return
- Object.isSealed(obj) : 프로퍼티 추가,삭제가 불가능하고 모든 프로퍼티 configurable이 false면 true, 아니면 false
- Object.isFrozen(obj) : 프로퍼티 추가 삭제,변경이 불가능하고 모든 프로퍼티가 configurable : false, wirtable : false면 true
