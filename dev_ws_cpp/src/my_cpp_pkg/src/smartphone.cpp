#include "rclcpp/rclcpp.hpp"   
#include "example_interfaces/msg/string.hpp"   

using namespace std::placeholders;

/*
> Check the package_directory ex: my_cpp_pkg/ is present @at ws_main_dir/src
> Cheate node ex:smartphone.cpp @inside ws_main_dir/src/my_cpp_pkg/src
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
> Receive data from pub_topic: ros2 run node_name
*/

class SmartphoneNode : public rclcpp::Node 
{
public:                  
    SmartphoneNode() : Node("smartphone") //constructuor
    {
        // initialise subscriber
        // subscriber_name_ = explitly->create_subscription<type>("same_name_as_pub_topic", queue size, callback)
        subscriber_=this->create_subscription<example_interfaces::msg::String>(
            "robot_news", 10, 
            std::bind(&SmartphoneNode::callbackRobotNews, this, std::placeholders::_1)); 
            // if place holder more than 1 => (...this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3...));
        // confirmation logs: the node has started successfully
        RCLCPP_INFO(this->get_logger(), "Smartphone has been started.");
    } 
 
private:
    void callbackRobotNews(const example_interfaces::msg::String::SharedPtr msg) //callback when node spins
    // callback_func(msg1_type shsredPtr_passthrough msg1, msg2_type msg2, msg3_type msg3,...)
    {
        RCLCPP_INFO(this->get_logger(), "%s", msg->data.c_str());
    }
    // create subscriber as shared_pointer
    rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr subscriber_;
    // rclcpp::subscription_obj<interfaces>::SharedPtr_passtgrough subscriber_name_;
};
 
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SmartphoneNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}