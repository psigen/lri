namespace lri
{
  class LRI 
  {
 public:
    LRI(std::string network);
    ~LRI();
    
    /**
     * Creates a publisher object which pushes events to a given topic.
     */
    template<typename MessageType>
        Publisher<MessageType> publisher(std::string topic);
    
    /**
     * Creates a subscriber object which listens for changes on a given topic.
     */
    template<typename MessageType>
        Subscriber<MessageType> subscriber(std::string topic);
    template<typename MessageType>
        Subscriber<MessageType> subscriber(std::string topic, SubscriberCallback<MessageType> callback);
    
    /**
     * Creates a monitored object for which changes are propagated to subscribers.
     */
    template<typename MessageType>
        Monitor<MessageType> share(std::string topic);
    template<typename MessageType>
        Monitor<MessageType> share(std::string topic, double maxHz = 0.0);
    
    /**
     * Creates a proxy state that replicates changes from the subscriber.
     */
    template<typename MessageType>
        Proxy<MessageType> replicate(std::string topic);
    template<typename MessageType>
        Proxy<MessageType> replicate(std::string topic, double maxHz = 0.0);

    /**
     * Processes messages and callbacks on the current foreground thread.
     */
    void spin(void);

    /**
     * Starts a background thread pool that will process messages and callbacks.
     */
    void start(void);

    /**
     * Stops a background thread pool to process messages and callbacks.
     */
    void stop(void);

    /**
     * Returns whether the background thread pool is running.
     */
    bool isRunning(void);
  };

  /**
   * A subscriber listens to a particular topic and calls its callback function when the
   * topic gets a new event.
   */
  template<typename MessageType> 
      class Subscriber
  {
 public:
    void listen(SubscriberCallback callback);
    void shutdown(void);

    /** Defines a callback function that will receive this message type */
    typedef void (*SubscriberCallback)(Subscriber<MessageType> &source, const MessageType &message);
  };
  
  /**
   * A publisher is connected to a particular topic and sends out an event when it
   * is called with a message.
   */
  template<typename MessageType>
      class Publisher
  {
 public:
    void publish(MessageType message);
    void shutdown(void);
  };

  /**
   * A monitor wraps a given message, turning it into a shared state.  It monitors changes in
   * the object, and sends state updates to subscribers when commit() is called, or
   * automatically at some maximum fixed rate.
   */
  template<typename MessageType>
      class Monitor
  {
 public:
    void setMaxRate(double Hz);
    void commit(void);
    void shutdown(void);
  };

  /**
   * A proxy wraps a given message, turning it into shared state.  It provides const-access
   * to message fields, and updates them automatically from the publisher either when
   * refresh is called or at some maximum fixed rate.
   */
  template<typename MessageType>
      class Proxy
  {
 public:
    void setMaxRate(double Hz);
    void commit(void);
    void shutdown(void);
  };
}
