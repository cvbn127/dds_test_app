#include "impl/templated_publisher.h"
#include "impl/templated_subscriber.h"

#include <sensor_msgs/msg/ImagePubSubTypes.h>

#include <vector>

namespace dds_test_app
{
  template <>
  auto initialize_msg<sensor_msgs::msg::ImagePubSubType>() -> sensor_msgs::msg::Image
  {
    sensor_msgs::msg::Image msg;
    uint32_t                w    = 2000;
    uint32_t                h    = 2000;
    uint32_t                step = 3;
    std::vector<uint8_t>    data(w * h * step);
    msg.height() = h;
    msg.width()  = w;
    msg.step()   = step;
    msg.data(std::move(data));
    return std::move(msg);
  };

  template <>
  void print_message<sensor_msgs::msg::ImagePubSubType>(const typename sensor_msgs::msg::ImagePubSubType::type& /*msg*/)
  {
    auto str = std::string(R"(
sdsdf
sdfasd
saas
)");
    std::cout << str << std::endl;
  };
} // namespace dds_test_app
