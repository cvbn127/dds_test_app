#pragma once

#include "templated_publisher.h"
#include "templated_subscriber.h"

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastrtps/xmlparser/XMLProfileManager.h>

#include <fastrtps/attributes/ParticipantAttributes.h>

#include <future>
#include <iostream>

#include "interface/tools.h"

namespace dds_test_app
{
  template <typename PubSubType>
  class TemplatedTools : public ITools
  {
  public:
    TemplatedTools()                                 = default;
    TemplatedTools(TemplatedTools<PubSubType> &&rhs) = default;
    ~TemplatedTools() override
    {
      if (_participant != nullptr)
      {
        eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->delete_participant(_participant);
      }
    };
    bool init(const std::string &file_path, const std::string &profile_name, const std::string &pub_topic_name, const std::string &sub_topic_name,
              size_t pub_rate = 1) override
    {
      size_t domain_id = 0;

      std::cout << "Trying load xml profile file " << file_path << std::endl;
      const auto ret_code = eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->load_XML_profiles_file(file_path);
      if (eprosima::fastrtps::types::ReturnCode_t::RETCODE_ERROR == ret_code)
      {
        std::cerr << "Cannot load xml participant config " << file_path << std::endl;
        std::cerr << "Using default xml participant config." << std::endl;
        const auto ret_code_default_profiles = eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->load_profiles();
        if (eprosima::fastrtps::types::ReturnCode_t::RETCODE_ERROR == ret_code_default_profiles)
        {
          std::string err_msg = "Cannot load default XML profile!!! " + file_path;
          std::cerr << err_msg;
          return false;
        }
      }

      // participant = fastdds::dds::DomainParticipantFactory::get_instance()->create_participant_with_profile(domain_id,
      // profile_name); В 2.0.1 domain_id из профиля не используется при создании
      // Participant'а поэтому я вручную загружаю профиль и беру оттуда domain_id
      // надо будет убрать этот блок кода, когда загрузка domain_id из xml станет
      // возможной
      {
        eprosima::fastrtps::ParticipantAttributes attr;
        if (eprosima::fastrtps::xmlparser::XMLP_ret::XML_OK
            == eprosima::fastrtps::xmlparser::XMLProfileManager::fillParticipantAttributes(profile_name, attr))
        {
          domain_id = attr.domainId;
        }
        std::cout << "Trying to create Participant with profile " << profile_name << std::endl;
        _participant = eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->create_participant_with_profile(domain_id, profile_name);
      }

      if (_participant == nullptr)
      {
        std::cerr << "Cannot create Participant with profile " << profile_name << std::endl;
        std::cerr << "Trying to create with default qos settings..." << std::endl;
        _participant = eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->create_participant(
            domain_id, eprosima::fastdds::dds::PARTICIPANT_QOS_DEFAULT);
        if (_participant == nullptr)
        {
          std::string err_msg = "Failed to create participant with default qos settings!";
          std::cerr << err_msg << std::endl;
          return false;
        }
      }

      _subscriber = std::make_unique<TemplatedSubscriber<PubSubType>>(_participant);
      _publisher  = std::make_unique<TemplatedPublisher<PubSubType>>(_participant);

      bool result = _subscriber->init(sub_topic_name);
      if (!result)
      {
        return result;
      }

      result = _publisher->init(pub_rate, pub_topic_name);
      if (!result)
      {
        return result;
      }
      _subscriber->set_callback([this](const auto &msg) {
        // _publisher->publish(msg);
        _publisher->update_message(msg);
      });
      return result;
    };
    void run() override
    {
      auto future = std::async(std::launch::async, [this]() { _publisher->run(); });
      _subscriber->run();
    };

  private:
    eprosima::fastdds::dds::DomainParticipant *      _participant{nullptr};
    std::unique_ptr<TemplatedPublisher<PubSubType>>  _publisher{nullptr};
    std::unique_ptr<TemplatedSubscriber<PubSubType>> _subscriber{nullptr};
  };
} // namespace dds_test_app
