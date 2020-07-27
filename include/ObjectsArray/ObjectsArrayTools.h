#pragma once

#include <memory>
#include <string>
#include <chrono>

#include "ObjectsArraySubscriber.h"
#include "ObjectsArrayPublisher.h"

class ObjectsArrayTools
{
    public:
        ~ObjectsArrayTools();
        bool init(const std::string& file_path, const std::string &profile_name, const std::string &sub_topic_name = "objects_array_test", const std::string &pub_topic_name = "objects_array_pub");
        void run();
    private:
        eprosima::fastrtps::Participant *participant = nullptr;
        std::unique_ptr<ObjectsArrayPublisher> publisher;
        std::unique_ptr<ObjectsArraySubscriber> subscriber;
        std::chrono::steady_clock::time_point last_received_timepoint;
};
