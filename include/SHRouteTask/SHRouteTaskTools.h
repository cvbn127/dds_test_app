#pragma once

#include <memory>
#include <string>
#include <chrono>

#include "SHRouteTaskSubscriber.h"
#include "SHRouteTaskPublisher.h"

class SHRouteTaskTools
{
    public:
        ~SHRouteTaskTools();
        bool init(const std::string& file_path, const std::string &profile_name, const std::string &sub_topic_name = "sh_route_task_test", const std::string &pub_topic_name = "sh_route_task_pub");
        void run();
    private:
        eprosima::fastrtps::Participant *participant = nullptr;
        std::unique_ptr<SHRouteTaskPublisher> publisher;
        std::unique_ptr<SHRouteTaskSubscriber> subscriber;
        std::chrono::steady_clock::time_point last_received_timepoint;
};
