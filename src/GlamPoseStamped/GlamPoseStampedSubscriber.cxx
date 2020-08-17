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
 * @file GlamPoseStampedSubscriber.cpp
 * This file contains the implementation of the subscriber functions.
 *
 * This file was generated by the tool fastcdrgen.
 */

#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/subscriber/Subscriber.h>
#include <fastrtps/attributes/SubscriberAttributes.h>

#include <fastrtps/Domain.h>
#include <fastrtps/xmlparser/XMLProfileManager.h>

#include "GlamPoseStampedSubscriber.h"

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;
using namespace eprosima::fastrtps::xmlparser;

std::function<void(const glam_msgs::msg::PoseStamped&)> GlamPoseStampedSubscriber::callback = [](auto msg){};
static std::chrono::steady_clock::time_point last_received_timepoint = std::chrono::steady_clock::now();

GlamPoseStampedSubscriber::GlamPoseStampedSubscriber(eprosima::fastrtps::Participant *participant) : mp_participant(participant), mp_subscriber(nullptr) {
}

GlamPoseStampedSubscriber::~GlamPoseStampedSubscriber() 
{
    if (is_type_registred)
    {
        Domain::unregisterType(mp_participant, myType.getName());
    }
    if (should_delete_participant)
    {
    	Domain::removeParticipant(mp_participant);
    }
}

void GlamPoseStampedSubscriber::set_callback(std::function<void(const glam_msgs::msg::PoseStamped&)> cb)
{
    callback = cb;
}

bool GlamPoseStampedSubscriber::init(const std::string &topic_name, const std::string &profile_name)
{
    if(mp_participant == nullptr)
    {
        should_delete_participant = true;
        ParticipantAttributes PParam;
        PParam.rtps.setName("Participant_subscriber"); //You can put the name you want
        PParam.rtps.builtin.domainId = 120;
        mp_participant = Domain::createParticipant(PParam);
    }
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

    SubscriberAttributes subscriber_att;
    if (XMLP_ret::XML_ERROR == XMLProfileManager::fillSubscriberAttributes(profile_name, subscriber_att))
    {
      std::cerr << "Problem loading profile '" << profile_name << "'" << ". Using default values." << std::endl;
    }
    subscriber_att.topic.topicDataType = myType.getName(); //Must be registered before the creation of the subscriber
    subscriber_att.historyMemoryPolicy = PREALLOCATED_WITH_REALLOC_MEMORY_MODE;
    subscriber_att.topic.topicKind = NO_KEY;
    subscriber_att.topic.topicName = topic_name;


    mp_subscriber = Domain::createSubscriber(mp_participant, subscriber_att, static_cast<SubscriberListener*>(&m_listener));
    if(mp_subscriber == nullptr)
    {
        return false;
    }
    last_received_timepoint = std::chrono::steady_clock::now();
    return true;
}

void GlamPoseStampedSubscriber::SubListener::onSubscriptionMatched(Subscriber* sub,MatchingInfo& info)
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

void GlamPoseStampedSubscriber::SubListener::onNewDataMessage(Subscriber* sub)
{
    // Take data
    glam_msgs::msg::PoseStamped st;

    std::cout << "new data message" << std::endl;

    if(sub->takeNextData(&st, &m_info))
    {
        if(m_info.sampleKind == ALIVE)
        {
            // Print your structure data here.
            ++n_msg;
            std::cout << "Sample received, count=" << n_msg << std::endl;
	    auto now = std::chrono::steady_clock::now();
	    auto duration = now - last_received_timepoint;
	    last_received_timepoint = now;
            std::cout << "time since last message(ms): " << (std::chrono::duration_cast<std::chrono::milliseconds>(duration)).count() << std::endl;
            callback(st);
            std::cout << "st.header().frame_id() " << st.header().frame_id() << std::endl;
        }
    }
}

void GlamPoseStampedSubscriber::run()
{
    std::cout << "Running. "<<std::endl;
    bool should_stop = false;
    char c = 0;
    while(!should_stop)
    {
        std::cin >> c;
        should_stop = c == 'q'? true : false;
    }
}

