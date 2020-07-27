#include "PoseArrayTools.h"

#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/Domain.h>
#include <fastrtps/xmlparser/XMLProfileManager.h>
#include <fastrtps/xmlparser/XMLProfileManager.h>

#include <iostream>
#include <future>

using namespace eprosima;
using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;
using namespace eprosima::fastrtps::xmlparser;

PoseArrayTools::~PoseArrayTools()
{
    if (participant != nullptr)
    {
        Domain::removeParticipant(participant);
    }
}

bool PoseArrayTools::init(const std::string& file_path, const std::string &profile_name, const std::string &sub_topic_name, const std::string &pub_topic_name)
{
    std::cout << "sub topic " << sub_topic_name << std::endl;
    std::cout << "pub topic " << pub_topic_name << std::endl;
    if (XMLP_ret::XML_OK != XMLProfileManager::loadXMLFile(file_path))
    {
        std::cout << "cannot load xml " << file_path << std::endl; 
        return false;
    }
    participant = Domain::createParticipant(profile_name);

    subscriber = std::make_unique<PoseArraySubscriber>(participant);
    publisher = std::make_unique<PoseArrayPublisher>(participant);

    bool result = subscriber->init(sub_topic_name);
    if (!result)
    {
        return result;
    }

    result = publisher->init(1, pub_topic_name);
    if (!result)
    {
        return result;
    }
    subscriber->set_callback([this](const auto &msg) {
        //auto now = std::chrono::steady_clock::now();
        //auto duration = now - last_received_timepoint;
        //last_received_timepoint = now;
        //std::cout << "time since last message(ms): " << (std::chrono::duration_cast<std::chrono::milliseconds>(duration)).count() << std::endl;
        // publisher->publish(msg);
        publisher->update_message(msg);
    });    
    return result;
}

void PoseArrayTools::run()
{
    auto future = std::async(std::launch::async, [this](){ publisher->run(); });
    subscriber->run();
}
