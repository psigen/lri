#include "discovery/discovery_udp.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/MulticastSocket.h"
#include "Poco/Net/DatagramSocket.h"
#include "Poco/Runnable.h"
#include "Poco/Thread.h"

using std::size_t;

namespace {

static const int kLriDiscpveryUdpPort = 9390;
static const char* kLriDiscpveryUdpGroup = "225.1.0.37";
static const Poco::Net::SocketAddress kLriDiscoverySocketAddress(
    kLriDiscpveryUdpGroup, kLriDiscpveryUdpPort);

class DiscoveryUDPFunction : public Poco::Runnable {
 public:
  DiscoveryUDPFunction() : Poco::Runnable() : run_(true) {}
  virtual ~DiscoveryUDPFunction() {};

 private:
  virtual void run() {
    // Until run_ becomes false, wait for messages to be received on UDP
    // multicast.
    // When new data is received, parse the proto message and update the list
    // of topic publishers accordingly.
  }

 public:
  void Shutdown() {
    run_ = false;
  }

private:
  bool run_;
};

}  // namespace

namespace lri {

typedef Poco::Thread Thread;
typedef Poco::Net::DatagramSocket DatagramSocket;

DiscoveryUDP::DiscoveryUDP() {
  // Start a new thread to listen on the UDP multicast.
  discovery_thread_ = new Thread();
  discovery_thread_->start(new DiscoveryUDPFunction);

  // Prepare an instance of a multicast datagram socket interface that will be
  // used to publish to the UDP multicast.
  socket_ = new DatagramSocket();
}

DiscoveryUDP::~DiscoveryUDP() {
  // Terminate UDP multicast listener thread.
}

void DiscoveryUDP::Query(
  const std::vector<TopicQuery>& topics,
    std::vector<TopicPublisher>* publishers) {
  // Send out multicast QueryTopic packets for every topic.
  for (size_t i = 0; i < topics.size(); ++i) {
    
  }

  // Wait for response from peers on the multicast address and return
  // responses.
}

void DiscoveryUDP::Register(const std::vector<TopicQuery>& topics) {
  // Save the list of topics.
  publishing_topics_.insert(publishing_topics_.end(), topics.begin(),
                            topics.end());
  // Announce the topics.
}

void DiscoveryUDP::Unregister(const std::vector<TopicQuery>& topics) {
  // Remove the topics from the saved list.
  // Send unregister notice to the multicast address.
}

void DiscoveryUDP::SetCallback(DiscoveryCallback callback) {
  callback_ = callback;
}

}  // namespace lri

