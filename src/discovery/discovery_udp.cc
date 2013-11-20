#include "discovery/discovery_udp.h"

#include <thread>

using std::size_t;
using std::thread;

namespace {

static const int kLriDiscpveryUdpPort = 9390;
static const char* kLriDiscpveryUdpGroup = "225.1.0.37";

}  // namespace

namespace lri {

DiscoveryUDP::DiscoveryUDP() :
    run_(true),
    publishers_callback_context_(NULL),
    subscribers_callback_context_(NULL),
    discovery_thread_(NULL),
    socket_(NULL) {
  // Start a new thread to listen on the UDP multicast.
  discovery_thread_ = new thread(&DiscoveryUDP::DiscoveryThread, this);

  // Prepare an instance of a multicast datagram socket interface that will be
  // used to publish to the UDP multicast.
  socket_ = new DiscoverySocket();
}

DiscoveryUDP::~DiscoveryUDP() {
  // Terminate UDP multicast listener thread.
  run_ = false;
  discovery_thread_->join();
}

void DiscoveryUDP::DiscoveryThread() {
  while (run_) {
  }
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

