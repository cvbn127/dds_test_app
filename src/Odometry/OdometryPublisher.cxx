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
 * @file OdometryPublisher.cpp
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

#include "OdometryPublisher.h"

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;

OdometryPublisher::OdometryPublisher() : mp_participant(nullptr), mp_publisher(nullptr) {}

OdometryPublisher::~OdometryPublisher() {	Domain::removeParticipant(mp_participant);}

bool OdometryPublisher::init(int rate)
{
    m_rate = rate;
    // Create RTPSParticipant

    ParticipantAttributes PParam;
    PParam.rtps.setName("Participant_publisher");  //You can put here the name you want
    PParam.rtps.builtin.domainId = 120;
    // PParam.domainId = 120;
    // PParam.rtps.builtin.readerHistoryMemoryPolicy = PREALLOCATED_WITH_REALLOC_MEMORY_MODE;
    // PParam.rtps.builtin.writerHistoryMemoryPolicy = PREALLOCATED_WITH_REALLOC_MEMORY_MODE;
    mp_participant = Domain::createParticipant(PParam);
    if(mp_participant == nullptr)
    {
        return false;
    }

    //Register the type

    Domain::registerType(mp_participant, static_cast<TopicDataType*>(&myType));

    // Create Publisher

    PublisherAttributes Wparam;
    Wparam.topic.topicKind = NO_KEY;
    Wparam.topic.topicDataType = myType.getName();  //This type MUST be registered
    Wparam.topic.topicName = "/odometry_pub";
    Wparam.historyMemoryPolicy = PREALLOCATED_WITH_REALLOC_MEMORY_MODE;

    mp_publisher = Domain::createPublisher(mp_participant,Wparam,static_cast<PublisherListener*>(&m_listener));

    if(mp_publisher == nullptr)
    {
        return false;
    }

    std::cout << "Publisher created, waiting for Subscribers." << std::endl;
    return true;
}

void OdometryPublisher::PubListener::onPublicationMatched(Publisher* pub,MatchingInfo& info)
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

void OdometryPublisher::run()
{
    while(m_listener.n_matched == 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(250)); // Sleep 250 ms
    }

    // Publication code

    nav_msgs::msg::Odometry st;
    st.header().frame_id() = std::string("Hi!");
    st.child_frame_id() = std::string("child");
    // st.header().stamp().sec() = 127;
    st.pose().covariance()[0] = 42.0;
    st.pose().covariance()[1] = 43.0;
    st.pose().pose().position().x() = 11;
    st.pose().pose().orientation().w() = 31;
    
    st.twist().covariance()[2] = 27.9;

    /* Initialize your structure here */

    size_t sleep_time = (1.0 / m_rate) * 1000.0;
    // size_t sleep_time = 360000;

    int msgsent = 0;
    do
    {
        st.header().stamp().sec() = std::chrono::system_clock::now().time_since_epoch().count();
        mp_publisher->write(&st);  ++msgsent;
        std::cout << "Sending sample, count=" << msgsent << "" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    } while(true);
}
