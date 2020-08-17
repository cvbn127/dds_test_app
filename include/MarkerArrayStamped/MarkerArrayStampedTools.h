#pragma once

#include <memory>
#include <string>
#include <chrono>

#include "MarkerArrayStampedSubscriber.h"
#include "MarkerArrayStampedPublisher.h"

class MarkerArrayStampedTools
{
    public:
        ~MarkerArrayStampedTools();
        bool init(const std::string& file_path, const std::string &profile_name, const std::string &sub_topic_name = "marker_array_stamped_test", const std::string &pub_topic_name = "marker_array_stamped_pub");
        void run();
    private:
        eprosima::fastrtps::Participant *participant = nullptr;
        std::unique_ptr<MarkerArrayStampedPublisher> publisher;
        std::unique_ptr<MarkerArrayStampedSubscriber> subscriber;
        std::chrono::steady_clock::time_point last_received_timepoint;
};
