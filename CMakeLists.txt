cmake_minimum_required(VERSION 2.8.12)

project("generated_code")

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find requirements
find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)


set(MESSAGES_PATH /volumes/fastrtps_gen/fastrtps_gen/sources)

message(STATUS "Configuring action_msgs...")
file(GLOB_RECURSE ACTION_MSGS_SRCS ${MESSAGES_PATH}/action_msgs/msg/*.cxx)
add_library(Action_msgs_lib ${ACTION_MSGS_SRCS})
target_link_libraries(Action_msgs_lib fastcdr fastrtps)
target_include_directories(Action_msgs_lib PUBLIC ${MESSAGES_PATH} ${MESSAGES_PATH}/action_msgs/msg )

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
target_link_libraries(GisRtk_msgs_lib fastcdr fastrtps)
target_include_directories(GisRtk_msgs_lib PUBLIC ${MESSAGES_PATH} ${MESSAGES_PATH}/gis_rtk_msgs/msg )



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
target_link_libraries(Odometry_pub_sub fastcdr fastrtps Nav_msgs_lib)
target_include_directories(Odometry_pub_sub PUBLIC include/Odometry)

add_library(OccupancyGrid_pub_sub
    src/OccupancyGrid/OccupancyGridPublisher.cxx 
    src/OccupancyGrid/OccupancyGridSubscriber.cxx
    src/OccupancyGrid/OccupancyGridTools.cxx
)
target_link_libraries(OccupancyGrid_pub_sub fastcdr fastrtps Nav_msgs_lib)
target_include_directories(OccupancyGrid_pub_sub PUBLIC include/OccupancyGrid)


add_library(Pose_pub_sub
    src/Pose/PosePublisher.cxx 
    src/Pose/PoseSubscriber.cxx
)
target_link_libraries(Pose_pub_sub fastcdr fastrtps Geometry_msgs_lib)
target_include_directories(Pose_pub_sub PUBLIC include/Pose)

add_library(Polygon_pub_sub
    src/Polygon/PolygonPublisher.cxx
    src/Polygon/PolygonSubscriber.cxx
)
target_link_libraries(Polygon_pub_sub fastcdr fastrtps Geometry_msgs_lib)
target_include_directories(Polygon_pub_sub PUBLIC include/Polygon)

add_library(Image_pub_sub
    src/Image/ImagePublisher.cxx
    src/Image/ImageSubscriber.cxx
    src/Image/ImageTools.cxx
)
target_link_libraries(Image_pub_sub fastcdr fastrtps Sensor_msgs_lib)
target_include_directories(Image_pub_sub PUBLIC include/Image)

add_library(PathVelocities_pub_sub
    src/PathVelocities/PathVelocitiesPublisher.cxx
    src/PathVelocities/PathVelocitiesSubscriber.cxx
    src/PathVelocities/PathVelocitiesTools.cxx
)
target_link_libraries(PathVelocities_pub_sub fastcdr fastrtps GisRtk_msgs_lib)
target_include_directories(PathVelocities_pub_sub PUBLIC include/PathVelocities)

add_library(PolygonArray_pub_sub
    src/PolygonArray/PolygonArrayPublisher.cxx
    src/PolygonArray/PolygonArraySubscriber.cxx
    src/PolygonArray/PolygonArrayTools.cxx
)
target_link_libraries(PolygonArray_pub_sub fastcdr fastrtps GisRtk_msgs_lib)
target_include_directories(PolygonArray_pub_sub PUBLIC include/PolygonArray)


add_library(GoalInfo_pub_sub
    src/GoalInfo/GoalInfoPublisher.cxx
    src/GoalInfo/GoalInfoSubscriber.cxx
    src/GoalInfo/GoalInfoTools.cxx
)
target_link_libraries(GoalInfo_pub_sub fastcdr fastrtps Action_msgs_lib)
target_include_directories(GoalInfo_pub_sub PUBLIC include/GoalInfo)


add_executable(TestApp src/main.cxx)
# target_link_libraries(TestApp fastcdr fastrtps
#     Geometry_msgs_lib
#     String_lib
#     String_pub_sub
#     Odometry_lib
#     Odometry_pub_sub
# )

target_link_libraries(TestApp fastcdr fastrtps
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
    PolygonArray_pub_sub
    PathVelocities_pub_sub

    Action_msgs_lib
    GoalInfo_pub_sub
)