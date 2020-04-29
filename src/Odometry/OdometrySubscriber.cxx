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
 * @file OdometrySubscriber.cpp
 * This file contains the implementation of the subscriber functions.
 *
 * This file was generated by the tool fastcdrgen.
 */

#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/subscriber/Subscriber.h>
#include <fastrtps/attributes/SubscriberAttributes.h>

#include <fastrtps/Domain.h>

#include "OdometrySubscriber.h"

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;

OdometrySubscriber::OdometrySubscriber() : mp_participant(nullptr), mp_subscriber(nullptr) {}

OdometrySubscriber::~OdometrySubscriber() {	Domain::removeParticipant(mp_participant);}

bool OdometrySubscriber::init()
{
    // Create RTPSParticipant

    ParticipantAttributes PParam;
    PParam.rtps.setName("Participant_subscriber"); //You can put the name you want
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

    // Create Subscriber

    SubscriberAttributes Rparam;
    Rparam.topic.topicKind = NO_KEY;
    Rparam.topic.topicDataType = myType.getName(); //Must be registered before the creation of the subscriber
    Rparam.topic.topicName = "odometry";
    // Rparam.topic.topicName = "odometry_pub";
    mp_subscriber = Domain::createSubscriber(mp_participant,Rparam, static_cast<SubscriberListener*>(&m_listener));
    if(mp_subscriber == nullptr)
    {
        return false;
    }
    return true;
}

void OdometrySubscriber::SubListener::onSubscriptionMatched(Subscriber* sub,MatchingInfo& info)
{
    (void)sub;

    if (info.status == MATCHED_MATCHING)
    {
        n_matched++;
        std::cout << "Subscriber matched" << std::endl;
    }
    else
    {
        n_matched--;
        std::cout << "Subscriber unmatched" << std::endl;
    }
}

void OdometrySubscriber::SubListener::onNewDataMessage(Subscriber* sub)
{
    // Take data
    nav_msgs::msg::Odometry st;

    std::cout << "new data message" << std::endl;

    if(sub->takeNextData(&st, &m_info))
    {
        if(m_info.sampleKind == ALIVE)
        {
            // Print your structure data here.
            ++n_msg;
            std::cout << "Sample received, count=" << n_msg << std::endl;
            std::cout << "st.header().frame_id() " << st.header().frame_id() << std::endl;
            std::cout << "st.header().stamp().sec() " << st.header().stamp().sec() << std::endl; 
            std::cout << "st.child_frame_id() " << st.child_frame_id() << std::endl;
            std::cout << "st.pose().covariance()[0] " << st.pose().covariance()[0] << std::endl;
            std::cout << "st.pose().covariance()[1] " << st.pose().covariance()[1] << std::endl;
            std::cout << "st.twist().covariance()[0] " << st.twist().covariance()[0] << std::endl;
            std::cout << "st.pose().pose().position().x() " << st.pose().pose().position().x() << std::endl;
            std::cout << "st.pose().pose().orientation().w() " << st.pose().pose().orientation().w() << std::endl;
        }
    }
}

void OdometrySubscriber::run()
{
    std::cout << "Waiting for Data, press Enter to stop the Subscriber. "<<std::endl;
    std::cin.ignore();
    std::cout << "Shutting down the Subscriber." << std::endl;
}

