import rclpy
from rclpy.node import Node
import requests
from example_interfaces.msg import String
from queue import Queue

class NovelPubNode(Node):
    def __init__(self, node_name):
        super().__init__(node_name)     # 继承父类的构造函数
        self.get_logger().info(f'{node_name} is open!')
        self.novels_queue_ = Queue()
        self.novel_publisher_ = self.create_publisher(String, 'novel', 10)  # 发布话题
        self.create_timer(5, self.timer_callback)   # 间隔5s执行一次回调

    def timer_callback(self):
        # self.novel_publisher_.publish()
        if self.novels_queue_.qsize() > 0:
            line = self.novels_queue_.get()
            msg = String()      # 组装为消息
            msg.data = line
            self.novel_publisher_.publish(msg)
            self.get_logger().info(f'publish:{msg}')

    def download(self, url):
        response = requests.get(url)    # 获取数据
        response.encoding = 'utf-8'
        text = response.text

        self.get_logger().info(f'download{url}, {len(text)}')
        for line in text.splitlines():      # 按行分割
            self.novels_queue_.put(line)    # 放到队列


def main():
    rclpy.init()
    node = NovelPubNode('novel_pub')
    node.download('http://127.0.0.1:8000/novel1.txt')
    rclpy.spin(node)
    rclpy.shutdown()



