#include "PathVelocitiesTools.h"
#include "PathVelocitiesSubscriber.h"
#include "PathVelocitiesPublisher.h"

bool PathVelocitiesTools::init()
{
    subscriber = std::make_unique<PathVelocitiesSubscriber>();
    publisher = std::make_unique<PathVelocitiesPublisher>();

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

void PathVelocitiesTools::run()
{
    subscriber->run();
}