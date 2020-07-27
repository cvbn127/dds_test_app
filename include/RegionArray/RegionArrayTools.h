#pragma once

#include <memory>
#include <string>
#include <chrono>

#include "RegionArraySubscriber.h"
#include "RegionArrayPublisher.h"

class RegionArrayTools
{
    public:
        ~RegionArrayTools();
        bool init(const std::string& file_path, const std::string &profile_name, const std::string &sub_topic_name = "region_array_test", const std::string &pub_topic_name = "region_array_pub");
        void run();
    private:
        eprosima::fastrtps::Participant *participant = nullptr;
        std::unique_ptr<RegionArrayPublisher> publisher;
        std::unique_ptr<RegionArraySubscriber> subscriber;
        std::chrono::steady_clock::time_point last_received_timepoint;
};
