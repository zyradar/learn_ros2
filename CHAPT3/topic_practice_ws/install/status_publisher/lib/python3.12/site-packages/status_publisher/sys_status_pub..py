import rclpy
from status_interfaces.msg import SystemStatus  # 自定义接口功能包
from rclpy.node import Node                     # 节点
import psutil                                   # 获取系统信息
import platform                                 # 获取订阅的话题名

class SysStatusPub(Node):
    def __init__(self, noed_name):
        super().__init__(noed_name)             # 调用父类
        # 定义状态发布者
        self.status_publisher_ = self.create_publisher(SystemStatus, 'sys_status', 10)
        self.timer_ = self.create_timer(1.0, self.timer_callback)   # 创建定时器

    def timer_callback(self):
        """
        builtin_interfaces/Time stamp   # 记录时间戳
        string host_name                # 主机名字
        float32 cpu_percent             # CPU使用率
        float32 memory_percent          # 内存使用率
        float32 memory_total            # 内存总大小
        float32 memory_available        # 有效内存
        float64 net_sent                # 网络发送数据总量 1Mb = 8Mb
        float64 net_recv                # 网络数据接受总量  Mb
        """
        cpu_percent = psutil.cpu_percent()          # 获取CPU使用率
        memory_info = psutil.virtual_memory()       # 获取系统内存相关信息
        ne_ip_counters = psutil.net_io_counters()   # 获取网络相关IO信息

        msg = SystemStatus()                        # 创建消息类
        msg.stamp = self.getclock().now().to_msg()  # 获取时间戳
        msg.host_name = platform.node()             # 获取网络主机名
        msg.cpu_percent = cpu_percent
        msg.memory_percent = memory_info.percent()
        msg.memory_total = memory_info.memory_total()
        msg.memory_available = memory_info.memory_available()
        msg.net_sent = ne_ip_counters.bytes_sent / 1024 / 1024
        msg.net_recv = ne_ip_counters.bytes_recv / 1024 / 1024

        self.get_logger().info(f'publish:{str(msg)}')
        self.status_publisher_.publish(msg)

def main():
    rclpy.init()
    node = SysStatusPub('sys_status_pub')
    rclpy.spin(node)
    rclpy.shutdown()

