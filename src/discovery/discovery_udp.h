#include <vector>
#include "discovery.h"

#ifndef SRC_DISCOVERY_UDP_DISCOVERY_H_
#define SRC_DISCOVERY_UDP_DISCOVERY_H_

namespace lri {

/**
 * Implements discovery by UDP multicast.
 */
class DiscoveryUDP : public Discovery {
 public:
   /**
   * Takes in a vector of topics (QueryTopic) that the node is interested in,
   * and returns a vector of publishers that are publishing to those topics.
   */
  void Query(const std::vector<QueryTopic>& topics,
                std::vector<PublishTopic>* publishers);

  /**
   * Takes in a vector of topics (PublishTopic) that the node is going to
   * publish to, for advertising them and for replying to topic queries.
   */
  void Register(const std::vector<PublishTopic>& topics);

  /**
   * Takes in a vector of topics (PublishTopic) that the node previously
   * was publishing to, but is no longer going to be publishing to.
   */
  void Unregister(const std::vector<PublishTopic>& topics);

  void SetCallback(DiscoveryCallback callback);

 protected:
  std::vector<PublishTopic> publishing_topics_;
  std::vector<QueryTopic> subscribed_topics_;
  DiscoveryCallback callback_;
};

}  // namespace lri

#endif  // SRC_DISCOVERY_UDP_DISCOVERY_H_

