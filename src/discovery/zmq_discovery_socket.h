#include <vector>
#include <sys/types.h>

#include "discovery/discovery_socket.h"

#ifndef ZMQ_DISCOVERY_SOCKET_H_
#define ZMQ_DISCOVERY_SOCKET_H_

namespace zmq {
class context_t;
class socket_t;
}  // namespace zmq

namespace lri {

class ZmqDiscoveryReadSocket : public DiscoveryReadSocket {
 public:
  /*
   * Default constructor: create a new connection to the discovery group.
   */
  ZmqDiscoveryReadSocket();

  /*
   * Default desctructor: close the connection to the discovery group.
   */
  virtual ~ZmqDiscoveryReadSocket();

  /*
   * Receive a chunk of data, waiting until data becomes available, if
   * neccessary. Returns true on success.
   */
  virtual bool Receive(std::vector<uint8_t>* data);

  /*
   * Receive a chunk of data if any data is pending, without waiting. Returns
   * true if data was read succesfully, returns false either on error or if
   * no data is available yet.
   */
  virtual bool ReceiveNonBlock(std::vector<uint8_t>* data);

 protected:
  zmq::context_t* context_;
  zmq::socket_t* socket_;
};


class ZmqDiscoveryWriteSocket : public DiscoveryWriteSocket {
public:
  /*
   * Default constructor: create a new connection to the discovery group.
   */
  ZmqDiscoveryWriteSocket();

  /*
   * Default desctructor: close the connection to the discovery group.
   */
  virtual ~ZmqDiscoveryWriteSocket();

  /*
   * Write a chunk of data. Returns true on success.
   */
  virtual bool Send(const std::vector<uint8_t>& data);

 protected:
  zmq::context_t* context_;
  zmq::socket_t* socket_;
};

}  // namespace lri

#endif  // ZMQ_DISCOVERY_SOCKET_H_
