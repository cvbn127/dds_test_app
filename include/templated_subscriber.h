#pragma once

#include <chrono>
#include <fastrtps/Domain.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastrtps/fastrtps_fwd.h>
#include <fastrtps/subscriber/SampleInfo.h>
#include <fastrtps/subscriber/Subscriber.h>
#include <fastrtps/subscriber/SubscriberListener.h>
#include <fastrtps/xmlparser/XMLProfileManager.h>
#include <functional>

namespace dds_test_app {

template <typename PubSubType>
void print_message(const typename PubSubType::type &msg) {
  (void)msg;
  return;
}

template <typename PubSubType> class TemplatedSubscriber {
public:
  using message_type = typename PubSubType::type;
  TemplatedSubscriber(eprosima::fastrtps::Participant *participant = nullptr)
      : mp_participant(participant), mp_subscriber(nullptr){};

  ~TemplatedSubscriber() {
    if (is_type_registred) {
      eprosima::fastrtps::Domain::unregisterType(mp_participant,
                                                 myType.getName());
    }
    if (should_delete_participant) {
      eprosima::fastrtps::Domain::removeParticipant(mp_participant);
    }
  };

  void set_callback(std::function<void(const message_type &)> cb) {
    callback = cb;
  };

  bool init(const std::string &topic_name,
            const std::string &profile_name = "test-app-sub-profile") {
    std::cout << "Initiating test subscriber " << topic_name << " " << myType.getName() << std::endl;
    if (mp_participant == nullptr) {
      should_delete_participant = true;
      eprosima::fastrtps::ParticipantAttributes PParam;
      PParam.rtps.setName(
          "Participant_subscriber"); // You can put the name you want
      PParam.domainId = 120;
      mp_participant = eprosima::fastrtps::Domain::createParticipant(PParam);
    }
    eprosima::fastdds::dds::TopicDataType *data_type = nullptr;
    if (!eprosima::fastrtps::Domain::getRegisteredType(
            mp_participant, myType.getName(), &data_type)) {
      eprosima::fastrtps::Domain::registerType(
          mp_participant,
          static_cast<eprosima::fastdds::dds::TopicDataType *>(&myType));
      is_type_registred = true;
    } else {
      std::cout << "already registred " << myType.getName() << std::endl;
    }

    eprosima::fastrtps::SubscriberAttributes subscriber_att;
    if (eprosima::fastrtps::xmlparser::XMLP_ret::XML_ERROR ==
        eprosima::fastrtps::xmlparser::XMLProfileManager::
            fillSubscriberAttributes(profile_name, subscriber_att)) {
      std::cerr << "Problem loading profile '" << profile_name << "'"
                << ". Using default values." << std::endl;
    }
    subscriber_att.topic.topicDataType =
        myType.getName(); // Must be registered before the creation of the
                          // subscriber
    subscriber_att.historyMemoryPolicy =
        eprosima::fastrtps::rtps::PREALLOCATED_WITH_REALLOC_MEMORY_MODE;
    subscriber_att.topic.topicKind = eprosima::fastrtps::rtps::NO_KEY;
    subscriber_att.topic.topicName = topic_name;

    mp_subscriber = eprosima::fastrtps::Domain::createSubscriber(
        mp_participant, subscriber_att,
        static_cast<eprosima::fastrtps::SubscriberListener *>(&m_listener));
    if (mp_subscriber == nullptr) {
      return false;
    }
    SubListener::last_received_timepoint = std::chrono::steady_clock::now();
    std::cout << "Subscriber succesfully created " << topic_name << " " << myType.getName() << std::endl;
    return true;
  };

  void run() {
    std::cout << "Running. " << std::endl;
    bool should_stop = false;
    char c = 0;
    while (!should_stop) {
      std::cin >> c;
      should_stop = c == 'q' ? true : false;
    }
  };

private:
  eprosima::fastrtps::Participant *mp_participant;
  eprosima::fastrtps::Subscriber *mp_subscriber;
  static std::function<void(const message_type &)> callback;

  bool should_delete_participant = false;
  bool is_type_registred = false;

  class SubListener : public eprosima::fastrtps::SubscriberListener {
  public:
    SubListener() : n_matched(0), n_msg(0){};
    ~SubListener(){};
    void onSubscriptionMatched(eprosima::fastrtps::Subscriber *sub,
                               eprosima::fastrtps::rtps::MatchingInfo &info) {
      (void)sub;

      if (info.status == eprosima::fastrtps::rtps::MATCHED_MATCHING) {
        n_matched++;
        std::cout << "Subscriber matched" << std::endl;
      } else {
        n_matched--;
        std::cout << "Subscriber unmatched" << std::endl;
      }
    };
    void onNewDataMessage(eprosima::fastrtps::Subscriber *sub) {
      // Take data
      message_type msg{};

      std::cout << "new data message" << std::endl;

      if (sub->takeNextData(&msg, &m_info)) {
        if (m_info.sampleKind == eprosima::fastrtps::rtps::ALIVE) {
          // Print your structure data here.
          ++n_msg;
          std::cout << "Sample received, count=" << n_msg << std::endl;
          auto now = std::chrono::steady_clock::now();
          auto duration = now - last_received_timepoint;
          last_received_timepoint = now;
          std::cout << "time since last message(ms): "
                    << (std::chrono::duration_cast<std::chrono::milliseconds>(
                            duration))
                           .count()
                    << std::endl;
          print_message<PubSubType>(msg);
          callback(msg);
        }
      }
    };
    eprosima::fastrtps::SampleInfo_t m_info;
    int n_matched;
    int n_msg;
    static std::chrono::steady_clock::time_point last_received_timepoint;
    // std::chrono::steady_clock::now();
  } m_listener;
  PubSubType myType;
};

template <typename PubSubType>
std::chrono::steady_clock::time_point
    TemplatedSubscriber<PubSubType>::SubListener::last_received_timepoint =
        std::chrono::steady_clock::now();

template <typename PubSubType>
std::function<void(const typename PubSubType::type &)>
    TemplatedSubscriber<PubSubType>::callback =
        [](const typename PubSubType::type &msg) {};

} // namespace dds_test_app