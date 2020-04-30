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
 * @file PathVelocitiesSubscriber.cpp
 * This file contains the implementation of the subscriber functions.
 *
 * This file was generated by the tool fastcdrgen.
 */

#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/subscriber/Subscriber.h>
#include <fastrtps/attributes/SubscriberAttributes.h>

#include <fastrtps/Domain.h>

#include "PathVelocitiesSubscriber.h"

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;

std::function<void(const gis_rtk_msgs::msg::PathVelocities&)> PathVelocitiesSubscriber::callback = [](auto msg){};

PathVelocitiesSubscriber::PathVelocitiesSubscriber() : mp_participant(nullptr), mp_subscriber(nullptr) {
}

PathVelocitiesSubscriber::~PathVelocitiesSubscriber() {	Domain::removeParticipant(mp_participant);}

void PathVelocitiesSubscriber::set_callback(std::function<void(const gis_rtk_msgs::msg::PathVelocities&)> cb)
{
    callback = cb;
}

bool PathVelocitiesSubscriber::init()
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
    Rparam.topic.topicName = "path_velocities_test";
    Rparam.historyMemoryPolicy = PREALLOCATED_WITH_REALLOC_MEMORY_MODE;
    // Rparam.topic.topicName = "PathVelocities_pub";
    mp_subscriber = Domain::createSubscriber(mp_participant,Rparam, static_cast<SubscriberListener*>(&m_listener));
    if(mp_subscriber == nullptr)
    {
        return false;
    }
    return true;
}

void PathVelocitiesSubscriber::SubListener::onSubscriptionMatched(Subscriber* sub,MatchingInfo& info)
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

void PathVelocitiesSubscriber::SubListener::onNewDataMessage(Subscriber* sub)
{
    // Take data
    gis_rtk_msgs::msg::PathVelocities st;

    std::cout << "new data message" << std::endl;

    if(sub->takeNextData(&st, &m_info))
    {
        if(m_info.sampleKind == ALIVE)
        {
            // Print your structure data here.
            ++n_msg;
            std::cout << "Sample received, count=" << n_msg << std::endl;
            callback(st);
            std::cout << "st.header().frame_id() " << st.header().frame_id() << std::endl;
            std::cout << "st.header().stamp().sec() " << st.header().stamp().sec() << std::endl;
            std::cout << "path_velocities.size() " << st.path_velocities().size() << std::endl; 
        }
    }
}

void PathVelocitiesSubscriber::run()
{
    std::cout << "Waiting for Data, press Enter to stop the Subscriber. "<<std::endl;
    std::cin.ignore();
    std::cout << "Shutting down the Subscriber." << std::endl;
}

