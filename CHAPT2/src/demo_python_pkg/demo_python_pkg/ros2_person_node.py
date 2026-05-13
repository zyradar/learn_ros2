import rclpy
from rclpy.node import Node

class PresonNode(Node):
    def __init__(self, node_name:str, name_value:str, age_value:int) -> None:
        super().__init__(node_name) # 继承父类
        self.name = name_value
        self.age = age_value
        
    def eat(self, food_name: str):
        """
        方法：吃东西
        """
        print(f"{self.name}, {self.age}, {food_name}")
        self.get_logger().info(f"{self.name}, {self.age}")

def main():
    rclpy.init()
    node = PresonNode("test_san", "san", 18)
    node.eat('fish')
    rclpy.spin(node)
    print('----')
    node.destroy_node()
    rclpy.shutdowm()

