import rclpy
from rclpy.node import Node
from example_interfaces.msg import String
from queue import Queue
import threading
import espeakng


class NovelSubNode(Node):
    def __init__(self, node_name):
        super().__init__(node_name)     # 继承父类的构造函数
        self.get_logger().info(f'{node_name}open')
        self.novels_queue_ = Queue()
        # 订阅话题
        self.novel_subscriber_ = self.create_subscription(String, 'novel', self.novel_callback, 10)
        self.speak_thread_ = threading.Thread(target=self.speaker_thread)


    def novel_callback(self, msg):
        self.novels_queue_.put(msg.data)

    def speaker_thread(self):
        speaker = espeakng.Speaker()
        speaker.voice = 'zh'

        while rcl

def main():
    rclpy.init()
    node = NovelSubNode('novel_sub')
    rclpy.spin(node)
    rclpy.shutdown()