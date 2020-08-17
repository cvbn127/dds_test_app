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
 * @file ImagePublisher.h
 * This header file contains the declaration of the publisher functions.
 *
 * This file was generated by the tool fastcdrgen.
 */


#ifndef _GLAM_MSGS_MSG_PoseStamped_PUBLISHER_H_
#define _GLAM_MSGS_MSG_PoseStamped_PUBLISHER_H_

#include <fastrtps/fastrtps_fwd.h>
#include <fastrtps/publisher/PublisherListener.h>

#include "PoseStampedPubSubTypes.h"

class GlamPoseStampedPublisher
{
public:
	GlamPoseStampedPublisher(eprosima::fastrtps::Participant *participant = nullptr);
	virtual ~GlamPoseStampedPublisher();
	bool init(int rate, const std::string &topic_name = "glam_pose_stamped", const std::string &profile_name = "pose-array-pub-profile");
	void run();
	void publish(const glam_msgs::msg::PoseStamped &msg);
	void update_message(const glam_msgs::msg::PoseStamped &msg);

private:
	eprosima::fastrtps::Participant *mp_participant;
	eprosima::fastrtps::Publisher *mp_publisher;

	int m_rate;
	bool should_delete_participant = false;
	bool is_type_registred = false;

	glam_msgs::msg::PoseStamped latest_message;

	class PubListener : public eprosima::fastrtps::PublisherListener
	{
	public:
		PubListener() : n_matched(0){};
		~PubListener(){};
		void onPublicationMatched(eprosima::fastrtps::Publisher* pub,eprosima::fastrtps::rtps::MatchingInfo& info);
		int n_matched;
	} m_listener;
	glam_msgs::msg::PoseStampedPubSubType myType;
};

#endif // _SENSOR_MSGS_MSG_IMAGE_PUBLISHER_H_
