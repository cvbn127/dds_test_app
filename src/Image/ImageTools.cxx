#include "ImageTools.h"
#include "ImageSubscriber.h"
#include "ImagePublisher.h"

bool ImageTools::init()
{
    subscriber = std::make_unique<ImageSubscriber>();
    publisher = std::make_unique<ImagePublisher>();

    bool result = subscriber->init();
    if (!result)
    {
        return result;
    }

    result = publisher->init(1);
    if (!result)
    {
        return result;
    }
    subscriber->set_callback([this](const auto &msg) {publisher->publish(msg);});    
    return result;
}

void ImageTools::run()
{
    subscriber->run();
}