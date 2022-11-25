
- 기존 Select가 확인하던 I/O 상태변화에 대해서 소켓별로 WAS를 사용하여 등록을 하면 윈도우 메시지를 통해서 통지

- 사용자가 커널의 상황을 지속적으로 확인하며 통지를 받는 것이 아니라, 특정 상황이 되면 통지를 주도록 예약

- 즉 둘이 합쳐 Async Select이다. 통지 방식으로 윈도우 메시지를 사용하는 만큼 WAS는 윈도우 프로시저에서만 사용가능

- 리눅스의 동기 형식의 통지방식은 다수의 fd(소켓)에 대해서 동시에 체크 할 수 있었지만, 윈도우의 비동기 통지방식은 소켓별로 따로 통지

- 비동기 통지의 경우 한번 등록하면 계속해서 호출할 필요가 없기 때문에, 부하가 적다는 이점

- 부적으로 따로 체크하는 것이 아니라 운영체제가 I/O 상황이 될때 인터럽트를 사용하는 방식으로 구현되기 때문에 운영체제 수준에서도 연산량이 많이 줄어듬.

- 다른 운영체제에서 지원하지 않는 기능이기 때문에, 다른 구동환경에서 같은 프로세스를 사용할 수가 없다는 단점
![image](https://user-images.githubusercontent.com/54939319/203927208-4776ead4-41a6-4a54-889b-46ee64bdfa16.png)

```C
int WSAAsyncSelect(
   SOCKET socket, // I/O 상황을 체크할 소켓
   HWND hWnd, //메시지 통지를 받을 윈도우 핸들
   unsigned int wMsg, //이벤트가 발생하면 보낼 메시지
   long lEvent //통지받을 네트워크 이벤트 비트마스크
);
//성공시 0을 반환, 실패시 SOCKET_ERROR 반환
//네트워크 이벤트
enum NetworkEvent
{
   FD_ACCEPT, //클라이언트가 접속했을 때
   FD_READ,   //수신 가능할 때
   FD_WRITE,  //송신 가능할 때
   FD_CLOSE,  //접속 종료할 때
   FD_CONNECT,//접속 완료될 때
   FD_OOB,    //OOB 데이터 도착할 때
};

```


```C
#define WM_SOCKET (WM_USER + 1)
int main(){
HWND hWnd = MakeWindow();
...
   WSAAsyncSelect( socket, hWnd, WM_SOCKET, FD_READ | FD_WRITE | FD_CLOSE ); 
  //소켓에 AsyncSelect 이벤트 등록
...
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
...
switch(uMsg)
{
   case WM_SOCKET:
   {
      SOCKET selectedSocket = wParam; //socket번호는 wParam으로 전달
      int event = WSAGETSELECTEVENT(lParam); //이벤트 정보는 lParam에서 추출
      switch(event)
      {
         //I/O 이벤트별 대응코드
      }
   }
}
```


- 커널에게 미리 등록만 해두면 유저는 따로 커널에게 확인하여 동기화하지 않더라도 알아서 메시지가 발생.
 
- Sync보다 상당히 편하고, 매 프레임마다 체크를 하지 않아도 되니 부담 적음.
 
- WAS 함수자체에서 I/O상황을 리턴받는 것이 아니고 등록만 하는 것이다 보니 Block이 걸릴 소지가 없다. 따라서 Non-Block 방식
