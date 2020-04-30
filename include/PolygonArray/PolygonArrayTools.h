#pragma once

#include <memory>

class PolygonArraySubscriber;
class PolygonArrayPublisher;

class PolygonArrayTools
{
    public:
        bool init();
        void run();
    private:
        std::unique_ptr<PolygonArrayPublisher> publisher;
        std::unique_ptr<PolygonArraySubscriber> subscriber;
};