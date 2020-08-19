// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/*!
 * @file StringPubSubMain.cpp
 * This file acts as a main entry point to the application.
 *
 * This file was generated by the tool fastcdrgen.
 */

#include "StringPublisher.h"
#include "StringSubscriber.h"

#include "Odometry/OdometryPublisher.h"
#include "Odometry/OdometrySubscriber.h"

#include "OccupancyGrid/OccupancyGridPublisher.h"
#include "OccupancyGrid/OccupancyGridSubscriber.h"
#include "OccupancyGrid/OccupancyGridTools.h"

// #include "Pose/PosePublisher.h"
// #include "Pose/PoseSubscriber.h"

#include "Polygon/PolygonPublisher.h"
#include "Polygon/PolygonSubscriber.h"


#include <sensor_msgs/msg/ImagePubSubTypes.h>

#include "RTPRouteTask/RTPRouteTaskPublisher.h"
#include "RTPRouteTask/RTPRouteTaskSubscriber.h"
#include "RTPRouteTask/RTPRouteTaskTools.h"

#include "RegionArray/RegionArrayPublisher.h"
#include "RegionArray/RegionArraySubscriber.h"
#include "RegionArray/RegionArrayTools.h"

#include "ObjectsArray/ObjectsArrayPublisher.h"
#include "ObjectsArray/ObjectsArraySubscriber.h"
#include "ObjectsArray/ObjectsArrayTools.h"

#include "PoseArray/PoseArrayPublisher.h"
#include "PoseArray/PoseArraySubscriber.h"
#include "PoseArray/PoseArrayTools.h"

#include "GoalInfo/GoalInfoPublisher.h"
#include "GoalInfo/GoalInfoSubscriber.h"
#include "GoalInfo/GoalInfoTools.h"

#include "GeoPoseStamped/GeoPoseStampedPublisher.h"
#include "GeoPoseStamped/GeoPoseStampedSubscriber.h"
#include "GeoPoseStamped/GeoPoseStampedTools.h"

#include "SHRouteTask/SHRouteTaskPublisher.h"
#include "SHRouteTask/SHRouteTaskSubscriber.h"
#include "SHRouteTask/SHRouteTaskTools.h"

