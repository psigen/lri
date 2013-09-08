#include <vector>
#include "discovery.h"

#ifndef SRC_DISCOVERY_DISCOVERY_UDP_H_
#define SRC_DISCOVERY_DISCOVERY_UDP_H_


namespace lri {

class Thread;
class DatagramSocket;

/**
 * Implements discovery by UDP multicast.
 */
class DiscoveryUDP : public Discovery {
 public:
   /**
   * Takes in a vector of topics (QueryTopic) that the node is interested in,
   * and returns a vector of publishers that are publishing to those topics.
   */
   void QueryPublishers(const std::vector<lri::TopicQuery>& topics,
              std::vector<lri::TopicPublisher>* publishers);

   /**
    * Takes in a vector of topics that the node is publishing to,
    * and returns a vector of subscribers that are publishing to those topics.
    */
  virtual void QuerySubscribers(
    const std::vector<lri::TopicQuery>& topics,
    std::vector<lri::TopicPublisher>* publishers);

   /**
  * Takes in a vector of topics that the node is subscribing to, for querying
  * their publishers and for keeping track of their publishers.
  */
  virtual void RegisterSubscriber(const std::vector<lri::TopicQuery>& topics);

  /**
  * Takes in a vector of topics that the node previously was subscribed to,
  * but is no longer interested in subscribing to.
  */
  virtual void UnregisterSubscriber(const std::vector<lri::TopicQuery>& topics);

  /**
   * Takes in a vector of topics (PublishTopic) that the node is going to
   * publish to, for advertising them and for replying to topic queries.
   */
  void RegisterPublisher(const std::vector<lri::TopicQuery>& topics);

  /**
   * Takes in a vector of topics (PublishTopic) that the node previously
   * was publishing to, but is no longer going to be publishing to.
   */
  void UnregisterPublisher(const std::vector<lri::TopicQuery>& topics);
 
 void SetCallback(DiscoveryCallback callback);

 protected:
  std::vector<lri::TopicQuery> publishing_topics_;
  std::vector<lri::TopicQuery> subscribed_topics_;
  std::vector<lri::TopicPublisher> topic_publishers_;

  DiscoveryCallback callback_;
  Thread* discovery_thread_;
  DatagramSocket* socket_;
};

}  // namespace lri

#endif  // SRC_DISCOVERY_DISCOVERY_UDP_H_
