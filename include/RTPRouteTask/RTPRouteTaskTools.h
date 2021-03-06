#pragma once

#include <memory>
#include <string>
#include <chrono>

#include "RTPRouteTaskSubscriber.h"
#include "RTPRouteTaskPublisher.h"

class RTPRouteTaskTools
{
    public:
        ~RTPRouteTaskTools();
        bool init(const std::string& file_path, const std::string &profile_name, const std::string &sub_topic_name = "geo_pose_test", const std::string &pub_topic_name = "geo_pose_pub");
        void run();
    private:
        eprosima::fastrtps::Participant *participant = nullptr;
        std::unique_ptr<RTPRouteTaskPublisher> publisher;
        std::unique_ptr<RTPRouteTaskSubscriber> subscriber;
        std::chrono::steady_clock::time_point last_received_timepoint;
};
