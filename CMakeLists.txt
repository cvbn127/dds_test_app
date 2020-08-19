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
    sensor_msgs_lib
    diagnostic_msgs_lib


    gis_rtk_msgs_lib
    rtp_msgs_lib
    RTPRouteTask_pub_sub
    
    sh_chassis_msgs_lib
    SHRouteTask_pub_sub

    action_msgs_lib
    unique_identifier_msgs_lib 

    geographic_msgs_lib

    MarkerArrayStamped_pub_sub
    GlamPoseStamped_pub_sub
)
