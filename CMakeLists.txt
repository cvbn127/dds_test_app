cmake_minimum_required(VERSION 2.8.12)

project("generated_code")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find requirements
find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)


#set(MESSAGES_PATH /volumes/fastrtps_gen/fastrtps_gen/sources)
set(MESSAGES_PATH /volumes/fastcdr-ros-msgs)

message(STATUS "Configuring action_msgs...")
file(GLOB_RECURSE ACTION_MSGS_SRCS ${MESSAGES_PATH}/action_msgs/msg/*.cxx)
add_library(Action_msgs_lib ${ACTION_MSGS_SRCS})
target_link_libraries(Action_msgs_lib fastcdr fastrtps)
target_include_directories(Action_msgs_lib PUBLIC ${MESSAGES_PATH} ${MESSAGES_PATH}/action_msgs/msg )

message(STATUS "Configuring diagnostic_msgs...")
file(GLOB_RECURSE DIAGNOSTIC_MSGS_SRCS ${MESSAGES_PATH}/diagnostic_msgs/msg/*.cxx)
add_library(Diagnostic_lib ${DIAGNOSTIC_MSGS_SRCS})
target_link_libraries(Diagnostic_lib fastcdr fastrtps)
target_include_directories(Diagnostic_lib PUBLIC ${MESSAGES_PATH} ${MESSAGES_PATH}/diagnostic_msgs/msg )

message(STATUS "Configuring builtin_interfaces...")
file(GLOB_RECURSE BUILTIN_INTERFACES_SRCS ${MESSAGES_PATH}/builtin_interfaces/msg/*.cxx)
add_library(Builtin_interfaces_lib ${BUILTIN_INTERFACES_SRCS})
target_link_libraries(Builtin_interfaces_lib fastcdr fastrtps)
target_include_directories(Builtin_interfaces_lib PUBLIC ${MESSAGES_PATH} ${MESSAGES_PATH}/builtin_interfaces/msg )

message(STATUS "Configuring std_msgs...")
file(GLOB_RECURSE STD_MSGS_SRCS ${MESSAGES_PATH}/std_msgs/msg/*.cxx)
add_library(Std_msgs_lib ${STD_MSGS_SRCS})
target_link_libraries(Std_msgs_lib fastcdr fastrtps)
target_include_directories(Std_msgs_lib PUBLIC ${MESSAGES_PATH} ${MESSAGES_PATH}/std_msgs/msg )

message(STATUS "Configuring geometry_msgs...")
file(GLOB_RECURSE GEOMETRY_MSGS_SRCS ${MESSAGES_PATH}/geometry_msgs/msg/*.cxx)
add_library(Geometry_msgs_lib ${GEOMETRY_MSGS_SRCS})
target_link_libraries(Geometry_msgs_lib fastcdr fastrtps)
target_include_directories(Geometry_msgs_lib PUBLIC ${MESSAGES_PATH} ${MESSAGES_PATH}/geometry_msgs/msg )

message(STATUS "Configuring nav_msgs...")
file(GLOB_RECURSE NAV_MSGS_SRCS ${MESSAGES_PATH}/nav_msgs/msg/*.cxx)
add_library(Nav_msgs_lib ${NAV_MSGS_SRCS})
target_link_libraries(Nav_msgs_lib fastcdr fastrtps)
target_include_directories(Nav_msgs_lib PUBLIC ${MESSAGES_PATH} ${MESSAGES_PATH}/nav_msgs/msg )

message(STATUS "Configuring sensor_msgs...")
file(GLOB_RECURSE SENSOR_MSGS_SRCS ${MESSAGES_PATH}/sensor_msgs/msg/*.cxx)
add_library(Sensor_msgs_lib ${SENSOR_MSGS_SRCS})
target_link_libraries(Sensor_msgs_lib fastcdr fastrtps)
target_include_directories(Sensor_msgs_lib PUBLIC ${MESSAGES_PATH} ${MESSAGES_PATH}/sensor_msgs/msg )

message(STATUS "Configuring gis_rtk_msgs...")
file(GLOB_RECURSE GIS_RTK_MSGS_SRCS ${MESSAGES_PATH}/gis_rtk_msgs/msg/*.cxx)
add_library(GisRtk_msgs_lib ${GIS_RTK_MSGS_SRCS})
target_link_libraries(GisRtk_msgs_lib fastcdr fastrtps Geometry_msgs_lib)
target_include_directories(GisRtk_msgs_lib PUBLIC ${MESSAGES_PATH} ${MESSAGES_PATH}/gis_rtk_msgs/msg )

message(STATUS "Configuring rtp_msgs...")
file(GLOB_RECURSE RTP_MSGS_SRCS ${MESSAGES_PATH}/rtp_msgs/msg/*.cxx)
add_library(Rtp_msgs_lib ${RTP_MSGS_SRCS})
target_link_libraries(Rtp_msgs_lib fastcdr fastrtps Geometry_msgs_lib)
target_include_directories(Rtp_msgs_lib PUBLIC ${MESSAGES_PATH} ${MESSAGES_PATH}/rtp_msgs/msg )

message(STATUS "Configuring sh_chassis_msgs...")
file(GLOB_RECURSE SH_CHASSIS_MSGS_SRCS ${MESSAGES_PATH}/sh_chassis_msgs/msg/*.cxx)
add_library(ShChassis_msgs_lib ${SH_CHASSIS_MSGS_SRCS})
target_link_libraries(ShChassis_msgs_lib fastcdr fastrtps Geometry_msgs_lib)
target_include_directories(ShChassis_msgs_lib PUBLIC ${MESSAGES_PATH} ${MESSAGES_PATH}/sh_chassis_msgs/msg )

message(STATUS "Configuring unique_identifier_msgs...")
file(GLOB_RECURSE UNIQUE_IDENTIFIER_MSGS_SRCS ${MESSAGES_PATH}/unique_identifier_msgs/msg/*.cxx)
add_library(UniqueIdentifier_msgs_lib ${UNIQUE_IDENTIFIER_MSGS_SRCS})
target_link_libraries(UniqueIdentifier_msgs_lib fastcdr fastrtps)
target_include_directories(UniqueIdentifier_msgs_lib PUBLIC ${MESSAGES_PATH} ${MESSAGES_PATH}/unique_identifier_msgs/msg )

message(STATUS "Configuring geographic_msgs...")
file(GLOB_RECURSE GEOGRAPHIC_MSGS_SRCS ${MESSAGES_PATH}/geographic_msgs/msg/*.cxx)
add_library(Geographic_msgs_lib ${GEOGRAPHIC_MSGS_SRCS})
target_link_libraries(Geographic_msgs_lib fastcdr fastrtps)
target_include_directories(Geographic_msgs_lib PUBLIC ${MESSAGES_PATH} ${MESSAGES_PATH}/geographic_msgs/msg )


add_library(String_pub_sub
    src/StringPublisher.cxx 
    src/StringSubscriber.cxx
)
target_link_libraries(String_pub_sub fastcdr fastrtps Std_msgs_lib)
target_include_directories(String_pub_sub PUBLIC include)


add_library(Odometry_pub_sub
    src/Odometry/OdometryPublisher.cxx 
    src/Odometry/OdometrySubscriber.cxx
)
target_link_libraries(Odometry_pub_sub fastcdr fastrtps Builtin_interfaces_lib Nav_msgs_lib)
target_include_directories(Odometry_pub_sub PUBLIC include/Odometry)

add_library(OccupancyGrid_pub_sub
    src/OccupancyGrid/OccupancyGridPublisher.cxx 
    src/OccupancyGrid/OccupancyGridSubscriber.cxx
    src/OccupancyGrid/OccupancyGridTools.cxx
)
target_link_libraries(OccupancyGrid_pub_sub fastcdr fastrtps Builtin_interfaces_lib Nav_msgs_lib)
target_include_directories(OccupancyGrid_pub_sub PUBLIC include/OccupancyGrid)


add_library(Pose_pub_sub
    src/Pose/PosePublisher.cxx 
    src/Pose/PoseSubscriber.cxx
)
target_link_libraries(Pose_pub_sub fastcdr fastrtps Builtin_interfaces_lib Geometry_msgs_lib)
target_include_directories(Pose_pub_sub PUBLIC include/Pose)

add_library(Polygon_pub_sub
    src/Polygon/PolygonPublisher.cxx
    src/Polygon/PolygonSubscriber.cxx
)
target_link_libraries(Polygon_pub_sub fastcdr fastrtps Builtin_interfaces_lib Geometry_msgs_lib)
target_include_directories(Polygon_pub_sub PUBLIC include/Polygon)

add_library(Image_pub_sub
    src/Image/ImagePublisher.cxx
    src/Image/ImageSubscriber.cxx
    src/Image/ImageTools.cxx
)
target_link_libraries(Image_pub_sub fastcdr fastrtps Builtin_interfaces_lib Sensor_msgs_lib)
target_include_directories(Image_pub_sub PUBLIC include/Image)

add_library(RTPRouteTask_pub_sub
    src/RTPRouteTask/RTPRouteTaskPublisher.cxx
    src/RTPRouteTask/RTPRouteTaskSubscriber.cxx
    src/RTPRouteTask/RTPRouteTaskTools.cxx
)
target_link_libraries(RTPRouteTask_pub_sub fastcdr fastrtps Builtin_interfaces_lib Rtp_msgs_lib)
target_include_directories(RTPRouteTask_pub_sub PUBLIC include/RTPRouteTask)

add_library(SHRouteTask_pub_sub
    src/SHRouteTask/SHRouteTaskPublisher.cxx
    src/SHRouteTask/SHRouteTaskSubscriber.cxx
    src/SHRouteTask/SHRouteTaskTools.cxx
)
target_link_libraries(SHRouteTask_pub_sub fastcdr fastrtps Builtin_interfaces_lib ShChassis_msgs_lib)
target_include_directories(SHRouteTask_pub_sub PUBLIC include/SHRouteTask)

add_library(RegionArray_pub_sub
    src/RegionArray/RegionArrayPublisher.cxx
    src/RegionArray/RegionArraySubscriber.cxx
    src/RegionArray/RegionArrayTools.cxx
)
target_link_libraries(RegionArray_pub_sub fastcdr fastrtps Builtin_interfaces_lib GisRtk_msgs_lib)
target_include_directories(RegionArray_pub_sub PUBLIC include/RegionArray)

add_library(ObjectsArray_pub_sub
    src/ObjectsArray/ObjectsArrayPublisher.cxx
    src/ObjectsArray/ObjectsArraySubscriber.cxx
    src/ObjectsArray/ObjectsArrayTools.cxx
)
target_link_libraries(ObjectsArray_pub_sub fastcdr fastrtps Builtin_interfaces_lib GisRtk_msgs_lib)
target_include_directories(ObjectsArray_pub_sub PUBLIC include/ObjectsArray)

add_library(PoseArray_pub_sub
    src/PoseArray/PoseArrayPublisher.cxx
    src/PoseArray/PoseArraySubscriber.cxx
    src/PoseArray/PoseArrayTools.cxx
)
target_link_libraries(PoseArray_pub_sub fastcdr fastrtps Builtin_interfaces_lib Geometry_msgs_lib)
target_include_directories(PoseArray_pub_sub PUBLIC include/PoseArray)

add_library(GoalInfo_pub_sub
    src/GoalInfo/GoalInfoPublisher.cxx
    src/GoalInfo/GoalInfoSubscriber.cxx
    src/GoalInfo/GoalInfoTools.cxx
)
target_link_libraries(GoalInfo_pub_sub fastcdr fastrtps Builtin_interfaces_lib Action_msgs_lib)
target_include_directories(GoalInfo_pub_sub PUBLIC include/GoalInfo)

add_library(GeoPoseStamped_pub_sub
    src/GeoPoseStamped/GeoPoseStampedPublisher.cxx
    src/GeoPoseStamped/GeoPoseStampedSubscriber.cxx
    src/GeoPoseStamped/GeoPoseStampedTools.cxx
)
target_link_libraries(GeoPoseStamped_pub_sub fastcdr fastrtps Builtin_interfaces_lib Geographic_msgs_lib)
target_include_directories(GeoPoseStamped_pub_sub PUBLIC include/GeoPoseStamped)

add_executable(TestApp src/main.cxx)

target_link_libraries(TestApp fastcdr fastrtps
    Builtin_interfaces_lib 

    Std_msgs_lib
    String_pub_sub

    Nav_msgs_lib
    Odometry_pub_sub
    OccupancyGrid_pub_sub

    Geometry_msgs_lib
    Pose_pub_sub

    Polygon_pub_sub

    Sensor_msgs_lib
    Image_pub_sub

    GisRtk_msgs_lib
    Rtp_msgs_lib
    RTPRouteTask_pub_sub
    
    ShChassis_msgs_lib
    SHRouteTask_pub_sub

    Action_msgs_lib
    GoalInfo_pub_sub
    UniqueIdentifier_msgs_lib 

    Geographic_msgs_lib
    GeoPoseStamped_pub_sub

    RegionArray_pub_sub
    ObjectsArray_pub_sub
    PoseArray_pub_sub
)
