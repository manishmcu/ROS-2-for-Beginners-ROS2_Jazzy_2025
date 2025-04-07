#include "rclcpp/rclcpp.hpp"    // dep1: rclcpp
#include "example_interfaces/msg/string.hpp"   //dep2: example_interfaces

using namespace std::chrono_literals; // cpp_timer from namespace
 
/*
> Check the package_directory ex: my_cpp_pkg/ is present @at ws_main_dir/src
> Cheate node ex:robot_news_station.cpp @inside ws_main_dir/src/my_cpp_pkg/src
> Come back to ws_main_dir/src and @open vscode: <code .>
> Use template, save the code, wait for @auto_compilation.
> Check @datatype: ros2 interface show example_interfaces/msg/String.

> 1.1 package.xml: Add @dependencies@ ex: <depend>rclcpp</depend>

> 2.1 CMakeLists.txt: Link dependencies @find_package(dependency, REQUIRED)
> 2.2 CMakeLists.txt: add_executable(executable_name path_of_file)
> 2.3 CMakeLists.txt: ament_target_dependencies(executable_name dep1 dep2 dep3 ...)
> 2.4 CMakeLists.txt: add executable_name to install(TARGETS... )

> Go to: ws_main_dir
> Build: colcon build --packages-select cpp_pachage_name
> Source: source install/setup.bash
> Run: ros2 run cpp_pachage_name executable_name
> Check running_nodes list: ros2 node list 
> Check topics of the running_nodes: ros2 topic list
> Check the pub_topic data: ros2 echo topic_name
*/

class RobotNewsStationNode : public rclcpp::Node 
{
public:
    RobotNewsStationNode() : Node("robot_news_station"), robot_name_("R2D2") // 'robot_news_station' -> node_executable_name
    {
        // initialise publisger in constructor

        // pub_class_attribute_ = explicitly_says->create_publisher_method<interface>("topic_name", queue_size);
        publisher_ = this->create_publisher<example_interfaces::msg::String>("robot_news", 10); // 'robot_news' -> pub_topic_name
        // initialise_timer_ = explicitly_says->cpp_tiimer(time, std::bind(&callback_reference, explicitly_says));
        timer_ = this->create_wall_timer(0.5s, std::bind(&RobotNewsStationNode::publishNews, this)); 
        // confirmation logs: the node has started successfully
        RCLCPP_INFO(this->get_logger(), "Robot News Station has been started");   
    }
 
private:  
    void publishNews()
    {
        // msg_type msg = interfaces();
        auto msg = example_interfaces::msg::String();
        // msg.data = msg_type(message);
        msg.data = std::string("Hi, this is ") + robot_name_ + std::string(" from the robot");
        // method_->to_publish(message);
        publisher_->publish(msg);
    }
    std::string robot_name_;
    // declear PUBLISHER using shared_pointer//
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;  // rclcpp::publisher_class<interface::msg::msg_type>::to_shared_point pub_class_attribute;
    // create a shared_pointer for timer_;
    rclcpp::TimerBase::SharedPtr timer_;
};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<RobotNewsStationNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}