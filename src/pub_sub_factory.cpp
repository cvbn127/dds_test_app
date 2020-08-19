#include "pub_sub_factory.h"

namespace dds_test_app {

auto PubSubFactory::get_builder(const std::string &pkg, const std::string &msg)
    -> std::shared_ptr<PubSubFactory::Builder> {
  auto type_name = pkg + "__" + msg;
  auto it = builders.find(type_name);
  if (it == std::end(builders)) {
    return std::shared_ptr<Builder>{nullptr};
  }
  return it->second;
}

std::unique_ptr<IPublisher>
PubSubFactory::create_publisher(const std::string &pkg,
                                const std::string &msg) {

  auto builder = get_builder(pkg, msg);
  if (!builder) {
    return {nullptr};
  }

  return builder->build_publisher();
}

std::unique_ptr<ISubscriber>
PubSubFactory::create_subscriber(const std::string &pkg,
                                 const std::string &msg) {
  auto builder = get_builder(pkg, msg);
  if (!builder) {
    return {nullptr};
  }

  return builder->build_subscriber();
}

std::unique_ptr<ITools> PubSubFactory::create_tools(const std::string &pkg,
                                                    const std::string &msg) {
  auto builder = get_builder(pkg, msg);
  if (!builder) {
    return {nullptr};
  }

  return builder->build_tools();
}
} // namespace dds_test_app
