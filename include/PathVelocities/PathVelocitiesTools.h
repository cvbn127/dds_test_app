#pragma once

#include <memory>

class PathVelocitiesSubscriber;
class PathVelocitiesPublisher;

class PathVelocitiesTools
{
    public:
        bool init();
        void run();
    private:
        std::unique_ptr<PathVelocitiesPublisher> publisher;
        std::unique_ptr<PathVelocitiesSubscriber> subscriber;
};