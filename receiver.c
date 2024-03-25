

// 표준 입력 및 출력을 지원
#include <stdio.h>
// 메모리 할당과 관련된 함수를 선언하고 있는 표준 라이브러리 헤더
#include <stdlib.h>
// 문자열 처리와 관련됨 함수들을 선언
#include <string.h>
// UNIX 운영체제 및 유닉스와 호환되는 운영 체제에서 사용되는 표준 인터페이스,
// socket()역시 여기에 포함
#include <unistd.h>
// 소켓 프로그래밍이나 네트워크에서 주로 사용되며, IP 주소를 변화하거나 다양한
// 형식으로 표시하는 데 유용한 함수를 제공
#include <arpa/inet.h>
#include <sys/socket.h>

// define 키워드를 사용하여 상수, 함수 및 코드 조각들을 정의할 수 있음
#define PORT (7777)
#define BUFF_SIZE (1024)
#define QUEUE_LIMIT (1)

int main() {
  int serverSocket; // Socket descriptor
  struct sockaddr_in serverAddr;

  struct sockaddr_in clientAddr;
  unsigned int clientAddrLength;

  char buff[BUFF_SIZE];

  printf("Server start\n");

  if ((serverSocket = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
    printf("socket() failed.\n");
    return -1;
  }

  // 서버 쪽의 주소 정보를 생성
  memset(&serverAddr, 0x00, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET;
  // INADDR_ANY = 소켓을 바인딩할 때 사용, 특정한 IP 주소를 지정하지 않고 소켓을
  // 수신 대기 상태로 만듦.
  serverAddr.sin_addr.s_addr = INADDR_ANY;
  // 열어줄 포트의 번호를 생성
  serverAddr.sin_port = htons(PORT);

  // 소켓에 주소 정보를 바인드
  if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) <
      0) {
    printf("bind() failed.\n");
    return -2;
  }

  printf("          Waiting..\n");

  clientAddrLength = sizeof(clientAddr);
  recvfrom(serverSocket, buff, BUFF_SIZE, 0, (struct sockaddr *)&clientAddr,
           &clientAddrLength);

  printf("      Recv data: %s\n", buff);

  close(serverSocket);

  printf("End.\n");
}
