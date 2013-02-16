#include "topic_query.h"
#include "topic_publisher.h"
#include "topic_notice.h"

#ifndef LRI_INCLUDE_DISCOVERY_H_
#define LRI_INCLUDE_DISCOVERY_H_

namespace lri {

/**
 * The discovery module is responsible for determining which
 * nodes and topics are available and how to connect to them
 * using various transport layers.
 */
class Discovery {
  
  /**
   * Takes in a vector of topics (QueryTopic) that the node is interested in, 
   * and returns a vector of publishers that are publishing to those topics.
   */
  Query(const std::vector<QueryTopic>& topics, 
        std::vector<PublishTopic>* publishers);

  /**
   * Takes in a vector of topics (PublishTopic) that the node is going to 
   * publish to, for advertising them and for replying to topic queries.
   */
  Provide(const std::vector<PublishTopic>& topics); 
  
  /**
   * Takes in a vector of topics (PublishTopic) that the node previously
   * was publishing to, but is no longer going to be publishing to.
   */
  UnProvide(const std::vector<PublishTopic>& topics); 
};

}  // namespace lri

#endif  // LRI_INCLUDE_DISCOVERY_H_
