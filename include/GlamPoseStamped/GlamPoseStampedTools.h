#pragma once

#include <memory>
#include <string>
#include <chrono>

#include "GlamPoseStampedSubscriber.h"
#include "GlamPoseStampedPublisher.h"

class GlamPoseStampedTools
{
    public:
        ~GlamPoseStampedTools();
        bool init(const std::string& file_path, const std::string &profile_name, const std::string &sub_topic_name = "pose_stamped_test", const std::string &pub_topic_name = "pose_stamped_pub");
        void run();
    private:
        eprosima::fastrtps::Participant *participant = nullptr;
        std::unique_ptr<GlamPoseStampedPublisher> publisher;
        std::unique_ptr<GlamPoseStampedSubscriber> subscriber;
        std::chrono::steady_clock::time_point last_received_timepoint;
};
