#include "discovery/discovery_udp.h"

#include <thread>

#include "discovery/zmq_discovery_socket.h"

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
    read_socket_(NULL),
    write_socket_(NULL) {
  // Start a new thread to listen on the UDP multicast.
  discovery_thread_ = new thread(&DiscoveryUDP::DiscoveryThread, this);

  // Prepare read and write instances of UDP sockets interface that will be
  // used to receive from, and publish to the UDP multicast.
  read_socket_ = new ZmqDiscoveryReadSocket();
  write_socket_ = new ZmqDiscoveryWriteSocket();
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

}

void DiscoveryUDP::RegisterPublisher(const std::vector<TopicUri>& topics) {
  // Save the list of topics.
  // TODO(joydeepb): Check for duplicates.
  publishing_topics_.insert(publishing_topics_.end(), topics.begin(),
                            topics.end());
  // Announce the topics.
}

void DiscoveryUDP::UnregisterPublisher(const std::vector<TopicUri>& topics) {
  for (size_t i = 0; i < topics.size(); ++i) {
    const std::vector<lri::TopicUri>::iterator publisher_index;// = 
//        find(publishing_topics_.begin(), publishing_topics_.end(), topics[i]);
    if (publisher_index != publishing_topics_.end()) {
      // Remove the topics from the saved list.
      publishing_topics_.erase(publisher_index);
      // Send unregister notice to the multicast address.
    }
  }
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

