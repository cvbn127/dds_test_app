cmake_minimum_required(VERSION 2.8.12)

project(TestApp)

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
    sh_chassis_msgs_lib
    action_msgs_lib
    unique_identifier_msgs_lib 
    geographic_msgs_lib
)


option(RUN_CLANG_TIDY "Run clang_tidy to static code checking" ON)

if(${RUN_CLANG_TIDY})
  find_program(
    CLANG_TIDY_EXE
    NAMES "clang-tidy"
    DOC "Path to clang-tidy executable"
    )
  if(NOT CLANG_TIDY_EXE)
    message(STATUS "clang-tidy not found.")
  else()
    message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
    set(DO_CLANG_TIDY "${CLANG_TIDY_EXE}" "-config=" "-fix")
  endif()

  if(CLANG_TIDY_EXE)
    set_target_properties(
      TestApp PROPERTIES
      CXX_CLANG_TIDY "${DO_CLANG_TIDY}"
    )
  endif()
  
endif()
