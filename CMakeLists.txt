cmake_minimum_required(VERSION 3.0.2)
project(custum_pc_publisher)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
)

catkin_package(
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(custum_pc_publisher src/custum_pc.cpp)
target_link_libraries(custum_pc_publisher ${catkin_LIBRARIES})