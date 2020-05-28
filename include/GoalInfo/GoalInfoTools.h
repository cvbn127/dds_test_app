#pragma once

#include <memory>
#include <string>

#include "GoalInfoSubscriber.h"
#include "GoalInfoPublisher.h"

class GoalInfoTools
{
    public:
        ~GoalInfoTools();
        bool init(const std::string& file_path, const std::string &profile_name);
        void run();
    private:
        eprosima::fastrtps::Participant *participant = nullptr;
        std::unique_ptr<GoalInfoPublisher> publisher;
        std::unique_ptr<GoalInfoSubscriber> subscriber;
};