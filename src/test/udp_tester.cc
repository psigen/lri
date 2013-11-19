#include <algorithm>
#include <iostream>
#include <sstream>
#include <zmq.hpp>

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <unistd.h>

#include <iostream>

using std::string;

namespace {
string IToA(const int n) {
  std::stringstream stream;
  stream << n;
  return stream.str();
}
const int kPortNumber =  9390;
const string kMulticastAddress = "225.1.0.37";
const string kEpgmAddress =
    "epgm://" + kMulticastAddress + ":" + IToA(kPortNumber);
const string kIpcAddress = "ipc://lri_test.ipc";
}  // namespace

void ZmqSender() {
  printf("ZMQ Sender\n");
  const char message_string[] = "Hello, World!";
  zmq::message_t message(sizeof(message_string));
  std::copy(&(message_string[0]), &(message_string[0]) + message.size(),
            reinterpret_cast<char*>(message.data()));
  //  Prepare our context and publisher
  zmq::context_t context (1);
  zmq::socket_t publisher (context, ZMQ_PUB);
  publisher.bind(kIpcAddress.c_str());
  publisher.connect(kEpgmAddress.c_str());
  while (1) {
    publisher.send(message.data(), message.size(), 0);
    printf("Sent \"%s\"\n", message.data());
    sleep(1);
  }
}

void ZmqReceiver() {
  printf("ZMQ Receiver\n");
  zmq::context_t context (1);

  //  Socket to talk to server
  zmq::socket_t subscriber (context, ZMQ_SUB);
  subscriber.connect(kIpcAddress.c_str());
  subscriber.connect(kEpgmAddress.c_str());
  subscriber.setsockopt(ZMQ_SUBSCRIBE, "", 0);
  while (1) {
    zmq::message_t update;
    subscriber.recv(&update);
    std::istringstream iss(static_cast<char*>(update.data()));
    printf("Received \"%s\"\n", iss.str().c_str());
    //std::cout << "Received \"" << update.data() << "\"\n";
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
  addr.sin_addr.s_addr = inet_addr(kMulticastAddress.c_str());
  addr.sin_port=htons(kPortNumber);

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
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY); /* N.B.: differs from sender */
  addr.sin_port = htons(kPortNumber);

  /* bind to receive address */
  if (bind(fd,(struct sockaddr *) &addr,sizeof(addr)) < 0) {
    perror("bind");
    exit(1);
  }

  /* use setsockopt() to request that the kernel join a multicast group */
  mreq.imr_multiaddr.s_addr=inet_addr(kMulticastAddress.c_str());
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
      ZmqSender();
      break;

    case 1:
      ZmqReceiver();
      break;

    case 2:
      NativeSender();
      break;

    case 3:
      NativeReceiver();
      break;

  }
  return 0;
}


