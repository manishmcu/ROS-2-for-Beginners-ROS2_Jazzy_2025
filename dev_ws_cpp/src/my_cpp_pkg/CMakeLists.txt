cmake_minimum_required(VERSION 3.8)
project(my_cpp_pkg)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(example_interfaces REQUIRED) # from robot_news_station

add_executable(cpp_node src/my_first_node.cpp)  # exe_line1: (executable_name path_of_file)
ament_target_dependencies(cpp_node rclcpp)      # exe_line2: add dependencies>> (executable_name dep1 dep2 dep3 ...)

add_executable(robot_news_station src/robot_news_station.cpp)
ament_target_dependencies(robot_news_station rclcpp example_interfaces)

add_executable(smartphone src/smartphone.cpp)
ament_target_dependencies(smartphone rclcpp example_interfaces)

install(TARGETS
  cpp_node
  robot_news_station
  smartphone
  # next_exe1
  # next_exe2
  # ...
  DESTINATION lib/${PROJECT_NAME}
)

ament_package()
