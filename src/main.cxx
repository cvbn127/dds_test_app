
#include <action_msgs/msg/GoalInfoPubSubTypes.h>
#include <diagnostic_msgs/msg/DiagnosticStatusPubSubTypes.h>
#include <geographic_msgs/msg/GeoPoseStampedPubSubTypes.h>
#include <geometry_msgs/msg/PolygonPubSubTypes.h>
#include <geometry_msgs/msg/PoseArrayPubSubTypes.h>
#include <geometry_msgs/msg/PosePubSubTypes.h>
#include <gis_rtk_msgs/msg/ObjectsArrayPubSubTypes.h>
#include <gis_rtk_msgs/msg/RegionArrayPubSubTypes.h>
#include <glam_msgs/msg/MarkerArrayStampedPubSubTypes.h>
#include <glam_msgs/msg/PoseStampedPubSubTypes.h>
#include <nav_msgs/msg/OccupancyGridPubSubTypes.h>
#include <nav_msgs/msg/OdometryPubSubTypes.h>
#include <rtp_msgs/msg/RouteTaskPubSubTypes.h>
#include <sensor_msgs/msg/ImagePubSubTypes.h>
#include <sh_chassis_msgs/msg/RouteTaskPubSubTypes.h>
#include <std_msgs/msg/StringPubSubTypes.h>

#include "pub_sub_factory.h"

int main(int argc, char **argv) {

  dds_test_app::PubSubFactory factory;
  factory.register_factory<sensor_msgs::msg::ImagePubSubType>();
  factory.register_factory<std_msgs::msg::StringPubSubType>();
  factory.register_factory<nav_msgs::msg::OdometryPubSubType>();
  factory.register_factory<nav_msgs::msg::OccupancyGridPubSubType>();
  factory.register_factory<geometry_msgs::msg::PolygonPubSubType>();
  factory.register_factory<geometry_msgs::msg::PosePubSubType>();
  factory.register_factory<geometry_msgs::msg::PoseArrayPubSubType>();
  factory.register_factory<geographic_msgs::msg::GeoPoseStampedPubSubType>();
  factory.register_factory<diagnostic_msgs::msg::DiagnosticStatusPubSubType>();
  factory.register_factory<gis_rtk_msgs::msg::RegionArrayPubSubType>();
  factory.register_factory<gis_rtk_msgs::msg::ObjectsArrayPubSubType>();
  factory.register_factory<action_msgs::msg::GoalInfoPubSubType>();
  factory.register_factory<rtp_msgs::msg::RouteTaskPubSubType>();
  factory.register_factory<sh_chassis_msgs::msg::RouteTaskPubSubType>();
  factory.register_factory<glam_msgs::msg::PoseStampedPubSubType>();
  factory.register_factory<glam_msgs::msg::MarkerArrayStampedPubSubType>();

  const std::string default_pub_topic = "test_app_pub";
  const std::string default_sub_topic = "test_app_sub";

  if (argc < 3) {
    std::cout << "Usage:" << std::endl;
    std::cout << argv[0] << " pub msg_type [topic]" << std::endl;
    std::cout << argv[0] << " sub msg_type [topic]" << std::endl;
    std::cout << argv[0] << " tools msg_type [pub_topic] [pub_topic]"
              << std::endl;
    std::cout << "Default pub topic name: " << default_pub_topic << std::endl;
    std::cout << "Default sub topic name: " << default_sub_topic << std::endl;

    std::cout << "Acceptable msg_types: " << std::endl;
    factory.print_factory_list();
    return 0;
  }
  auto verb = std::string(argv[1]);
  auto msg_type = std::string(argv[2]);

  if (verb == "pub") {
    auto p = factory.create_publisher(msg_type);
    if (!p) {
      std::cerr << "Cannot create publisher with type " << msg_type
                << std::endl;
      return 255;
    }
    auto topic = default_pub_topic;
    if (argc > 3) {
      topic = std::string(argv[3]);
    }
    auto success = p->init(1, topic);
    if (!success) {
      std::cout << "Failed to init publisher!" << std::endl;
      return 255;
    }
    p->run();
    return 0;
  }
  if (verb == "sub") {
    auto s = factory.create_subscriber(msg_type);
    if (!s) {
      std::cerr << "Cannot create subscriber with type " << msg_type
                << std::endl;
      return 255;
    }
    auto topic = default_sub_topic;
    if (argc > 3) {
      topic = std::string(argv[3]);
    }
    auto success = s->init(topic);
    if (!success) {
      std::cout << "Failed to init subscriber!" << std::endl;
      return 255;
    }
    s->run();
    return 0;
  }
  if (verb == "tools") {
    auto t = factory.create_tools(msg_type);
    if (!t) {
      std::cerr << "Cannot create tools with type " << msg_type << std::endl;
      return 255;
    }
    auto pub_topic = default_pub_topic;
    auto sub_topic = default_sub_topic;
    if (argc > 3) {
      pub_topic = std::string(argv[3]);
    }
    if (argc > 4) {
      sub_topic = std::string(argv[4]);
    }

    auto success = t->init("/volumes/soss_config/default_fastrtps_profile.xml",
                           "part_profile_name", pub_topic, sub_topic);
    if (!success) {
      std::cout << "Failed to init tools!" << std::endl;
      return 255;
    }
    t->run();
    return 0;
  }

  return 254;
}
