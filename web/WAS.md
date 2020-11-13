# Web Server

html, css, js, image와 같이 정적인 파일들에 대한 요청을 응답하는 서버

- Forward Proxy : 캐쉬기능이 있어 자주 사용하는 컨텐츠에 대해서는 더 빠르게 응답이 가능하다.

- Reverse Proxy : HTTP요청을 특정 네트워크, 서버로 전달하는 역할을 수행하는 서버. 내부 네트워크에 접근할 수 있도록 전달하는 역할

`Apache`, `Nginx` 등이 존재한다.

<br>

# WAS (Web Application Server)

동적 웹 서비스를 위해 동적인 정보를 생성하는 역할을 담단하는 미들웨어.
Web server와 애플리케이션 사이에서 중간 다리역할을 하며, 동적으로 데이터를 처리하여 전달해주는 서버

`Tomcat`, `uWsgi`, `Jboss` 등이 존재한다.

<br>

# Web Application

웹서버(WAS)로 부터 전달 받은 동적인 데이터를 처리를 수행하고 그에 맞는 응답을 보내주는 부분.
