#include "topic_query.pb.h"
#include "topic_publisher.pb.h"
#include "topic_notice.pb.h"

#ifndef LRI_INCLUDE_DISCOVERY_H_
#define LRI_INCLUDE_DISCOVERY_H_

namespace lri {

/**
 * The discovery module is responsible for determining which
 * nodes and topics are available and how to connect to them
 * using various transport layers.
 */
class Discovery {
 public:
  Discovery();
  virtual ~Discovery();

  /**
   * Takes in a vector of topics that the node is interested in,
   * and returns a vector of publishers that are publishing to those topics.
   */
  virtual void QueryPublishers(
      const std::vector<lri::TopicQuery>& topics,
      std::vector<lri::TopicPublisher>* publishers) = 0;

  /**
    * Takes in a vector of topics that the node is publishing to,
    * and returns a vector of subscribers that are publishing to those topics.
    */
  virtual void QuerySubscribers(
    const std::vector<lri::TopicQuery>& topics,
    std::vector<lri::TopicPublisher>* publishers) = 0;

  /**
  * Takes in a vector of topics that the node is subscribing to, for querying
  * their publishers and for keeping track of their publishers.
  */
  virtual void RegisterSubscriber(const std::vector<lri::TopicQuery>& topics)
      = 0;

  /**
  * Takes in a vector of topics that the node previously was subscribed to,
  * but is no longer interested in subscribing to.
  */
  virtual void UnregisterSubscriber(const std::vector<lri::TopicQuery>& topics)
      = 0;

  /**
   * Takes in a vector of topics (PublishTopic) that the node is going to
   * publish to, for advertising them and for replying to topic queries.
   */
  virtual void RegisterPublisher(const std::vector<lri::TopicQuery>& topics)
      = 0;

  /**
   * Takes in a vector of topics (PublishTopic) that the node previously
   * was publishing to, but is no longer going to be publishing to.
   */
  virtual void UnregisterPublisher(const std::vector<lri::TopicQuery>& topics)
      = 0;

  /**
   * Defines a callback function that will be called when a new publisher is
   * discovered for a subscribed topic.
   */
  typedef void (*DiscoveryCallback)(
      const std::vector<lri::TopicQuery>& topics, void* context);

  virtual void SetCallback(DiscoveryCallback callback) = 0;
};

}  // namespace lri

#endif  // LRI_INCLUDE_DISCOVERY_H_
