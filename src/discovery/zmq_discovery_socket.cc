#include "discovery/zmq_discovery_socket.h"

#include <stdio.h>
#include <string.h>
#include <vector>
#include <stdint.h>
#include <zmq.hpp>

using std::size_t;
using std::string;
using std::vector;

namespace {

// Number of threads to ask ZMQ to use. The ZMQ manual suggests it be set to
// the bandwidth in GB/s that is expected to be used.
const size_t kNumZmqThreads = 1;

// The IPC channel to use for discovery on the same computer.
const string kIpcAddress = "ipc://lri_test.ipc";

// The Encapsulated Pragmatic General Multicast (EPGM) multicast address to
// use for discovery accross computers on the same subnet.
const string kEpgmAddress = "epgm://225.1.0.37:9390";

}  // namespace

namespace lri {

ZmqDiscoveryReadSocket::ZmqDiscoveryReadSocket() :
    context_(NULL), socket_(NULL) {
  try {
    context_ = new zmq::context_t(kNumZmqThreads);
    socket_ = new zmq::socket_t(*context_, ZMQ_PUB);
    socket_->connect(kIpcAddress.c_str());
    socket_->connect(kEpgmAddress.c_str());
    socket_->setsockopt(ZMQ_SUBSCRIBE, "", 0);
  }
  catch(const std::exception& exception) {
    fprintf(stderr, "Error in %s : %s\n", __FUNCTION__, exception.what());
  }
}

ZmqDiscoveryReadSocket::~ZmqDiscoveryReadSocket() {
  if (socket_) {
    delete socket_;
    socket_ = NULL;
  }
  if (context_) {
    delete context_;
    context_ = NULL;
  }
}

bool ZmqDiscoveryReadSocket::Receive(vector<uint8_t>* data) {

}

bool ZmqDiscoveryReadSocket::ReceiveNonBlock(vector<uint8_t>* data) {

}

ZmqDiscoveryWriteSocket::ZmqDiscoveryWriteSocket() :
    context_(NULL), socket_(NULL) {
  try {
    context_ = new zmq::context_t(kNumZmqThreads);
    socket_ = new zmq::socket_t(*context_, ZMQ_PUB);
    socket_->bind(kIpcAddress.c_str());
    socket_->connect(kEpgmAddress.c_str());
  }
  catch(const std::exception& exception) {
    fprintf(stderr, "Error in %s : %s\n", __FUNCTION__, exception.what());
  }
}

ZmqDiscoveryWriteSocket::~ZmqDiscoveryWriteSocket() {
  if (socket_) {
    delete socket_;
    socket_ = NULL;
  }
  if (context_) {
    delete context_;
    context_ = NULL;
  }
}

bool ZmqDiscoveryWriteSocket::Send(const vector<uint8_t>& data) {

}

}  // namespace lri
