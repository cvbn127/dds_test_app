#pragma once

#include <memory>
#include <string>
#include <chrono>

#include "ImageSubscriber.h"
#include "ImagePublisher.h"

class ImageTools
{
    public:
        ~ImageTools();
        bool init(const std::string& file_path, const std::string &profile_name, const std::string &sub_topic_name = "image_test", const std::string &pub_topic_name = "image_pub");
        void run();
    private:
        eprosima::fastrtps::Participant *participant = nullptr;
        std::unique_ptr<ImagePublisher> publisher;
        std::unique_ptr<ImageSubscriber> subscriber;
        std::chrono::steady_clock::time_point last_received_timepoint;
};