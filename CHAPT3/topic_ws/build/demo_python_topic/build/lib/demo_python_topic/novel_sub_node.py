import rclpy
from rclpy.node import Node
from example_interfaces.msg import String
from queue import Queue
import threading
import espeakng
import time


class NovelSubNode(Node):
    def __init__(self, node_name):
        super().__init__(node_name)     # 继承父类的构造函数
        self.get_logger().info(f'{node_name} is open!')
        self.novels_queue_ = Queue()
        # 订阅话题
        self.novel_subscriber_ = self.create_subscription(String, 'novel', self.novel_callback, 10)
        self.speak_thread_ = threading.Thread(target=self.speaker_thread)
        self.speak_thread_.start()

    def novel_callback(self, msg):
        self.novels_queue_.put(msg.data)

    def speaker_thread(self):
        speaker = espeakng.Speaker()
        speaker.voice = 'zh'

        while rclpy.ok():   # 检测当前ROS上下文是否OK
            if self.novels_queue_.qsize() > 0:
                text = self.novels_queue_.get()
                self.get_logger().info(f'read:{text}')
                speaker.say(text)       # 说
                speaker.wait()          # 等待说完
            else:
                # 让当前的线程休眠1s
                time.sleep(1)

def main():
    rclpy.init()
    node = NovelSubNode('novel_sub')
    rclpy.spin(node)
    rclpy.shutdown()