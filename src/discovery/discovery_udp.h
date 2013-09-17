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
   * Takes in a vector of topics that the node is interested in, and
   * subsequently calls the registered callback with a list of known publishers.
   */
  virtual void QueryPublishers(const std::vector<lri::TopicUri>& topics);

  /**
    * Takes in a vector of topics that the node is publishing to, and
    * subsequentlya calls the registered callback with a list of known
    * subscribers.
    */
  virtual void QuerySubscribers(const std::vector<lri::TopicUri>& topics);

  /**
  * Takes in a vector of topics that the node is subscribing to, for querying
  * their publishers and for keeping track of their publishers.
  */
  virtual void RegisterSubscriber(const std::vector<lri::TopicUri>& topics);

  /**
  * Takes in a vector of topics that the node previously was subscribed to,
  * but is no longer interested in subscribing to.
  */
  virtual void UnregisterSubscriber(const std::vector<lri::TopicUri>& topics);

  /**
   * Takes in a vector of topics (PublishTopic) that the node is going to
   * publish to, for advertising them and for replying to topic queries.
   */
  virtual void RegisterPublisher(const std::vector<lri::TopicUri>& topics);

  /**
   * Takes in a vector of topics (PublishTopic) that the node previously
   * was publishing to, but is no longer going to be publishing to.
   */
  virtual void UnregisterPublisher(const std::vector<lri::TopicUri>& topics);

  /**
   * Defines a callback function type that will be called when new publishers or
   * subscribers are discovered for topics of interest.
   */
  typedef void (*DiscoveryCallback)(
      const std::vector<lri::TopicUri>& topics, void* context);

  /**
   * Register a callback to call when new publishers are discovered for topics
   * of interest.
   */
  virtual void SetPublishersCallback(DiscoveryCallback callback, void* context);
  
  /**
   * Register a callback to call when new subscribers are discovered for topics
   * of interest.
   */
  virtual void SetSubscribersCallback(
      DiscoveryCallback callback, void* context);
  
  /**
   * Register a callback to call when an error occurs.
   */
  // TODO: Define an error callback interface
  virtual void SetErrorCallback(void* error, void* context);

 protected:
  std::vector<lri::TopicQuery> publishing_topics_;
  std::vector<lri::TopicQuery> subscribed_topics_;
  std::vector<lri::TopicPublisher> topic_publishers_;

  DiscoveryCallback publishers_callback_;
  DiscoveryCallback subscribers_callback_;
  void* publishers_callback_context_;
  void* subscribers_callback_context_;
  Thread* discovery_thread_;
  DatagramSocket* socket_;
};

}  // namespace lri

#endif  // SRC_DISCOVERY_DISCOVERY_UDP_H_
