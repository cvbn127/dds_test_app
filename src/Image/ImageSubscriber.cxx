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
 * @file ImageSubscriber.cpp
 * This file contains the implementation of the subscriber functions.
 *
 * This file was generated by the tool fastcdrgen.
 */

#include <fastrtps/participant/Participant.h>
#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/subscriber/Subscriber.h>
#include <fastrtps/attributes/SubscriberAttributes.h>

#include <fastrtps/Domain.h>

#include "ImageSubscriber.h"

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;

std::function<void(const sensor_msgs::msg::Image&)> ImageSubscriber::callback = [](auto msg){};

ImageSubscriber::ImageSubscriber(eprosima::fastrtps::Participant *participant) : mp_participant(participant), mp_subscriber(nullptr) {
}

ImageSubscriber::~ImageSubscriber() 
{
    if (should_delete_participant)
    {
    	Domain::removeParticipant(mp_participant);
    }
}

void ImageSubscriber::set_callback(std::function<void(const sensor_msgs::msg::Image&)> cb)
{
    callback = cb;
}

bool ImageSubscriber::init(const std::string &topic_name)
{
    if(mp_participant == nullptr)
    {
        should_delete_participant = true;
        ParticipantAttributes PParam;
        PParam.rtps.setName("Participant_subscriber"); //You can put the name you want
        PParam.rtps.builtin.domainId = 120;
        // PParam.domainId = 120;
        // PParam.rtps.builtin.readerHistoryMemoryPolicy = PREALLOCATED_WITH_REALLOC_MEMORY_MODE;
        // PParam.rtps.builtin.writerHistoryMemoryPolicy = PREALLOCATED_WITH_REALLOC_MEMORY_MODE;
        mp_participant = Domain::createParticipant(PParam);
    }

    Domain::registerType(mp_participant, static_cast<TopicDataType*>(&myType));

    // Create Subscriber

    SubscriberAttributes Rparam;
    Rparam.topic.topicKind = NO_KEY;
    Rparam.topic.topicDataType = myType.getName(); //Must be registered before the creation of the subscriber
    //Rparam.topic.topicName = "image_test";
    Rparam.topic.topicName = topic_name;
    Rparam.historyMemoryPolicy = PREALLOCATED_WITH_REALLOC_MEMORY_MODE;
    // Rparam.topic.topicName = "Image_pub";
    mp_subscriber = Domain::createSubscriber(mp_participant,Rparam, static_cast<SubscriberListener*>(&m_listener));
    if(mp_subscriber == nullptr)
    {
        return false;
    }
    return true;
}

void ImageSubscriber::SubListener::onSubscriptionMatched(Subscriber* sub,MatchingInfo& info)
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

int last_seq_numb = -1;
int miss_count = 0;


void ImageSubscriber::SubListener::onNewDataMessage(Subscriber* sub)
{
    // Take data
    sensor_msgs::msg::Image st;

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
            int sn = std::atoi(st.header().frame_id().c_str());
            if (last_seq_numb == -1)
            {
                last_seq_numb = sn;
            }
            else
            {
                auto diff = sn - last_seq_numb;
                last_seq_numb = sn;
                if (diff > 1)
                {
                    miss_count++;
                    std::cout << "************************************************************************************" << std::endl;
                    std::cout << "************************************************************************************" << std::endl;
                    std::cout << "************************************************************************************" << std::endl;
                }
            }
            std::cout << "missed " << miss_count << std::endl;
            // std::cout << "st.header().stamp().sec() " << st.header().stamp().sec() << std::endl; 
            // std::cout << "st.pose().covariance()[0] " << st.pose().covariance()[0] << std::endl;
            // std::cout << "st.pose().covariance()[1] " << st.pose().covariance()[1] << std::endl;
            // std::cout << "st.twist().covariance()[0] " << st.twist().covariance()[0] << std::endl;
            // std::cout << "st.pose().pose().position().x() " << st.pose().pose().position().x() << std::endl;
            // std::cout << "st.pose().pose().orientation().w() " << st.pose().pose().orientation().w() << std::endl;
        }
    }
}

void ImageSubscriber::run()
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

