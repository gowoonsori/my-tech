# Http Header

## 공통 헤더

- Date : http메세지가 만들어진 시간

- Connection : `HTTP/1.1`에서 기본적으로 keep-alive이고 `HTTP/2`에서는 사라진 헤더
- Content-Length : 메세지의 본문(payload,body)의 크기를 바이트 단위로 표시
- Content-Type : 컨텐츠의 타입([MIME](https://developer.mozilla.org/ko/docs/Web/HTTP/Basics_of_HTTP/MIME_types/Common_types))과 인코딩 정보

- Content-Language : 사용자의 언어 (ko-KR..)
- Content-Encoding : 미디어 타입을 압축하기 위한 헤더 (어떤 알고리즘을 사용했는가)
- Cach-Control : 캐싱을 사용하기 위해 정의하는데 사용

  - 일반적으로 GET 요청에 사용되며, 가져온 데이터를 저장해 두고 캐싱하여 사용하기 위해 웹에서도 캐시를 사용한다.

  많은 부가 속성 [보기](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Cache-Control)

## Request 헤더

- Host : 서버의 도메인 네임

- User-Agent : 사용자의 클라이언트 (브라우저)
- Accept : 받고싶은 데이터 타입

  - Accept-Encoding
  - Accpet-Charset
  - Accept-Language...

- Authorization : 인증 토큰을 서버로 보낼때 사용하는 헤더
- Origin : 어떤 url에서 요청을 보냈는가 ( CSRF공격 방지 )
- Referer : 요청을 보낸 페이지 이전의 페이지 ( CSRF공격을 방지 )

  이를 이용해 애널리틱스 같은 곳에서 어디에서 접근했는지 검사도 가능하다.

- If-None-Match : 요청 측에서 ETag가 달라졌는지 검사를 요청하는 태그
- Cookie : 클라이언트가 서버한테 쿠키를 보내줄때 사용하는 필드
  - 구조
    ```
    Cookie : key=value; key= value;...
    ```

## Response 헤더

- Access-Control-Allow-Origin : 요청을 보내는 주소를 검사하기 위한 헤더로 이와 요청하는 클라이언트 주소가 다르면 CORS 에러가 발생한다.

  서버에 접근하는 요청을 검사

- Allow : 위의 헤더 필드와 비슷하나 CORS요청 말고도 검사한다. (ex. 요청 메서드 )
- Content-Disposition : 브라우저가 응답 데이터를 어떻게 표시해야 할지 알려주는 헤더 (ex. inline = 웹페이지, attachment = download filname='filename.확장자' 등)
- Location : 201,300번대 응답이 왔을때 어떤 페이지로 리다이렉트하는지 알려주는 헤더
- Content-Security-Policy : css나 script같이 외부 파일을 불러올때 특정 파일,특정 프로토콜,특정 경로에서만 불러올 수 있도록 설정 하는 것 (XSS공격 방지)

  - 많은 속성들 [보기](https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers/Content-Security-Policy)

- Age : 캐시설정 시간(max-age)으로 부터 얼마나 지났는지 표시
- Expires : 캐시와 별개로 해당 컨텐츠가 언제 만료되는지 표시하며, cache-control의 max-age가 존재한다면 이 헤더는 무시된다.
- ETag : Http 컨텐츠가 바뀌었는지 검사하기 위한 태그 (바뀌면 클라이언트는 캐시를 지우고 새로 업데이트)

- Set-Cookie : 서버가 클라이언트한테 저장할 쿠키 데이터를 넘겨주기위한 필드

  - 구조
    ```
    Set-Cookie : key=value; options
    ```
  - 옵션

    - Expires : 쿠키 만료 날짜
    - Max-Age : 쿠키 수명 (Expires 무시)
    - Secure : https에서만 쿠키 전송
    - HttpOnly : js에서 쿠키 접근 불가
    - Domain : 도메인이 일치 하는 요청에만 쿠키 전송 (ex. gowoonsori.com)
    - Path : path옵션을 설정하고 '/directory'(url)을 주면 해당 url과 하위 도메인에서만 쿠키가 존재 (ex. gowoonsori.com/example/name)
