#include "impl/templated_publisher.h"
#include "impl/templated_subscriber.h"

#include <nav_msgs/msg/OdometryPubSubTypes.h>

#include <vector>

namespace dds_test_app
{
  //   template <>
  //   auto initialize_msg<nav_msgs::msg::OdometryPubSubType>() -> nav_msgs::msg::Odometry
  //   {
  //     nav_msgs::msg::Odometry msg;
  //     uint32_t                w    = 2000;
  //     uint32_t                h    = 2000;
  //     uint32_t                step = 3;
  //     std::vector<uint8_t>    data(w * h * step);
  //     msg.height() = h;
  //     msg.width()  = w;
  //     msg.step()   = step;
  //     msg.data(std::move(data));
  //     return std::move(msg);
  //   };

  template <>
  void print_message<nav_msgs::msg::OdometryPubSubType>(const typename nav_msgs::msg::OdometryPubSubType::type& msg)
  {
    auto str = std::string("sec: ") + std::to_string(msg.header().stamp().sec()) + "\nnsec: " + std::to_string(msg.header().stamp().nanosec()) + "\n";
    str += msg.child_frame_id() + "\n";
    str += "pose:\n  pose:\n    position:\n      x: " + std::to_string(msg.pose().pose().position().x()) + "\n";
    str += "      y: " + std::to_string(msg.pose().pose().position().y()) + "\n";
    str += "      z: " + std::to_string(msg.pose().pose().position().z()) + "\n";
    str += "twist:\n  twist:\n    linear:\n      x: " + std::to_string(msg.twist().twist().linear().x()) + "\n";
    str += "      y: " + std::to_string(msg.twist().twist().linear().y()) + "\n";
    str += "      z: " + std::to_string(msg.twist().twist().linear().z()) + "\n";
    str += "    angular:\n      x: " + std::to_string(msg.twist().twist().angular().x()) + "\n";
    str += "      y: " + std::to_string(msg.twist().twist().angular().y()) + "\n";
    str += "      z: " + std::to_string(msg.twist().twist().angular().z()) + "\n";

    std::cout << str << std::endl;
  };
} // namespace dds_test_app
