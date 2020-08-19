#pragma once

#include "templated_publisher.h"
#include "templated_subscriber.h"

#include <fastrtps/Domain.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/xmlparser/XMLProfileManager.h>

#include <future>
#include <iostream>

namespace dds_test_app {
template <typename PubSubType> class TemplatedTools {
public:
  TemplatedTools() = default;
  TemplatedTools(TemplatedTools<PubSubType> &&rhs) = default;
  ~TemplatedTools() {
    if (participant != nullptr) {
      eprosima::fastrtps::Domain::removeParticipant(participant);
    }
  };
  bool init(const std::string &file_path, const std::string &profile_name,
            const std::string &pub_topic_name,
            const std::string &sub_topic_name, size_t pub_rate = 1) {
    if (eprosima::fastrtps::xmlparser::XMLP_ret::XML_OK !=
        eprosima::fastrtps::xmlparser::XMLProfileManager::loadXMLFile(
            file_path)) {
      std::cout << "cannot load xml " << file_path << std::endl;
      return false;
    }
    participant = eprosima::fastrtps::Domain::createParticipant(profile_name);

    subscriber = std::make_unique<TemplatedSubscriber<PubSubType>>(participant);
    publisher = std::make_unique<TemplatedPublisher<PubSubType>>(participant);

    bool result = subscriber->init(sub_topic_name);
    if (!result) {
      return result;
    }

    result = publisher->init(pub_rate, pub_topic_name);
    if (!result) {
      return result;
    }
    subscriber->set_callback([this](const auto &msg) {
      // publisher->publish(msg);
      publisher->update_message(msg);
    });
    return result;
  };
  void run() {
    auto future =
        std::async(std::launch::async, [this]() { publisher->run(); });
    subscriber->run();
  };

private:
  eprosima::fastrtps::Participant *participant = nullptr;
  std::unique_ptr<TemplatedPublisher<PubSubType>> publisher;
  std::unique_ptr<TemplatedSubscriber<PubSubType>> subscriber;
};
} // namespace dds_test_app
