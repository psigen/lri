#include "discovery.h"
#include "gtest/gtest.h"

class DiscoveryTest : public testing::Test {
 protected:
  virtual void SetUp() = 0;
  virtual void TearDown() = 0;

  // Declares the variables your tests want to use.
  lri::Discovery discovery_provider_;
  lri::Discovery discovery_client_;
};

TEST(DiscoveryTest, Initialization)
{
  const UdpDiscovery discovery;
  // TODO(pkv): Fill in some checks about the default params for UDP discovery
}

TEST(DiscoveryTest, Query)
{
  lri::TopicQuery query;
  
  // Make the provider register for a topic
  discovery_provider_.Register(query);

  // Have the client query for the same topic
  std::vector<TopicPublisher> publishers;
  discovery_client_.Query(query, &publishers);

  // The client should see the provider.
  // TODO(pkv): What is the mechanism for seeing a provider?
}

TEST(DiscoveryTest, Register)
{
  
}

TEST(DiscoveryTest, Unregister)
{
  
}

TEST(DiscoveryTest, SetCallback)
{
  
}

TEST(DiscoveryTest, ChangeCallback)
{
  
}

TEST(DiscoveryTest, ClearCallback)
{
  
}
