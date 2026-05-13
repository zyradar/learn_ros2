import rclpy
from rclpy.node import Node

if __name__ == "__main__":
    rclpy.init()        # 初始化工作，分配资源
    node = Node('python_node')
    node.get_logger().info('hello python node!!')
    node.get_logger().warning('hello python node!!')
    rclpy.spin(node)
    rclpy.shutdown()

