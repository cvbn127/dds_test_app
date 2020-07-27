#pragma once

#include <memory>
#include <string>
#include <chrono>

#include "PoseArraySubscriber.h"
#include "PoseArrayPublisher.h"

class PoseArrayTools
{
    public:
        ~PoseArrayTools();
        bool init(const std::string& file_path, const std::string &profile_name, const std::string &sub_topic_name = "pose_array_test", const std::string &pub_topic_name = "pose_array_pub");
        void run();
    private:
        eprosima::fastrtps::Participant *participant = nullptr;
        std::unique_ptr<PoseArrayPublisher> publisher;
        std::unique_ptr<PoseArraySubscriber> subscriber;
        std::chrono::steady_clock::time_point last_received_timepoint;
};
