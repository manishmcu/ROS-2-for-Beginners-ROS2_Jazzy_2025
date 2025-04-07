#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import String
 
class RobotStationNode(Node): # MODIFY NAME
    def __init__(self):
        super().__init__("robot_news_station") # MODIFY EXECUTABLE NAME
        self.counter_ = 0
        self.robot_name_ = "C3P0"
        self.publishers_ = self.create_publisher(String, "robot_news", 10)  # (datatype, topic_name, queue size)
        self.timer_ = self.create_timer(0.5, self.publish_news)
        self.get_logger().info("Robot News has been started")
        self.create_timer(1.0, self.publish_news)
        
    def publish_news(self):
        msg = String()
        msg.data = "Hi, this is " + self.robot_name_+ str(self.counter_) + " from robot news station"   # Check example_interfaces.msg for initialising variable_type
        self.counter_ +=1
        self.publishers_.publish(msg)
 
def main(args=None):
    rclpy.init(args=args)
    node = RobotStationNode() # MODIFY NAME
    rclpy.spin(node)
    rclpy.shutdown()
 
 
if __name__ == "__main__":
    main()
