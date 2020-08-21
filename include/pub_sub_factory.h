#pragma once

#include <map>
#include <memory>
#include <utility>

#include "interface/publisher.h"
#include "interface/subscriber.h"
#include "interface/tools.h"

#include "impl/templated_publisher.h"
#include "impl/templated_subscriber.h"
#include "impl/templated_tools.h"

namespace dds_test_app
{
  class PubSubFactory
  {
  public:
    template <typename PubSubType>
    void register_factory(const std::string &msg_type_name = "")
    {
      auto type_name = msg_type_name;
      if (type_name.empty())
      {
        type_name = std::string{PubSubType{}.getName()};
      }
      builders[type_name] = std::make_shared<ConcreateBuilder<PubSubType>>();
    };

    std::unique_ptr<ITools>      create_tools(const std::string &message_type_name);
    std::unique_ptr<IPublisher>  create_publisher(const std::string &message_type_name);
    std::unique_ptr<ISubscriber> create_subscriber(const std::string &message_type_name);
    void                         print_factory_list();

  private:
    class Builder
    {
    public:
      virtual std::unique_ptr<ITools>      build_tools()      = 0;
      virtual std::unique_ptr<IPublisher>  build_publisher()  = 0;
      virtual std::unique_ptr<ISubscriber> build_subscriber() = 0;
      virtual ~Builder()                                      = default;
    };
    template <typename T>
    class ConcreateBuilder : public Builder
    {
    public:
      using pb_type = T;
      virtual std::unique_ptr<ITools>      build_tools() override { return std::make_unique<TemplatedTools<pb_type>>(); };
      virtual std::unique_ptr<IPublisher>  build_publisher() override { return std::make_unique<TemplatedPublisher<pb_type>>(); };
      virtual std::unique_ptr<ISubscriber> build_subscriber() override { return std::make_unique<TemplatedSubscriber<pb_type>>(); };
    };

    std::map<std::string, std::shared_ptr<Builder>> builders;

    std::shared_ptr<Builder> get_builder(const std::string &message_type_name);
  };

} // namespace dds_test_app
