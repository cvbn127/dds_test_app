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
 * @file PolygonPublisher.cpp
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

#include "PolygonPublisher.h"

using namespace eprosima::fastrtps;
using namespace eprosima::fastrtps::rtps;

PolygonPublisher::PolygonPublisher() : mp_participant(nullptr), mp_publisher(nullptr) {}

PolygonPublisher::~PolygonPublisher() {	Domain::removeParticipant(mp_participant);}

bool PolygonPublisher::init(int rate)
{
    m_rate = rate;
    // Create RTPSParticipant

    ParticipantAttributes PParam;
    PParam.rtps.setName("Participant_publisher");  //You can put here the name you want
    PParam.domainId = 120;
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
    Wparam.topic.topicName = "polygon_pub";
    Wparam.historyMemoryPolicy = PREALLOCATED_WITH_REALLOC_MEMORY_MODE;

    mp_publisher = Domain::createPublisher(mp_participant,Wparam,static_cast<PublisherListener*>(&m_listener));

    if(mp_publisher == nullptr)
    {
        return false;
    }

    std::cout << "Publisher created, waiting for Subscribers." << std::endl;
    return true;
}

void PolygonPublisher::PubListener::onPublicationMatched(Publisher* pub,MatchingInfo& info)
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

void PolygonPublisher::run()
{
    while(m_listener.n_matched == 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(250)); // Sleep 250 ms
    }

    // Publication code

    geometry_msgs::msg::Polygon st;
    geometry_msgs::msg::Point32 one_point;
    geometry_msgs::msg::Point32 second_point;

    std::vector<geometry_msgs::msg::Point32> points;
    points.push_back(one_point);
    points.push_back(second_point);

    st.points(points);
    /* Initialize your structure here */

    size_t sleep_time = (1.0 / m_rate) * 1000.0;
    // size_t sleep_time = 3600000;

    int msgsent = 0;
    do
    {
        one_point.x() = 32;
        one_point.y() = 14;
        one_point.z() = 3.2;
        second_point.x() = 42.2 + msgsent;
        second_point.y() = 27.33;
        second_point.z() = 82.2;
        std::vector<geometry_msgs::msg::Point32> points;
        points.push_back(one_point);
        points.push_back(second_point);

        st.points(points);
        mp_publisher->write(&st);  ++msgsent;
        std::cout << "Sending sample, count=" << msgsent << "" << std::endl;
        std::cout << "st.points().size() " << st.points().size() << std::endl;
        for(auto p: st.points())
        {
            std::cout << "p.x() " << p.x() << std::endl;
            std::cout << "p.y() " << p.y() << std::endl;
            std::cout << "p.z() " << p.z() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    } while(true);
}
