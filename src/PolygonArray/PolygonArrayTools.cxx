#include "PolygonArrayTools.h"
#include "PolygonArraySubscriber.h"
#include "PolygonArrayPublisher.h"

bool PolygonArrayTools::init()
{
    subscriber = std::make_unique<PolygonArraySubscriber>();
    publisher = std::make_unique<PolygonArrayPublisher>();

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

void PolygonArrayTools::run()
{
    subscriber->run();
}