#pragma once

#include <chrono>
#include <functional>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>

#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>

#include <fastrtps/xmlparser/XMLProfileManager.h>

#include "interface/subscriber.h"

namespace dds_test_app
{

  template <typename PubSubType>
  void print_message(const typename PubSubType::type &msg)
  {
    (void)msg;
    return;
  }

  template <typename PubSubType>
  class TemplatedSubscriber : public ISubscriber
  {
  public:
    using message_type = typename PubSubType::type;
    TemplatedSubscriber(eprosima::fastdds::dds::DomainParticipant *participant = nullptr)
    : _participant{participant}, _subscriber{nullptr}, _topic{nullptr}, _reader{nullptr}, _type{nullptr} {};

    ~TemplatedSubscriber() override
    {
      if (_reader != nullptr)
      {
        _subscriber->delete_datareader(_reader);
      }
      if (_topic != nullptr)
      {
        _participant->delete_topic(_topic);
      }
      if (_subscriber != nullptr)
      {
        _participant->delete_subscriber(_subscriber);
      }

      if (should_delete_participant)
      {
        eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->delete_participant(_participant);
      }
    };

    void set_callback(std::function<void(const message_type &)> cb) { callback = cb; };

    bool init(const std::string &topic_name, const std::string &profile_name = "test-app-sub-profile") override
    {
      std::cout << "Initiating test subscriber " << topic_name << " " << _type.get_type_name() << std::endl;
      this->topic_name = topic_name;
      if (_participant == nullptr)
      {
        should_delete_participant = true;
        _participant              = eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->create_participant(
            0, eprosima::fastdds::dds::PARTICIPANT_QOS_DEFAULT);
      }

      _type.register_type(_participant);
      // _subscriber = _participant->create_subscriber_with_profile(profile_name, nullptr);
      // if (_subscriber == nullptr)
      // {
      //   std::cerr << "Cannot create subscriber with qos profile " << profile_name << std::endl;
      //   std::cerr << "Trying to create subscriber with default qos settings..." << std::endl;
      //   _subscriber = _participant->create_subscriber(eprosima::fastdds::dds::SUBSCRIBER_QOS_DEFAULT, nullptr);
      //   if (_subscriber == nullptr)
      //   {
      //     std::cerr << "Failed to create subscriber with default qos settings !!!" << std::endl;
      //     return false;
      //   }
      // }

      _subscriber = _participant->create_subscriber(eprosima::fastdds::dds::SUBSCRIBER_QOS_DEFAULT, nullptr);
      if (_subscriber == nullptr)
      {
        std::cerr << "Failed to create subscriber with default qos settings !!!" << std::endl;
        return false;
      }

      _topic = _participant->create_topic(topic_name, _type.get_type_name(), eprosima::fastdds::dds::TOPIC_QOS_DEFAULT);
      if (_topic == nullptr)
      {
        std::cerr << "Failed to create topic " << topic_name << " " << _type.get_type_name() << std::endl;
        return false;
      }

      this->topic_name = topic_name;

      _reader = _subscriber->create_datareader_with_profile(_topic, profile_name, &_listener);
      if (_reader == nullptr)
      {
        std::cerr << "Failed to create DataReader" << std::endl;
        return false;
      }

      std::cout << "Subscriber succesfully created " << topic_name << " " << _type.get_type_name() << std::endl;
      return true;
    };

    void run() override
    {
      std::cout << "Running. " << std::endl;
      bool should_stop = false;
      char c           = 0;
      while (!should_stop)
      {
        std::cin >> c;
        should_stop = c == 'q' ? true : false;
      }
    };

  private:
    eprosima::fastdds::dds::DomainParticipant *_participant;
    eprosima::fastdds::dds::Subscriber *       _subscriber;
    eprosima::fastdds::dds::Topic *            _topic;
    eprosima::fastdds::dds::DataReader *       _reader;
    eprosima::fastdds::dds::TypeSupport        _type;
    std::string                                topic_name{""};

    static std::function<void(const message_type &)> callback;

    bool should_delete_participant = false;
    bool is_type_registred         = false;

    class SubListener : public eprosima::fastdds::dds::DataReaderListener
    {
    public:
      SubListener() : _matched{0}, _samples{0} {};
      ~SubListener(){};
      void on_subscription_matched(eprosima::fastdds::dds::DataReader *reader, const eprosima::fastdds::dds::SubscriptionMatchedStatus &info) override
      {
        if (info.current_count_change == 1)
        {
          _matched = info.total_count;
          std::cout << "Subscriber matched." << std::endl;
        }
        else if (info.current_count_change == -1)
        {
          _matched = info.total_count;
          std::cout << "Subscriber unmatched." << std::endl;
        }
        else
        {
          std::cout << info.current_count_change
                    << " is not a valid value for SubscriptionMatchedStatus "
                       "current count change"
                    << std::endl;
        }
      };
      void on_data_available(eprosima::fastdds::dds::DataReader *reader) override
      {
        // Take data
        message_type msg{};

        std::cout << "new data message" << std::endl;

        if (reader->take_next_sample(&msg, &info) == ReturnCode_t::RETCODE_OK)
        {
          if (info.instance_state == eprosima::fastdds::dds::ALIVE)
          {
            ++_samples;
            std::cout << "Sample received, count=" << _samples << std::endl;
            auto now                = std::chrono::steady_clock::now();
            auto duration           = now - last_received_timepoint;
            last_received_timepoint = now;
            std::cout << "time since last message(ms): " << (std::chrono::duration_cast<std::chrono::milliseconds>(duration)).count() << std::endl;
            print_message<PubSubType>(msg);
            callback(msg);
          }
        }
      };
      eprosima::fastdds::dds::SampleInfo           info;
      int                                          _matched;
      int                                          _samples;
      static std::chrono::steady_clock::time_point last_received_timepoint;
      // std::chrono::steady_clock::now();
    } _listener;
  };

  template <typename PubSubType>
  std::chrono::steady_clock::time_point TemplatedSubscriber<PubSubType>::SubListener::last_received_timepoint = std::chrono::steady_clock::now();

  template <typename PubSubType>
  std::function<void(const typename PubSubType::type &)> TemplatedSubscriber<PubSubType>::callback = [](const typename PubSubType::type &msg) {};

} // namespace dds_test_app