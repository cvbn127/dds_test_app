#include "pub_sub_factory.h"

#include <iostream>

namespace dds_test_app
{

  auto PubSubFactory::get_builder(const std::string &message_type_name) -> std::shared_ptr<PubSubFactory::Builder>
  {
    auto it = builders.find(message_type_name);
    if (it == std::end(builders))
    {
      return std::shared_ptr<Builder>{nullptr};
    }
    return it->second;
  }

  auto PubSubFactory::create_publisher(const std::string &message_type_name) -> std::unique_ptr<IPublisher>
  {
    auto builder = get_builder(message_type_name);
    if (!builder)
    {
      return {nullptr};
    }
    return builder->build_publisher();
  }

  auto PubSubFactory::create_subscriber(const std::string &message_type_name) -> std::unique_ptr<ISubscriber>
  {
    auto builder = get_builder(message_type_name);
    if (!builder)
    {
      return {nullptr};
    }
    return builder->build_subscriber();
  }

  auto PubSubFactory::create_tools(const std::string &message_type_name) -> std::unique_ptr<ITools>
  {
    auto builder = get_builder(message_type_name);
    if (!builder)
    {
      return {nullptr};
    }
    return builder->build_tools();
  }

  void PubSubFactory::print_factory_list()
  {
    for (const auto &pair : builders)
    {
      std::cout << pair.first << std::endl;
    }
  }

} // namespace dds_test_app
