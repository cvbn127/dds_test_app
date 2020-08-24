#pragma once

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>

#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/qos/DataWriterQos.hpp>
#include <fastdds/dds/publisher/qos/PublisherQos.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

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
    TemplatedPublisher(eprosima::fastdds::dds::DomainParticipant *participant)
    : _participant{participant}, _publisher{nullptr}, _topic{nullptr}, _writer{nullptr}, _type{new PubSubType{}} {};

    ~TemplatedPublisher() override
    {
      if (_writer != nullptr)
      {
        _publisher->delete_datawriter(_writer);
      }
      if (_publisher != nullptr)
      {
        _participant->delete_publisher(_publisher);
      }
      if (_topic != nullptr)
      {
        _participant->delete_topic(_topic);
      }

      if (should_delete_participant)
      {
        eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->delete_participant(_participant);
      }
    };
    bool init(int rate, const std::string &topic_name, const std::string &profile_name = "test_app_pub_profile") override
    {
      std::cout << "Initiating test publisher " << topic_name << " " << _type.get_type_name() << std::endl;
      _rate            = rate;
      this->topic_name = topic_name;

      if (_participant == nullptr)
      {
        should_delete_participant = true;
        _participant              = eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->create_participant(
            0, eprosima::fastdds::dds::PARTICIPANT_QOS_DEFAULT);
        if (_participant == nullptr)
        {
          std::string err_msg = "Failed to create participant with default qos settings!";
          std::cerr << err_msg << std::endl;
          return false;
        }
      }

      _type.register_type(_participant);

      // _publisher = _participant->create_publisher_with_profile(profile_name, nullptr);
      // if (nullptr == _publisher)
      // {
      //   std::cerr << "Cannot create publisher with profile " << profile_name << std::endl;
      //   std::cerr << "Trying to create publisher with default qos settings..." << std::endl;
      //   _publisher = _participant->create_publisher(eprosima::fastdds::dds::PUBLISHER_QOS_DEFAULT, nullptr);
      //   if (nullptr == _publisher)
      //   {
      //     std::cerr << "Failed to create publisher with default qos settings !!!" << std::endl;
      //     return false;
      //   }
      // }
      _publisher = _participant->create_publisher(eprosima::fastdds::dds::PUBLISHER_QOS_DEFAULT, nullptr);
      if (nullptr == _publisher)
      {
        std::cerr << "Failed to create publisher with default qos settings !!!" << std::endl;
        return false;
      }

      _topic = _participant->create_topic(topic_name, _type.get_type_name(), eprosima::fastdds::dds::TOPIC_QOS_DEFAULT);
      if (_topic == nullptr)
      {
        std::cerr << "Failed to create topic " << topic_name << " " << _type.get_type_name() << std::endl;
        return false;
      }

      _writer = _publisher->create_datawriter_with_profile(_topic, profile_name, &_listener);
      if (_writer == nullptr)
      {
        std::cerr << "Failed to create DataWriter with profile " << profile_name << std::endl;
        std::cerr << "Trying to create default reliable DataWriter..." << std::endl;
        _writer = _publisher->create_datawriter(_topic, eprosima::fastdds::dds::DATAWRITER_QOS_DEFAULT, &_listener);
        if (_writer == nullptr)
        {
          std::cerr << "Failed to create default reliable DataWriter..." << std::endl;
          return false;
        }
      }

      std::cout << "Publisher succesfully created " << topic_name << " " << _type.get_type_name() << std::endl;
      return true;
    };
    void run() override
    {
      size_t sleep_time = (1.0 / _rate) * 1000.0;
      latest_message    = initialize_msg<PubSubType>();
      int msgsent       = 0;
      do
      {
        while (_listener._matched == 0)
        {
          std::this_thread::sleep_for(std::chrono::milliseconds(250)); // Sleep 250 ms
        }

        _writer->write(&latest_message);
        ++msgsent;
        std::cout << "Sending sample, count=" << msgsent << "" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
      } while (true);
    };
    void publish(const message_type &msg)
    {
      std::cout << "publish once" << std::endl;
      _writer->write(&msg);
    };
    void update_message(const message_type &msg) { latest_message = msg; };

  private:
    eprosima::fastdds::dds::DomainParticipant *_participant;
    eprosima::fastdds::dds::Publisher *        _publisher;
    eprosima::fastdds::dds::Topic *            _topic;
    eprosima::fastdds::dds::DataWriter *       _writer;
    eprosima::fastdds::dds::TypeSupport        _type;

    int         _rate;
    std::string topic_name;
    bool        should_delete_participant = false;
    bool        is_type_registred         = false;

    message_type latest_message;

    class PubListener : public eprosima::fastdds::dds::DataWriterListener
    {
    public:
      PubListener() : _matched(0){};
      ~PubListener(){};
      void on_publication_matched(eprosima::fastdds::dds::DataWriter *writer, const eprosima::fastdds::dds::PublicationMatchedStatus &info) override
      {
        if (info.current_count_change == 1)
        {
          _matched = info.total_count;
          std::cout << "Publisher matched." << std::endl;
        }
        else if (info.current_count_change == -1)
        {
          _matched = info.total_count;
          std::cout << "Publisher unmatched." << std::endl;
        }
        else
        {
          std::cout << info.current_count_change
                    << " is not a valid value for PublicationMatchedStatus "
                       "current count change"
                    << std::endl;
        }
      };
      int _matched;
    } _listener;
  };
} // namespace dds_test_app