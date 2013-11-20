#include <vector>
#include <stdint.h>

#ifndef DISCOVERY_SOCKET_H_
#define DISCOVERY_SOCKET_H_

namespace lri {

class DiscoveryReadSocket {
 public:
  /*
   * Default constructor: create a new connection to the discovery group.
   */
  DiscoveryReadSocket() {}

  /*
   * Default desctructor: close the connection to the discovery group.
   */
  virtual ~DiscoveryReadSocket() {}

  /*
   * Receive a chunk of data, waiting until data becomes available, if
   * neccessary. Returns true on success.
   */
  virtual bool Receive(std::vector<uint8_t>* data) = 0;

  /*
   * Receive a chunk of data if any data is pending, without waiting. Returns
   * true if data was read succesfully, returns false either on error or if
   * no data is available yet.
   */
  virtual bool ReceiveNonBlock(std::vector<uint8_t>* data) = 0;
};


class DiscoveryWriteSocket {
public:
  /*
   * Default constructor: create a new connection to the discovery group.
   */
  DiscoveryWriteSocket() {}

  /*
   * Default desctructor: close the connection to the discovery group.
   */
  virtual ~DiscoveryWriteSocket() {}

  /*
   * Write a chunk of data. Returns true on success.
   */
  virtual bool Send(const std::vector<uint8_t>& data) = 0;

};

}  // namespace lri

#endif  // DISCOVERY_SOCKET_H_
