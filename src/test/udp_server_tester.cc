#include "string.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/MulticastSocket.h"
#include "Poco/Net/DatagramSocket.h"
#include "Poco/Timestamp.h"
#include "Poco/DateTimeFormatter.h"
#include <iostream>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <fcntl.h>

#define PORT_NUMBER 9390
#define GROUP_ID "225.1.0.37"

void PocoSender() {
  printf("Poco sender\n");
  Poco::Net::SocketAddress sa(GROUP_ID, PORT_NUMBER);
  Poco::Net::DatagramSocket dgs;
  const char msg[] = "Hello Poco!";
  dgs.sendTo(msg, sizeof(msg), sa);
}

void PocoReceiver() {
  printf("Poco receiver\n");
  Poco::Net::SocketAddress sa(Poco::Net::IPAddress(), PORT_NUMBER);
  Poco::Net::DatagramSocket dgs;
  dgs.bind(sa, true);
  char buffer[1024];
  for (;;)
  {
    Poco::Net::SocketAddress sender;
    int n = dgs.receiveFrom(buffer, sizeof(buffer)-1, sender);
    buffer[n] = '\0';
    std::cout << sender.toString() << ": " << buffer << std::endl;
  }
}

void NativeSender() {
  printf("Native sender\n");
  struct sockaddr_in addr;
  int fd, cnt;
  struct ip_mreq mreq;
  const char message[] = "Hello, World!";

  /* create what looks like an ordinary UDP socket */
  if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
    perror("socket");
    exit(1);
  }

  /* set up destination address */
  memset(&addr,0,sizeof(addr));
  addr.sin_family=AF_INET;
  addr.sin_addr.s_addr=inet_addr(GROUP_ID);
  addr.sin_port=htons(PORT_NUMBER);

  /* now just sendto() our destination! */
  while (1) {
    if (sendto(fd,message,sizeof(message),0,(struct sockaddr *) &addr,
        sizeof(addr)) < 0) {
      perror("sendto");
      exit(1);
    }
    printf("Sent \"%s\"\n", message);
    sleep(1);
  }
}

void NativeReceiver() {
  printf("Native receiver\n");
  struct sockaddr_in addr;
  int fd, nbytes,addrlen;
  struct ip_mreq mreq;
  char msgbuf[256];

  u_int yes=1;            /*** MODIFICATION TO ORIGINAL */

  /* create what looks like an ordinary UDP socket */
  if ((fd=socket(AF_INET,SOCK_DGRAM,0)) < 0) {
    perror("socket");
    exit(1);
  }

  /**** MODIFICATION TO ORIGINAL */
  /* allow multiple sockets to use the same PORT number */
  if (setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(yes)) < 0) {
    perror("Reusing ADDR failed");
    exit(1);
  }
  /*** END OF MODIFICATION TO ORIGINAL */

  /* set up destination address */
  memset(&addr,0,sizeof(addr));
  addr.sin_family=AF_INET;
  addr.sin_addr.s_addr=htonl(INADDR_ANY); /* N.B.: differs from sender */
  addr.sin_port=htons(PORT_NUMBER);

  /* bind to receive address */
  if (bind(fd,(struct sockaddr *) &addr,sizeof(addr)) < 0) {
    perror("bind");
    exit(1);
  }

  /* use setsockopt() to request that the kernel join a multicast group */
  mreq.imr_multiaddr.s_addr=inet_addr(GROUP_ID);
  mreq.imr_interface.s_addr=htonl(INADDR_ANY);
  if (setsockopt(fd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) < 0) {
    perror("setsockopt");
    exit(1);
  }

  /* now just enter a read-print loop */
  while (1) {
    addrlen=sizeof(addr);
    if ((nbytes=recvfrom(fd,msgbuf,sizeof(msgbuf),0,
        (struct sockaddr *) &addr,(socklen_t*) &addrlen)) < 0) {
      perror("recvfrom");
      exit(1);
    }
    msgbuf[255] = 0;
    printf("Received \"%s\"\n", msgbuf);
  }
}

int main(int argc, char* argv[])
{
  if (argc<2) {
    printf("Run mode [1-6] not specified.\n");
    return 1;
  }
  if (argv[1][0]<'1' || argv[1][0]>'6') {
    printf("Invalid option.\n");
    return 1;
  }
  const int mode = argv[1][0] - '1';
  switch(mode) {
    case 0:
      PocoSender();
      break;

    case 1:
      PocoReceiver();
      break;

    case 2:
      NativeSender();
      break;

    case 3:
      NativeReceiver();
      break;

    case 4:
      PocoSender();
      break;

    case 5:
      PocoSender();
      break;

  }
  return 0;
}


