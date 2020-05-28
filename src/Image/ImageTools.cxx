#include "ImageTools.h"

#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/Domain.h>
#include <fastrtps/xmlparser/XMLProfileManager.h>
#include <fastrtps/xmlparser/XMLProfileManager.h>

#include <iostream>

using namespace eprosima;
using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;
using namespace eprosima::fastrtps::xmlparser;

ImageTools::~ImageTools()
{
    if (participant != nullptr)
    {
        Domain::removeParticipant(participant);
    }
}

bool ImageTools::init(const std::string& file_path, const std::string &profile_name)
{
    if (XMLP_ret::XML_OK != XMLProfileManager::loadXMLFile(file_path))
    {
        std::cout << "cannot load xml " << file_path << std::endl; 
        return false;
    }
    participant = Domain::createParticipant(profile_name);

    subscriber = std::make_unique<ImageSubscriber>(participant);
    publisher = std::make_unique<ImagePublisher>(participant);

    bool result = subscriber->init();
    if (!result)
    {
        return result;
    }

     result = publisher->init(1);
     if (!result)
     {
         return result;
     }
     subscriber->set_callback([this](const auto &msg) {publisher->publish(msg);});    
    return result;
}

void ImageTools::run()
{
    subscriber->run();
}
