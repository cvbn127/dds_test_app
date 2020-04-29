#pragma once

#include <memory>

class ImageSubscriber;
class ImagePublisher;

class ImageTools
{
    public:
        bool init();
        void run();
    private:
        std::unique_ptr<ImagePublisher> publisher;
        std::unique_ptr<ImageSubscriber> subscriber;
};