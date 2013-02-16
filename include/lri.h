#include <string>

#ifndef LRI_INCLUDE_LRI_H_
#define LRI_INCLUDE_LRI_H_

namespace lri {
class LRI {
 public:
  LRI(std::string group);
  ~LRI();
  
  /**
   * Creates a publisher object which pushes events to a given topic.
   */
  template<typename MessageType>
      Publisher<MessageType> Publish(const std::string& topic);
  
  /**
   * Creates a subscriber object which listens for changes on a given topic.
   */
  template<typename MessageType>
      Subscriber<MessageType> Subscribe(const std::string& topic);
  template<typename MessageType>
      Subscriber<MessageType> Subscribe(
          const std::string& topic, SubscriberCallback<MessageType> callback);
  
  /**
   * Creates a monitored object for which changes are propagated to
   * subscribers. Used for publishing the state of the monitored object. For
   * example, this could be used to monitor a joint angle, and when the value
   * of the joint angle changed, the change would be propagated to the 
   * subscribers.
   */
  template<typename MessageType>
      Monitor<MessageType> Share(const std::string& topic);
  template<typename MessageType>
      Monitor<MessageType> Share(const std::string& topic, double max_hz);
  
  /**
   * Creates a proxy state that replicates changes from the publisher.
   */
  template<typename MessageType>
      Proxy<MessageType> Replicate(const std::string& topic);
  template<typename MessageType>
      Proxy<MessageType> Replicate(const std::string& topic, double max_hz);

  /**
   * Processes messages and callbacks on the current foreground thread.
   */
  void Update(void);

  /**
   * Starts a background thread pool that will process messages and callbacks.
   */
  void Start(void);

  /**
   * Stops a background thread pool to process messages and callbacks.
   */
  void Stop(void);

  /**
   * Returns whether the background thread pool is running.
   */
  bool IsRunning(void);

  /**
   * Returns the LRI group URI that this LRI instance is using.
   */
  const char& group();
};

/**
 * A subscriber listens to a particular topic and calls its callback function when the
 * topic gets a new event.
 */
template<typename MessageType> class Subscriber {
 public:
  void Listen(SubscriberCallback callback);
  void Shutdown(void);
  const LRI& lri();

  /** Defines a callback function that will receive this message type */
  typedef void (*SubscriberCallback)(const Subscriber<MessageType>& source, 
      const MessageType& message);
};

/**
 * A publisher is connected to a particular topic and sends out an event when it
 * is called with a message.
 */
template<typename MessageType> class Publisher {
 public:
  void Publish(const MessageType& message);
  void Shutdown(void);
  const LRI& lri();
};

/**
 * A monitor wraps a given message, turning it into a shared state.  It monitors changes in
 * the object, and sends state updates to subscribers when commit() is called, or
 * automatically at some maximum fixed rate.
 */
template<typename MessageType> class Monitor {
 public:
  void SetMaxRate(double Hz);
  void Commit(void);
  void Shutdown(void);
  const LRI& lri();
};

/**
 * A proxy wraps a given message, turning it into shared state.  It provides const-access
 * to message fields, and updates them automatically from the publisher either when
 * refresh is called or at some maximum fixed rate.
 */
template<typename MessageType> class Proxy {
 public:
  void SetMaxRate(double Hz);
  void Shutdown(void);
  const LRI& lri();
};

}  // namespace lri

#endif  // LRI_INCLUDE_LRI_H_

