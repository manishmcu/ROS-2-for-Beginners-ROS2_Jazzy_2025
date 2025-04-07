#!/usr/bin/env python3
import rclpy
from rclpy.node import Node  ### import Node class from rclpy.node

class MyNode(Node):  ## Inhrite from Node class
    def __init__(self):  ## constructor
        super().__init__("py_test")           ### <<NODE NAME>> "py_test" inside the <<file_name>> "my_first_node"
        self.counter_ = 0
        self.get_logger().info("Hello World") ### printing on terminal
        self.create_timer(1.0, self.timer_callback) ## (delay, referance_of_function) till node alive, it will be call
        
    def timer_callback(self):
        self.get_logger().info("Hello manish" + str(self.counter_))
        self.counter_ +=1


def main(args=None):
    rclpy.init(args=args)     ### initialize ros2 communication
    # node = Node("py_test")  
    node = MyNode()           ### using our own class, that inheriting from Node
    rclpy.spin(node)          ### spin used for making node alive
    rclpy.shutdown   
    
if __name__  == "__main__":
    main()        ## main function to run functioality directly from terminal
    
