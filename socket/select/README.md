
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
