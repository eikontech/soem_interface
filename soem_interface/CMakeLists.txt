# Copyright (2019-2020) Robotics Systems Lab - ETH Zurich:
# Markus Staeuble, Jonas Junger, Johannes Pankert, Philipp Leemann,
# Tom Lankhorst, Samuel Bachmann, Gabriel Hottiger, Lennert Nachtigall,
# Mario Mauerer, Remo Diethelm
#
# This file is part of the soem_interface.
#
# The soem_interface is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# The seom_interface is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with the soem_interface.  If not, see <https://www.gnu.org/licenses/>.

cmake_minimum_required(VERSION 3.5)
project(soem_interface)

# Add support for C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

find_package(ament_cmake REQUIRED)

find_package(rclcpp REQUIRED)
find_package(message_logger REQUIRED)
find_package(soem_ros2 REQUIRED)

set(PACKAGE_DEPENDENCIES message_logger soem_ros2)

set(INCLUDE_DIRS include 
  ${ament_cmake_INCLUDE_DIRS}
  ${message_logger_INCLUDE_DIRS}
  ${soem_ros2_INCLUDE_DIRS})
include_directories(${INCLUDE_DIRS})

message(STATUS "INCLUDE_DIRS - ${INCLUDE_DIRS}")

set(LIBRARY_DIRS ${ament_cmake_LIBRARY_DIRS}
  ${message_logger_LIBRARY_DIRS}
  ${soem_ros2_LIBRARY_DIRS})
link_directories(${LIBRARY_DIRS})

message(STATUS "LIBRARY_DIRS - ${LIBRARY_DIRS}")

set(LIBS ${ament_cmake_LIBRARIES} ${message_logger_LIBRARIES} ${soem_ros2_LIBRARIES})

message(STATUS "LIBS - ${LIBS}")

add_definitions(-std=c++14 -Wall -Werror)
add_definitions(-DMELO_USE_COUT)

include_directories(
  include
  ${soem_ros2_INCLUDE_DIRS}
  ${message_logger_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME} 
  src/${PROJECT_NAME}/common/ThreadSleep.cpp
  src/${PROJECT_NAME}/common/Macros.cpp src/${PROJECT_NAME}/EthercatSlaveBase.cpp
  src/${PROJECT_NAME}/EthercatBusManagerBase.cpp
  src/${PROJECT_NAME}/EthercatBusBase.cpp)
target_link_libraries(${PROJECT_NAME} ${LIBS})

ament_target_dependencies(
  ${PROJECT_NAME}
  rclcpp
  message_logger
  soem_ros2)

install(TARGETS ${PROJECT_NAME}
  ARCHIVE
  DESTINATION lib
  LIBRARY
  DESTINATION lib
  RUNTIME
  DESTINATION lib/${PROJECT_NAME})
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION include/${PROJECT_NAME})

ament_export_dependencies(ament_cmake)
ament_export_dependencies(${PACKAGE_DEPENDENCIES})
ament_export_include_directories(${INCLUDE_DIRS})
ament_export_libraries(${PROJECT_NAME} ${LIBS})

ament_package()
