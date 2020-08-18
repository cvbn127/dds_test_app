// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file ObjectsArrayPublisher.cpp
 * This file contains the implementation of the publisher functions.
 *
 * This file was generated by the tool fastcdrgen.
 */


#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/publisher/Publisher.h>
#include <fastrtps/attributes/PublisherAttributes.h>

#include <fastrtps/Domain.h>
#include <fastrtps/xmlparser/XMLProfileManager.h>

#include <thread>
#include <chrono>

#include "ObjectsArrayPublisher.h"

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;
using namespace eprosima::fastrtps::xmlparser;
using eprosima::fastdds::dds::TopicDataType;

ObjectsArrayPublisher::ObjectsArrayPublisher(eprosima::fastrtps::Participant *participant) : mp_participant(participant), mp_publisher(nullptr) {}

ObjectsArrayPublisher::~ObjectsArrayPublisher() 
{	
    if (is_type_registred)
    {
        std::cout << "unregister type" << std::endl;
        Domain::unregisterType(mp_participant, myType.getName());
    }
    if (should_delete_participant) 
    {
        Domain::removeParticipant(mp_participant);
    }
}

bool ObjectsArrayPublisher::init(int rate, const std::string &publisher_topic_name, const std::string &profile_name)
{
    m_rate = rate;
    // Create RTPSParticipant

    if(mp_participant == nullptr)
    {
        should_delete_participant = true;
        ParticipantAttributes PParam;
        PParam.rtps.setName("Participant_publisher");  //You can put here the name you want
        PParam.domainId = 120;
        mp_participant = Domain::createParticipant(PParam);
    }

    //Register the type
    TopicDataType *data_type = nullptr;
    if (!Domain::getRegisteredType(mp_participant, myType.getName(), &data_type))
    {
        Domain::registerType(mp_participant, static_cast<TopicDataType*>(&myType));
        is_type_registred = true;
    }
    else 
    {
        std::cout << "already registred " << myType.getName() << std::endl;
    }

    // Create Publisher

    PublisherAttributes publisher_att;
    if ( XMLP_ret::XML_ERROR == XMLProfileManager::fillPublisherAttributes(profile_name, publisher_att))
    {
        std::cerr << "Problem loading profile '" << profile_name << "'" << ". Using default values." << std::endl;
        publisher_att.topic.topicKind = NO_KEY;
        publisher_att.historyMemoryPolicy = PREALLOCATED_WITH_REALLOC_MEMORY_MODE;
        publisher_att.qos.m_publishMode.kind = eprosima::fastdds::dds::PublishModeQosPolicyKind_t::ASYNCHRONOUS_PUBLISH_MODE;
    }
    publisher_att.topic.topicDataType = myType.getName();  //This type MUST be registered
    publisher_att.topic.topicName = publisher_topic_name;

    mp_publisher = Domain::createPublisher(mp_participant, publisher_att ,static_cast<PublisherListener*>(&m_listener));

    if(mp_publisher == nullptr)
    {
        return false;
    }

    std::cout << "Publisher created, waiting for Subscribers." << std::endl;
    return true;
}

void ObjectsArrayPublisher::PubListener::onPublicationMatched(Publisher* pub,MatchingInfo& info)
{
    (void)pub;

    if (info.status == MATCHED_MATCHING)
    {
        n_matched++;
        std::cout << "Publisher matched" << std::endl;
    }
    else
    {
        n_matched--;
        std::cout << "Publisher unmatched" << std::endl;
    }
}

void ObjectsArrayPublisher::publish(const gis_rtk_msgs::msg::ObjectsArray &msg)
{
    std::cout << "publish" << std::endl;
    mp_publisher->write(const_cast<gis_rtk_msgs::msg::ObjectsArray *>(&msg));
}

void ObjectsArrayPublisher::update_message(const gis_rtk_msgs::msg::ObjectsArray &msg)
{
    latest_message = msg;
}

void ObjectsArrayPublisher::run()
{
    while(m_listener.n_matched == 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(250)); // Sleep 250 ms
    }

    // std::vector<gis_rtk_msgs::msg::Object> data(2);
    // latest_message.objects(data);
    // std::vector<geometry_msgs::msg::Point32> polygon_points(3);
    // geometry_msgs::msg::Point32 point{};
    // point.x() = 42;
    // point.y() = 11;
    // point.z() = -4.2;
    // polygon_points[2] = point;
    // latest_message.zones().at(0).polygon().points(polygon_points);
    // latest_message.zones().at(0).label() = 23;
    // latest_message.zones().at(1).polygon().points(polygon_points);
    // Publication code


    /* Initialize your structure here */

    size_t sleep_time = (1.0 / m_rate) * 1000.0;
    // size_t sleep_time = (1.0 / m_rate) * 1000.0;
    //size_t sleep_time = 360000;
    
    int msgsent = 0;
    do
    {
        // st.header().stamp().sec() = std::chrono::system_clock::now().time_since_epoch().count();
        mp_publisher->write(&latest_message);  ++msgsent;
        std::cout << "Sending sample, count=" << msgsent << "" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    } while(true);
}
