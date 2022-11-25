
- 쓰레드 하나로 다중처리 가능

- 서버가 여러 클라이언트를 처리하기 위한 방법 중 입출력 다중화를 사용하는 방법

- 멀티 플렉싱 모델 이라기도 함 , 하나의 프로세스로 여러 클라이언트와 통신하는 방법ㅊ

- 소켓셋에 저장된 소켓에 변화가 생길 때 까지 기다리고 있다가 소켓이 어떤 동작을 하면 동작한 소켓을 제외한 나머지 소켓을 모두 제거하고 해당되는 소켓에 대해 진행



```c
int select(int n,    // 검사할 파일 디스크립터 번호 중 가장 큰 값+1 (배열인자로 접근하기 때문에)
fd_set* readfds,    // 읽기를 검사할 fd_set
fd_set* writefds,    // 쓰기를 검사할 fd_set
fd_set* exceptfds,    // 예외를 검사할 fd_set
const struct timeval* timeout);    // 검사하는 시간에 제한을 둔다. NULL이면 무한정 대기한다.
// return값 : 0 <= 변경이 생긴 파일의 수, -1 = 실패
```


- select()의 핵심은 fd_set을 제어

- fd_set은 파일 디스크립터 번호를 배열로 가지는 '비트 필드'구조체

- select()는 fd_set을 순회하며, fd_set값이 1인 파일에 대해 읽기 또는 쓰기를 검사하고 변화가 생긴 fd_set을 1 생성 , 없으면 0

### fd_set을 제어하는 매크로 함수

![image](https://user-images.githubusercontent.com/54939319/203883234-44d4b1c2-5524-4091-9263-212f4bc922af.png)

#### EX

7개의 소켓을 만들었고, 각 소켓은 3~9까지 fdnum을 부여받았다고 가정하자. 그럼 fd_set의 모습은 다음과 같을 것이다.

![image](https://user-images.githubusercontent.com/54939319/203883513-51cfc9c3-5223-44a7-a124-277dc69c1f8b.png)

```c
// 3,5,8 소켓에 대해 읽기를 검사하기 위해 3, 5, 8번을 등록
FD_SET(3, &readfds);
FD_SET(5, &readfds);
FD_SET(8, &readfds);


```

![image](https://user-images.githubusercontent.com/54939319/203883649-a0d22277-cfef-40c3-8e34-03bfbb22ae4b.png)

- select()로 fd_set을 검사한다.

- nfds가 9인 이유는 검사할 비트가 배열 번호상 9번 비트


```c
select(9, &readfds, (fd_set*)0, (fd_set*)0, NULL);
```

- 예를들어 3번과 5번에서 변화가 생겼다면 fd_set의 모습은 다음처럼 변한다.

![image](https://user-images.githubusercontent.com/54939319/203883756-855fe5c9-313a-4a54-824b-b77745dfa110.png)

- fd_set은 이전 상태를 유지하지 않으므로 다시 또 3, 5, 8번 소켓을 검사하고 싶다면 다시 FD_SET으로 등록시키고 사용해야 한다. 

- select로 모든 소켓 중에 뭔가 변화가 있는 소켓이 있는지 알아냈으니 이제 FD_ISSET으로 어떤 소켓에 변화가 있는지 검사를 할 수 있다

```c
FD_SET(int fd, fd_set* fdset) // fdset의 fd번째 인자를 1로 set (fd번 소켓을 1로 올린다는 소리)
FD_ISSET(int fd, fd_set* fdset) // fdset의 fd번째 인자 값을 return
```

3,5 소켓 변화 read_fds의 fd_arrya는 [0][0][0][1][0][1][0] ...
```c
FD_ISSET(3, &read_fds)  = 1
FD_ISSET(5, &read_fds)  = 1
```

반복문을 돌면서 소켓 0번부터 최대 소켓번호 n 까지 순회하며 read_fds를 검사하면 어떤 소켓이 데이터를 수신 받았는지 알 수 있다.
