#include "OccupancyGridTools.h"
#include "OccupancyGridSubscriber.h"
#include "OccupancyGridPublisher.h"

bool OccupancyGridTools::init()
{
    subscriber = std::make_unique<OccupancyGridSubscriber>();
    publisher = std::make_unique<OccupancyGridPublisher>();

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

void OccupancyGridTools::run()
{
    subscriber->run();
}