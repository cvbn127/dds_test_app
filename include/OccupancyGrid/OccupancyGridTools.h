#pragma once

#include <memory>

class OccupancyGridSubscriber;
class OccupancyGridPublisher;

class OccupancyGridTools
{
    public:
        bool init();
        void run();
    private:
        std::unique_ptr<OccupancyGridPublisher> publisher;
        std::unique_ptr<OccupancyGridSubscriber> subscriber;
};