cmake_minimum_required(VERSION 2.8.12)

project("generated_code")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find requirements
find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)

find_package(action_msgs_lib REQUIRED)
find_package(diagnostic_msgs_lib REQUIRED)
find_package(glam_msgs_lib REQUIRED)
find_package(builtin_interfaces_lib REQUIRED)
find_package(std_msgs_lib REQUIRED)
find_package(geometry_msgs_lib REQUIRED)
find_package(nav_msgs_lib REQUIRED)
find_package(sensor_msgs_lib REQUIRED)
find_package(gis_rtk_msgs_lib REQUIRED)
find_package(rtp_msgs_lib REQUIRED)
find_package(sh_chassis_msgs_lib REQUIRED)
find_package(unique_identifier_msgs_lib REQUIRED)
find_package(geographic_msgs_lib REQUIRED)



add_library(Pose_pub_sub
    src/Pose/PosePublisher.cxx 
    src/Pose/PoseSubscriber.cxx
)
target_link_libraries(Pose_pub_sub fastcdr fastrtps builtin_interfaces_lib geometry_msgs_lib)
target_include_directories(Pose_pub_sub PUBLIC include/Pose)

add_library(Polygon_pub_sub
    src/Polygon/PolygonPublisher.cxx
    src/Polygon/PolygonSubscriber.cxx
)
target_link_libraries(Polygon_pub_sub fastcdr fastrtps builtin_interfaces_lib geometry_msgs_lib)
target_include_directories(Polygon_pub_sub PUBLIC include/Polygon)

add_library(RTPRouteTask_pub_sub
    src/RTPRouteTask/RTPRouteTaskPublisher.cxx
    src/RTPRouteTask/RTPRouteTaskSubscriber.cxx
    src/RTPRouteTask/RTPRouteTaskTools.cxx
)
target_link_libraries(RTPRouteTask_pub_sub fastcdr fastrtps builtin_interfaces_lib rtp_msgs_lib)
target_include_directories(RTPRouteTask_pub_sub PUBLIC include/RTPRouteTask)

add_library(SHRouteTask_pub_sub
    src/SHRouteTask/SHRouteTaskPublisher.cxx
    src/SHRouteTask/SHRouteTaskSubscriber.cxx
    src/SHRouteTask/SHRouteTaskTools.cxx
)
target_link_libraries(SHRouteTask_pub_sub fastcdr fastrtps builtin_interfaces_lib sh_chassis_msgs_lib)
target_include_directories(SHRouteTask_pub_sub PUBLIC include/SHRouteTask)

add_library(RegionArray_pub_sub
    src/RegionArray/RegionArrayPublisher.cxx
    src/RegionArray/RegionArraySubscriber.cxx
    src/RegionArray/RegionArrayTools.cxx
)
target_link_libraries(RegionArray_pub_sub fastcdr fastrtps builtin_interfaces_lib gis_rtk_msgs_lib)
target_include_directories(RegionArray_pub_sub PUBLIC include/RegionArray)

add_library(ObjectsArray_pub_sub
    src/ObjectsArray/ObjectsArrayPublisher.cxx
    src/ObjectsArray/ObjectsArraySubscriber.cxx
    src/ObjectsArray/ObjectsArrayTools.cxx
)
target_link_libraries(ObjectsArray_pub_sub fastcdr fastrtps builtin_interfaces_lib gis_rtk_msgs_lib)
target_include_directories(ObjectsArray_pub_sub PUBLIC include/ObjectsArray)

add_library(PoseArray_pub_sub
    src/PoseArray/PoseArrayPublisher.cxx
    src/PoseArray/PoseArraySubscriber.cxx
    src/PoseArray/PoseArrayTools.cxx
)
target_link_libraries(PoseArray_pub_sub fastcdr fastrtps builtin_interfaces_lib geometry_msgs_lib)
target_include_directories(PoseArray_pub_sub PUBLIC include/PoseArray)

add_library(GoalInfo_pub_sub
    src/GoalInfo/GoalInfoPublisher.cxx
    src/GoalInfo/GoalInfoSubscriber.cxx
    src/GoalInfo/GoalInfoTools.cxx
)
target_link_libraries(GoalInfo_pub_sub fastcdr fastrtps builtin_interfaces_lib action_msgs_lib)
target_include_directories(GoalInfo_pub_sub PUBLIC include/GoalInfo)

add_library(GeoPoseStamped_pub_sub
    src/GeoPoseStamped/GeoPoseStampedPublisher.cxx
    src/GeoPoseStamped/GeoPoseStampedSubscriber.cxx
    src/GeoPoseStamped/GeoPoseStampedTools.cxx
)
target_link_libraries(GeoPoseStamped_pub_sub fastcdr fastrtps builtin_interfaces_lib geographic_msgs_lib)
target_include_directories(GeoPoseStamped_pub_sub PUBLIC include/GeoPoseStamped)

add_library(DiagnosticStatus_pub_sub
    src/DiagnosticStatus/DiagnosticStatusPublisher.cxx
    src/DiagnosticStatus/DiagnosticStatusSubscriber.cxx
    src/DiagnosticStatus/DiagnosticStatusTools.cxx
)
target_link_libraries(DiagnosticStatus_pub_sub fastcdr fastrtps builtin_interfaces_lib diagnostic_msgs_lib)
target_include_directories(DiagnosticStatus_pub_sub PUBLIC include/DiagnosticStatus)

add_library(MarkerArrayStamped_pub_sub
    src/MarkerArrayStamped/MarkerArrayStampedPublisher.cxx
    src/MarkerArrayStamped/MarkerArrayStampedSubscriber.cxx
    src/MarkerArrayStamped/MarkerArrayStampedTools.cxx
)
target_link_libraries(MarkerArrayStamped_pub_sub fastcdr fastrtps builtin_interfaces_lib glam_msgs_lib)
target_include_directories(MarkerArrayStamped_pub_sub PUBLIC include/MarkerArrayStamped)

add_library(GlamPoseStamped_pub_sub
    src/GlamPoseStamped/GlamPoseStampedPublisher.cxx
    src/GlamPoseStamped/GlamPoseStampedSubscriber.cxx
    src/GlamPoseStamped/GlamPoseStampedTools.cxx
)
target_link_libraries(GlamPoseStamped_pub_sub fastcdr fastrtps builtin_interfaces_lib glam_msgs_lib)
target_include_directories(GlamPoseStamped_pub_sub PUBLIC include/GlamPoseStamped)

add_executable(TestApp src/main.cxx src/pub_sub_factory.cpp)

target_include_directories(TestApp PRIVATE include)

target_link_libraries(TestApp fastcdr fastrtps
    builtin_interfaces_lib 

    std_msgs_lib

    glam_msgs_lib

    nav_msgs_lib

    geometry_msgs_lib
    Pose_pub_sub

    Polygon_pub_sub

    sensor_msgs_lib

    diagnostic_msgs_lib
    DiagnosticStatus_pub_sub

    gis_rtk_msgs_lib
    rtp_msgs_lib
    RTPRouteTask_pub_sub
    
    sh_chassis_msgs_lib
    SHRouteTask_pub_sub

    action_msgs_lib
    GoalInfo_pub_sub
    unique_identifier_msgs_lib 

    geographic_msgs_lib
    GeoPoseStamped_pub_sub

    RegionArray_pub_sub
    ObjectsArray_pub_sub
    PoseArray_pub_sub

    MarkerArrayStamped_pub_sub
    GlamPoseStamped_pub_sub
)
