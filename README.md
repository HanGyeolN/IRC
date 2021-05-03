# IRC


- RFC

    [RFC 1459 - Internet Relay Chat Protocol](https://tools.ietf.org/html/rfc1459)

    [RFC 2810 - Internet Relay Chat: Architecture](https://tools.ietf.org/html/rfc2810)

    [RFC 2811 - Internet Relay Chat: Channel Management](https://tools.ietf.org/html/rfc2811)

    [RFC 2812 - Internet Relay Chat: Client Protocol](https://tools.ietf.org/html/rfc2812)

    [RFC 2813 - Internet Relay Chat: Server Protocol](https://tools.ietf.org/html/rfc2813)

    [RFC 7194 - Default Port for Internet Relay Chat (IRC) via TLS/SSL](https://tools.ietf.org/html/rfc7194)

- RFC 번역

    [RFC 1459](https://www.notion.so/RFC-1459-b46637780e024af5811cf5beb3a9d6d7)

    [RFC 2810](https://www.notion.so/RFC-2810-c6ec3c5f99fc4202a4252d667ef0192f)

    [RFC 2811](https://www.notion.so/RFC-2811-47c61fe47321446c95d556cd9bedf0c4)

    [RFC 2812](https://www.notion.so/RFC-2812-54bad51eda60408e85f2fa4d50d02687)

    [RFC 2813](https://www.notion.so/RFC-2813-cfaec233fc5f46f0996c71f54164f4bf)

    [RFC 7194](https://www.notion.so/RFC-7194-eddc2e0873a74616bafd6b8709977982)

요구사항

- IRC 서버를 C++로 작성 할 것
- C++98 버전을 사용
- RFC 1459, 2810, 2811, 2812, 2813, 7193를 따를 것
- 서버와 클라이언트 사이의 통신은 TCP/IP(v4 또는 v6)를 통해야 한다.
- 서버간 통신도 고려 할 것
- TLS 통신을 위해 암호화 라이브러리를 사용 할 것
- Fork 사용 금지, 다른 OS와의 호환성을 위해서 IO 수행은 논블락으로 해야 한다. select를 사용 할 것
- 기존 IRC 클라이언트로 연결이 가능해야 하고, 다른 IRC서버와 상호작용이 가능해야한다.
- 허용 함수 외 사용금지

접속

host: [irc.hangyeol.co.kr](http://irc.hangyeol.co.kr)

port: 6667, 6668(SSL)

passwd: 1234

(결과물 사진들 추가)

---

Q: 왜 FD_SET과 select를 사용하나? 

A: 다수의 클라이언트가 하나의 서버에 접속했을 때, 명령들을 동시에 처리하려면 fork나 thread를 사용해야 한다. 하지만 이런 멀티프로세싱이나 멀티스레딩 방식은 프로세스를 복사하면서 큰 부담이 걸리기 때문에 더 부담이 적은 방식인 select (멀티플렉싱) 방식을 사용한다.

관련 설명: [https://pony11.tistory.com/15](https://pony11.tistory.com/15)

개발 단계

---

1. RFC 번역 및 요구사항 파악

2. 소켓 통신, echo 서버 클라이언트 실습

3. select 활용 멀티플렉싱 서버 구현

4. 다중소켓 관리, 유저 테이블 구현

5. 서버간 공유할 데이터 테이블 구현

6. 메세지, REPLY 클래스 구현

7. RFC 커맨드 구현 (상용 irc서버에 메세지를 보내보고 그 결과를 확인하면서 구현에 참고함)

8. SSL 적용 

9. NONBLOCK 적용 (SSL과 NONBLOCK 적용은 처음에 해놓는게 좋음)

10. 상용 IRC 클라이언트 및 서버간 연결 테스트

어려웠던점

---

1. 맨처음 설계
2. select와 fd_set을 이용한 멀티플렉싱 서버를 이해하는것 
3. 여러 서버가 연결되어 있을 때, 최적 경로로 클라이언트간 메세지가 전송되도록 하는 것
4. 메세지를 읽을 때 CRLF단위로 끊어서 여러 메세지 단위를 한번 읽힌 것 처럼 하는 것 (get_next_line 처럼)
5. Reply 같은 정해진 문자열에 변수만 바뀌는 경우, 어떻게 설계해야 효율적일지 생각 해내는 것
6. nonblock으로 동작하도록 만드는것

---

발생한 문제들

[#issues](https://github.com/AMATEURTOSS/ft_irc/issues) 

---

다른사람 참고

[https://github.com/markveligod/ft_irc/blob/main/includes/Class.Command.hpp](https://github.com/markveligod/ft_irc/blob/main/includes/Class.Command.hpp)

싱글턴패턴 소년코딩

[https://boycoding.tistory.com/109](https://boycoding.tistory.com/109)

enum

[https://boycoding.tistory.com/179](https://boycoding.tistory.com/179)

커맨드패턴

[https://gmlwjd9405.github.io/2018/07/07/command-pattern.html](https://gmlwjd9405.github.io/2018/07/07/command-pattern.html)

[https://moonshoo.tistory.com/5](https://moonshoo.tistory.com/5)
