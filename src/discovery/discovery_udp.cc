#include "discovery_udp.h"

namespace lri {

DiscoverUDP::DiscoveryUDP() {
  // Start a new thread to listen on the UDP multicast.
}

DiscoverUDP::~DiscoveryUDP() {
  // Terminate UDP multicast listener thread.
}

void DiscoveryUDP::Query(
    const std::vector<QueryTopic>& topics, 
    std::vector<PublishTopic>* publishers) {
  // Send out multicast QueryTopic packets for every topic.
  
  // Wait for response from peers on the multicast address and return
  // responses.
}

void DiscoveryUDP::Register(const std::vector<PublishTopic>& topics) {
  // Save the list of topics.
  // Announce the topics.
} 

void DiscoveryUDP::Unregister(const std::vector<PublishTopic>& topics) {
  // Remove the topics from the saved list.
  // Send unregister notice to the multicast address.
}

void DiscoveryUDP::SetCallback(DiscoveryCallback callback) {
  callback_ = callback;
}

}  // namespace lri

