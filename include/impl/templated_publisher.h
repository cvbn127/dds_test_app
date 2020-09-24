#pragma once

#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/participant/Participant.h>
#include <fastrtps/publisher/Publisher.h>
#include <fastrtps/publisher/PublisherListener.h>

#include <fastrtps/Domain.h>
#include <fastrtps/xmlparser/XMLProfileManager.h>

#include <chrono>
#include <thread>

#include "interface/publisher.h"

namespace dds_test_app
{
  template <typename PubSubType>
  typename PubSubType::type initialize_msg()
  {
    using msg_type = typename PubSubType::type;
    msg_type default_msg{};
    return default_msg;
  };

  template <typename PubSubType>
  class TemplatedPublisher : public IPublisher
  {
  public:
    using message_type = typename PubSubType::type;
    TemplatedPublisher() : TemplatedPublisher(nullptr){};
    TemplatedPublisher(eprosima::fastrtps::Participant *participant) : mp_participant(participant), mp_publisher(nullptr){};
    ~TemplatedPublisher() override
    {
      if (is_type_registred)
      {
        std::cout << "unregister type" << std::endl;
        eprosima::fastrtps::Domain::unregisterType(mp_participant, myType.getName());
      }
      if (should_delete_participant)
      {
        eprosima::fastrtps::Domain::removeParticipant(mp_participant);
      }
    };
    bool init(int rate, const std::string &topic_name, const std::string &profile_name = "test-app-pub-profile") override
    {
      std::cout << "Initiating test publisher " << topic_name << " " << myType.getName() << std::endl;
      m_rate = rate;
      if (mp_participant == nullptr)
      {
        should_delete_participant = true;
        eprosima::fastrtps::ParticipantAttributes PParam;
        PParam.rtps.setName("Participant_publisher"); // You can put here the name you want
        PParam.rtps.builtin.domainId = 120;
        mp_participant  = eprosima::fastrtps::Domain::createParticipant(PParam);
      }

      // Register the type
      eprosima::fastrtps::TopicDataType *data_type = nullptr;
      if (!eprosima::fastrtps::Domain::getRegisteredType(mp_participant, myType.getName(), &data_type))
      {
        eprosima::fastrtps::Domain::registerType(mp_participant, static_cast<eprosima::fastrtps::TopicDataType *>(&myType));
        is_type_registred = true;
      }
      else
      {
        std::cout << "already registred " << myType.getName() << std::endl;
      }

      eprosima::fastrtps::PublisherAttributes publisher_att;
      if (eprosima::fastrtps::xmlparser::XMLP_ret::XML_ERROR
          == eprosima::fastrtps::xmlparser::XMLProfileManager::fillPublisherAttributes(profile_name, publisher_att))
      {
        std::cerr << "Problem loading profile '" << profile_name << "'"
                  << ". Using default values." << std::endl;
        publisher_att.topic.topicKind        = eprosima::fastrtps::rtps::NO_KEY;
        publisher_att.historyMemoryPolicy    = eprosima::fastrtps::rtps::PREALLOCATED_WITH_REALLOC_MEMORY_MODE;
        publisher_att.qos.m_publishMode.kind = eprosima::fastrtps::
          PublishModeQosPolicyKind::ASYNCHRONOUS_PUBLISH_MODE;
      }
      publisher_att.topic.topicDataType = myType.getName(); // This type MUST be registered
      publisher_att.topic.topicName     = topic_name;

      mp_publisher = eprosima::fastrtps::Domain::createPublisher(mp_participant, publisher_att,
                                                                 static_cast<eprosima::fastrtps::PublisherListener *>(&m_listener));

      if (mp_publisher == nullptr)
      {
        return false;
      }

      std::cout << "Publisher succesfully created " << topic_name << " " << myType.getName() << std::endl;
      return true;
    };
    void run() override
    {
      size_t sleep_time = (1.0 / m_rate) * 1000.0;
      latest_message    = initialize_msg<PubSubType>();
      int msgsent       = 0;
      do
      {
        while (m_listener.n_matched == 0)
        {
          std::this_thread::sleep_for(std::chrono::milliseconds(250)); // Sleep 250 ms
        }

        mp_publisher->write(&latest_message);
        ++msgsent;
        std::cout << "Sending sample, count=" << msgsent << "" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
      } while (true);
    };
    void publish(const message_type &msg)
    {
      mp_publisher->write(const_cast<message_type *>(&msg));
    };
    void update_message(const message_type &msg) { latest_message = msg; };

  private:
    eprosima::fastrtps::Participant *mp_participant;
    eprosima::fastrtps::Publisher *  mp_publisher;

    int  m_rate;
    bool should_delete_participant = false;
    bool is_type_registred         = false;

    message_type latest_message;

    class PubListener : public eprosima::fastrtps::PublisherListener
    {
    public:
      PubListener() : n_matched(0){};
      ~PubListener(){};
      void onPublicationMatched(eprosima::fastrtps::Publisher *pub, eprosima::fastrtps::rtps::MatchingInfo &info)
      {
        (void)pub;

        if (info.status == eprosima::fastrtps::rtps::MATCHED_MATCHING)
        {
          n_matched++;
          std::cout << "Publisher matched" << std::endl;
        }
        else
        {
          n_matched--;
          std::cout << "Publisher unmatched" << std::endl;
        }
      };
      int n_matched;
    } m_listener;
    PubSubType myType;
  };
} // namespace dds_test_app