#include "DiagnosticStatus/DiagnosticStatusPublisher.h"
#include "DiagnosticStatus/DiagnosticStatusSubscriber.h"
#include "DiagnosticStatus/DiagnosticStatusTools.h"

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

    if (strcmp(argv[1], "publisher") == 0) {
      type = 1;
    } else if (strcmp(argv[1], "subscriber") == 0) {
      type = 2;
    }
    if (strcmp(argv[1], "odometry_pub") == 0) {
      type = 3;
    }
    if (strcmp(argv[1], "odometry_sub") == 0) {
      type = 4;
    }
    if (strcmp(argv[1], "pose_pub") == 0) {
      type = 5;
    }
    if (strcmp(argv[1], "pose_sub") == 0) {
      type = 6;
    }
    if (strcmp(argv[1], "polygon_pub") == 0) {
      type = 7;
    }
    if (strcmp(argv[1], "polygon_sub") == 0) {
      type = 8;
    }
    if (strcmp(argv[1], "occupancy_pub") == 0) {
      type = 12;
    }
    if (strcmp(argv[1], "occupancy_sub") == 0) {
      type = 13;
    }
    if (strcmp(argv[1], "occupancy_tools") == 0) {
      type = 14;
    }
    if (strcmp(argv[1], "rtp_route_task_pub") == 0) {
      type = 15;
    }
    if (strcmp(argv[1], "rtp_route_task_sub") == 0) {
      type = 16;
    }
    if (strcmp(argv[1], "rtp_route_task_tools") == 0) {
      type = 17;
    }
    if (strcmp(argv[1], "region_array_pub") == 0) {
      type = 18;
    }
    if (strcmp(argv[1], "region_array_sub") == 0) {
      type = 19;
    }
    if (strcmp(argv[1], "region_array_tools") == 0) {
      type = 20;
    }
    if (strcmp(argv[1], "goal_info_pub") == 0) {
      type = 21;
    }
    if (strcmp(argv[1], "goal_info_sub") == 0) {
      type = 22;
    }
    if (strcmp(argv[1], "goal_info_tools") == 0) {
      type = 23;
    }
    if (strcmp(argv[1], "geo_pose_pub") == 0) {
      type = 24;
    }
    if (strcmp(argv[1], "geo_pose_sub") == 0) {
      type = 25;
    }
    if (strcmp(argv[1], "geo_pose_tools") == 0) {
      type = 26;
    }
    if (strcmp(argv[1], "sh_route_task_pub") == 0) {
      type = 27;
    }
    if (strcmp(argv[1], "sh_route_task_sub") == 0) {
      type = 28;
    }
    if (strcmp(argv[1], "sh_route_task_tools") == 0) {
      type = 29;
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
    if (strcmp(argv[1], "pose_array_pub") == 0) {
      type = 33;
    }
    if (strcmp(argv[1], "pose_array_sub") == 0) {
      type = 34;
    }
    if (strcmp(argv[1], "pose_array_tools") == 0) {
      type = 35;
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
  case 1: {
    StringPublisher mypub;
    if (mypub.init(num_bytes, rate)) {
      mypub.run();
    }
    break;
  }
  case 2: {
    StringSubscriber mysub;
    if (mysub.init()) {
      mysub.run();
    }
    break;
  }
  case 3: {
    OdometryPublisher odom_pub;
    if (odom_pub.init(rate)) {
      odom_pub.run();
    }
    break;
  }
  case 4: {
    OdometrySubscriber odom_sub;
    if (odom_sub.init()) {
      odom_sub.run();
    }
    break;
  }
  // case 5:
  // {
  // 	PosePublisher pose_pub;
  // 	if (pose_pub.init(rate))
  // 	{
  // 		pose_pub.run();
  // 	}
  // 	break;
  // }
  // case 6:
  // {
  // 	PoseSubscriber pose_sub;
  // 	if (pose_sub.init())
  // 	{
  // 		pose_sub.run();
  // 	}
  // 	break;
  // }
  case 7: {
    PolygonPublisher polygon_pub;
    if (polygon_pub.init(rate)) {
      polygon_pub.run();
    }
    break;
  }
  case 8: {
    PolygonSubscriber polygon_sub;
    if (polygon_sub.init()) {
      polygon_sub.run();
    }
    break;
  }

  case 12: {
    OccupancyGridPublisher occu_pub;
    if (occu_pub.init(rate)) {
      occu_pub.run();
    }
    break;
  }
  case 13: {
    OccupancyGridSubscriber occu_sub;
    if (occu_sub.init()) {
      occu_sub.run();
    }
    break;
  }
  case 14: {
    OccupancyGridTools occu_tools;
    if (occu_tools.init()) {
      occu_tools.run();
    }
    break;
  }
  case 15: {
    RTPRouteTaskPublisher pub;
    if (pub.init(rate)) {
      pub.run();
    }
    break;
  }
  case 16: {
    RTPRouteTaskSubscriber sub;
    if (sub.init()) {
      sub.run();
    }
    break;
  }
  case 17: {
    RTPRouteTaskTools tools;
    std::string sub_topic = "rtp_route_task_test";
    std::string pub_topic = "rtp_route_task_pub";
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
  case 18: {
    RegionArrayPublisher pub;
    if (pub.init(rate)) {
      pub.run();
    }
    break;
  }
  case 19: {
    RegionArraySubscriber sub;
    if (sub.init()) {
      sub.run();
    }
    break;
  }
  case 20: {
    RegionArrayTools tools;
    std::string sub_topic = "region_array_test";
    std::string pub_topic = "region_array_pub";
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
  case 21: {
    GoalInfoPublisher pub;
    if (pub.init(rate)) {
      pub.run();
    }
    break;
  }
  case 22: {
    GoalInfoSubscriber sub;
    if (sub.init()) {
      sub.run();
    }
    break;
  }
  case 23: {
    GoalInfoTools tools;
    if (tools.init("/volumes/soss_config/default_fastrtps_profile.xml",
                   "part_profile_name")) {
      tools.run();
    }
    break;
  }
  case 24: {
    GeoPoseStampedPublisher pub;
    if (pub.init(rate)) {
      pub.run();
    }
    break;
  }
  case 25: {
    GeoPoseStampedSubscriber sub;
    if (sub.init("/atlans_geopose")) {
      sub.run();
    }
    break;
  }
  case 26: {
    std::string sub_topic = "geopose_test";
    std::string pub_topic = "geopose_pub";
    if (argc > 2) {
      sub_topic = argv[2];
    }
    if (argc > 3) {
      pub_topic = argv[3];
    }
    GeoPoseStampedTools tools;
    if (tools.init("/volumes/soss_config/default_fastrtps_profile.xml",
                   "part_profile_name", sub_topic, pub_topic)) {
      tools.run();
    }
    break;
  }
  case 27: {
    SHRouteTaskPublisher pub;
    if (pub.init(rate)) {
      pub.run();
    }
    break;
  }
  case 28: {
    SHRouteTaskSubscriber sub;
    if (sub.init()) {
      sub.run();
    }
    break;
  }
  case 29: {
    SHRouteTaskTools tools;
    std::string sub_topic = "sh_route_task_test";
    std::string pub_topic = "sh_route_task_pub";
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
  case 30: {
    ObjectsArrayPublisher pub;
    if (pub.init(rate)) {
      pub.run();
    }
    break;
  }
  case 31: {
    ObjectsArraySubscriber sub;
    if (sub.init()) {
      sub.run();
    }
    break;
  }
  case 32: {
    ObjectsArrayTools tools;
    std::string sub_topic = "objects_array_test";
    std::string pub_topic = "objects_array_pub";
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
  case 33: {
    PoseArrayPublisher pub;
    if (pub.init(rate)) {
      pub.run();
    }
    break;
  }
  case 34: {
    PoseArraySubscriber sub;
    if (sub.init()) {
      sub.run();
    }
    break;
  }
  case 35: {
    PoseArrayTools tools;
    std::string sub_topic = "pose_array_test";
    std::string pub_topic = "pose_array_pub";
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
  case 36: {
    DiagnosticStatusPublisher pub;
    if (pub.init(rate)) {
      pub.run();
    }
    break;
  }
  case 37: {
    DiagnosticStatusSubscriber sub;
    if (sub.init()) {
      sub.run();
    }
    break;
  }
  case 38: {
    DiagnosticStatusTools tools;
    std::string sub_topic = "pose_array_test";
    std::string pub_topic = "pose_array_pub";
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
