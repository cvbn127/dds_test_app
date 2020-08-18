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
 * @file GoalInfoPublisher.cpp
 * This file contains the implementation of the publisher functions.
 *
 * This file was generated by the tool fastcdrgen.
 */


#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/publisher/Publisher.h>
#include <fastrtps/attributes/PublisherAttributes.h>

#include <fastrtps/Domain.h>

#include <thread>
#include <chrono>

#include "GoalInfoPublisher.h"

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;

using eprosima::fastdds::dds::TopicDataType;

GoalInfoPublisher::GoalInfoPublisher(eprosima::fastrtps::Participant *participant) : mp_participant(participant), mp_publisher(nullptr) {}

GoalInfoPublisher::~GoalInfoPublisher() 
{	
    if (should_delete_participant) 
    {
        Domain::removeParticipant(mp_participant);
    }
}

bool GoalInfoPublisher::init(int rate)
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

    Domain::registerType(mp_participant, static_cast<TopicDataType*>(&myType));

    // Create Publisher

    PublisherAttributes Wparam;
    Wparam.topic.topicKind = NO_KEY;
    Wparam.topic.topicDataType = myType.getName();  //This type MUST be registered
    Wparam.topic.topicName = "GoalInfo_pub";
    Wparam.historyMemoryPolicy = PREALLOCATED_WITH_REALLOC_MEMORY_MODE;
    Wparam.qos.m_publishMode.kind = eprosima::fastdds::dds::PublishModeQosPolicyKind_t::ASYNCHRONOUS_PUBLISH_MODE;

    mp_publisher = Domain::createPublisher(mp_participant,Wparam,static_cast<PublisherListener*>(&m_listener));

    if(mp_publisher == nullptr)
    {
        return false;
    }

    std::cout << "Publisher created, waiting for Subscribers." << std::endl;
    return true;
}

void GoalInfoPublisher::PubListener::onPublicationMatched(Publisher* pub,MatchingInfo& info)
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

void GoalInfoPublisher::publish(const action_msgs::msg::GoalInfo &msg)
{
    std::cout << "publish" << std::endl;
    mp_publisher->write(const_cast<action_msgs::msg::GoalInfo *>(&msg));
}

void GoalInfoPublisher::run()
{
    while(m_listener.n_matched == 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(250)); // Sleep 250 ms
    }

    // Publication code

    action_msgs::msg::GoalInfo st;

    unique_identifier_msgs::msg::UUID uuid;
    
    std::array<uint8_t, 16> arr;

    uuid.uuid() = arr;

    st.goal_id() = uuid;

    // uint32_t w = 100;
    // uint32_t h = 100;
    // uint32_t size = w * h;
    // std::vector<uint8_t> data(size);
    // for(int i = 0; i < size; i++)
    // {
    //     data[i] = 0;
    // }
    // st.height() = h;
    // st.width() = w;
    // st.data(data);
    // st.header().frame_id() = std::string("Hi!");
    // st.child_frame_id() = std::string("child");
    // // st.header().stamp().sec() = 127;
    // st.pose().covariance()[0] = 42.0;
    // st.pose().covariance()[1] = 43.0;
    // st.pose().pose().position().x() = 11;
    // st.pose().pose().orientation().w() = 31;
    
    // st.twist().covariance()[2] = 27.9;

    /* Initialize your structure here */

    size_t sleep_time = (1.0 / m_rate) * 100.0;
    // size_t sleep_time = (1.0 / m_rate) * 1000.0;
    // size_t sleep_time = 360000;

    int msgsent = 0;
    do
    {
        // st.header().stamp().sec() = std::chrono::system_clock::now().time_since_epoch().count();
        mp_publisher->write(&st);  ++msgsent;
        std::cout << "Sending sample, count=" << msgsent << "" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    } while(true);
}
