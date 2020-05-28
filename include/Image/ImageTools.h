#pragma once

#include <memory>
#include <string>

#include "ImageSubscriber.h"
#include "ImagePublisher.h"

class ImageTools
{
    public:
        ~ImageTools();
        bool init(const std::string& file_path, const std::string &profile_name);
        void run();
    private:
        eprosima::fastrtps::Participant *participant = nullptr;
        std::unique_ptr<ImagePublisher> publisher;
        std::unique_ptr<ImageSubscriber> subscriber;
};