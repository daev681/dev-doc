
- 쓰레드 하나로 다중처리 가능

- 서버가 여러 클라이언트를 처리하기 위한 방법 중 입출력 다중화를 사용하는 방법

- 멀티 플렉싱 모델 이라기도 함 , 하나의 프로세스로 여러 클라이언트와 통신하는 방법


```
int select(int n,    // 검사할 파일 디스크립터 번호 중 가장 큰 값+1 (배열인자로 접근하기 때문에)

fd_set* readfds,    // 읽기를 검사할 fd_set

fd_set* writefds,    // 쓰기를 검사할 fd_set

fd_set* exceptfds,    // 예외를 검사할 fd_set

const struct timeval* timeout);    // 검사하는 시간에 제한을 둔다. NULL이면 무한정 대기한다.

// return값 : 0 <= 변경이 생긴 파일의 수, -1 = 실패
```
