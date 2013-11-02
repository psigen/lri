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

// A sub-class of Poco::Runnable, defining the background thread that will be
// used to listen on the UDP multicast for subscription
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

void DiscoveryUDP::QueryPublishers(const std::vector<TopicUri>& topics) {
  // Add @topics to subscribed_topics_ to keep track of its publishers.
  // TODO(joydeepb): Check for duplicates.
  subscribed_topics_.insert(subscribed_topics_.end(), topics.begin(),
                            topics.end());

  // Send out multicast QueryTopic packets for every topic.

  // Wait a bit for response from peers on the multicast address and return
  // responses.
}

void DiscoveryUDP::RegisterPublisher(const std::vector<TopicUri>& topics) {
  // Save the list of topics.
  // TODO(joydeepb): Check for duplicates.
  publishing_topics_.insert(publishing_topics_.end(), topics.begin(),
                            topics.end());
  // Announce the topics.
}

void DiscoveryUDP::UnregisterPublisher(const std::vector<TopicUri>& topics) {
  // Remove the topics from the saved list.
  // Send unregister notice to the multicast address.
}

void DiscoveryUDP::SetPublishersCallback(DiscoveryCallback callback,
                                         void* context) {
  publishers_callback_ = callback;
  publishers_callback_context_ = context;
}

void DiscoveryUDP::SetSubscribersCallback(DiscoveryCallback callback,
                                          void* context) {
  subscribers_callback_ = callback;
  subscribers_callback_context_ = context;
}

}  // namespace lri

