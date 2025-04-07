#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import String
 
 
class SmartphoneNode(Node): 
    def __init__(self):
        super().__init__("smartphone") # MODIFY NAME
        self.subscriber_ = self.create_subscription(
            String, "robot_news", self.callback_robot_news, 10) # (datatype, topic_name, callback_function, queue size) 
        self.get_logger().info("Smartphone has been started")
            
    def callback_robot_news(self, msg: String):   #callback is req for knowing msg published
        self.get_logger().info(msg.data)  # Check example_interfaces.msg for initialising variable_type
 
def main(args=None):
    rclpy.init(args=args)
    node = SmartphoneNode()
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()
