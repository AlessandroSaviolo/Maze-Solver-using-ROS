cmake_minimum_required(VERSION 2.8.3)
project(potatorobo)

find_package(catkin REQUIRED COMPONENTS
  rospy
  roscpp
  std_msgs
)

FIND_LIBRARY(WIRINGPI_LIBRARY wiringPi /usr/local/include)

catkin_package(CATKIN_DEPENDS rospy roscpp std_msgs)

include_directories(${catkin_INCLUDE_DIRS})

add_executable(publisher src/Publisher.cpp)
add_executable(subscriber src/Subscriber.cpp)

target_link_libraries(publisher ${catkin_LIBRARIES} ${WIRINGPI_LIBRARY})
target_link_libraries(subscriber ${catkin_LIBRARIES} ${WIRINGPI_LIBRARY})

