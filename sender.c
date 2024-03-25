#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

// 127.0.0.1는 localhost, 즉 자기 자신의 주소를 가리킴
#define SERVER_IP ("127.0.0.1")
#define SERVER_PORT (7777)

int main() {
  int clientSocket;
  // sockaddr_in은 주소체계, ip, port와 같은 정보를 입력하게 해주는 구조체
  struct sockaddr_in serverAddr;
  char *MSG = "Hello~!";

  printf("Client start \n");

  // PF_INET: IPv4 인터넷 프로토콜을 사용함
  // SOCK_DRAM: UDP로 통신함을 알림 SOCK_STREAM은 TCP/IP 프로토콜을 사용한다는
  // 0: protocol 통신에 있어 특정 프로토콜을 사용하기 위해 지정한 변수, 보통 0

  // 소켓 생성
  if ((clientSocket = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
    printf("socket() failed.\n");
    return -1;
  }
  // memset(): 메모리 영역을 특정한 값을 설정하는 역할, memory set의 줄임말
  // 첫번째 인자는 메모리 크기를 변경할 포인터, 두번째는 초기화 값, 세번째는
  // 초기화 크기 반환값인데 성공시 ptr을 반환하고, 실패 시 NULL을 반환
  memset(&serverAddr, 0x00, sizeof(serverAddr));
  serverAddr.sin_family = AF_INET; // IPv4 인터넷 프로토콜
  serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
  serverAddr.sin_port = htons(SERVER_PORT);

  // strlen()은 문자열의 길이를 계산하기 출력하는 함수
  if (sendto(clientSocket, MSG, strlen(MSG), 0, (struct sockaddr *)&serverAddr,
             sizeof(serverAddr)) < 0) {
    printf("sendto() failed.\n");
    return -3;
  }

  printf("          Sending completed. \n");

  close(clientSocket);
  printf("End.\n");

  return 0;
}
