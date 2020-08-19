
#include <action_msgs/msg/GoalInfoPubSubTypes.h>
#include <diagnostic_msgs/msg/DiagnosticStatusPubSubTypes.h>
#include <geographic_msgs/msg/GeoPoseStampedPubSubTypes.h>
#include <geometry_msgs/msg/PolygonPubSubTypes.h>
#include <geometry_msgs/msg/PoseArrayPubSubTypes.h>
#include <geometry_msgs/msg/PosePubSubTypes.h>
#include <gis_rtk_msgs/msg/ObjectsArrayPubSubTypes.h>
#include <gis_rtk_msgs/msg/RegionArrayPubSubTypes.h>
#include <nav_msgs/msg/OccupancyGridPubSubTypes.h>
#include <nav_msgs/msg/OdometryPubSubTypes.h>
#include <rtp_msgs/msg/RouteTaskPubSubTypes.h>
#include <sensor_msgs/msg/ImagePubSubTypes.h>
#include <sh_chassis_msgs/msg/RouteTaskPubSubTypes.h>
#include <std_msgs/msg/StringPubSubTypes.h>

#include "MarkerArrayStamped/MarkerArrayStampedPublisher.h"
#include "MarkerArrayStamped/MarkerArrayStampedSubscriber.h"
#include "MarkerArrayStamped/MarkerArrayStampedTools.h"

#include "GlamPoseStamped/GlamPoseStampedPublisher.h"
#include "GlamPoseStamped/GlamPoseStampedSubscriber.h"
#include "GlamPoseStamped/GlamPoseStampedTools.h"

#include "pub_sub_factory.h"

int main(int argc, char **argv) {
  int type = 0;

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

  if (argc >= 2) {

    if (strcmp(argv[1], "region_array_pub") == 0) {
      type = 18;
    }
    if (strcmp(argv[1], "region_array_sub") == 0) {
      type = 19;
    }
    if (strcmp(argv[1], "region_array_tools") == 0) {
      type = 20;
    }
    if (strcmp(argv[1], "objects_array_pub") == 0) {
      type = 30;
    }
    if (strcmp(argv[1], "objects_array_sub") == 0) {
      type = 31;
    }
    if (strcmp(argv[1], "objects_array_tools") == 0) {
      type = 32;
    }
    if (strcmp(argv[1], "diagnostic_status_pub") == 0) {
      type = 36;
    }
    if (strcmp(argv[1], "diagnostic_status_sub") == 0) {
      type = 37;
    }
    if (strcmp(argv[1], "diagnostic_status_tools") == 0) {
      type = 38;
    }
    if (strcmp(argv[1], "marker_array_stamped_pub") == 0) {
      type = 39;
    }
    if (strcmp(argv[1], "marker_array_stamped_sub") == 0) {
      type = 40;
    }
    if (strcmp(argv[1], "marker_array_stamped_tools") == 0) {
      type = 41;
    }
    if (strcmp(argv[1], "glam_pose_stamped_pub") == 0) {
      type = 42;
    }
    if (strcmp(argv[1], "glam_pose_stamped_sub") == 0) {
      type = 43;
    }
    if (strcmp(argv[1], "glam_pose_stamped_tools") == 0) {
      type = 44;
    }
  }
  int num_bytes = 0;
  if (argc >= 4) {
    try {
      num_bytes = atoi(argv[3]);
    } catch (...) {
      num_bytes = 10;
    }
  };
  int rate = 1;
  if (argc == 3) {
    try {
      rate = atoi(argv[2]);
    } catch (...) {
      rate = 1;
    }
  }

  if (type == 0) {
    std::cout << "Error: Incorrect arguments." << std::endl;
    std::cout << "Usage: " << std::endl << std::endl;
    std::cout << argv[0] << " publisher|subscriber" << std::endl << std::endl;
    return 0;
  }

  std::cout << "Starting " << std::endl;

  // Register the type being used

  switch (type) {

  case 39: {
    MarkerArrayStampedPublisher pub;
    if (pub.init(rate)) {
      pub.run();
    }
    break;
  }
  case 40: {
    MarkerArrayStampedSubscriber sub;
    if (sub.init()) {
      sub.run();
    }
    break;
  }
  case 41: {
    MarkerArrayStampedTools tools;
    std::string sub_topic = "marker_array_stamped_test";
    std::string pub_topic = "marker_array_stamped_pub";
    if (argc > 2) {
      sub_topic = argv[2];
    }
    if (argc > 3) {
      pub_topic = argv[3];
    }
    if (tools.init("/volumes/soss_config/default_fastrtps_profile.xml",
                   "part_profile_name", sub_topic, pub_topic)) {
      tools.run();
    }
    break;
  }
  case 42: {
    GlamPoseStampedPublisher pub;
    if (pub.init(rate)) {
      pub.run();
    }
    break;
  }
  case 43: {
    GlamPoseStampedSubscriber sub;
    if (sub.init()) {
      sub.run();
    }
    break;
  }
  case 44: {
    GlamPoseStampedTools tools;
    std::string sub_topic = "glam_pose_stamped_test";
    std::string pub_topic = "glam_pose_stamped_pub";
    if (argc > 2) {
      sub_topic = argv[2];
    }
    if (argc > 3) {
      pub_topic = argv[3];
    }
    if (tools.init("/volumes/soss_config/default_fastrtps_profile.xml",
                   "part_profile_name", sub_topic, pub_topic)) {
      tools.run();
    }
    break;
  }
  }

  return 0;
}
