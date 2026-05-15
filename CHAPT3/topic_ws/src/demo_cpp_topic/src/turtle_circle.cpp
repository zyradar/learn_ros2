#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <chrono>

using namespace std::chrono_literals;       // 命名空间将参数自动转换为操作符

class TurtlrCircleNode: public rclcpp::Node     // 继承来自rclcpp下的Node节点
{
    private:
    /* 声明变量 */
        // 先创建共享指针，不赋值
        rclcpp::TimerBase::SharedPtr timer_;    // 定时器指针
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;  // 发布者只能是指针
    public:
        explicit TurtlrCircleNode(const std::string& node_name):Node(node_name)
        {
            // 共享指针赋值
            publisher_ = this-> create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
            timer_ = this -> create_wall_timer(1000ms, std::bind(&TurtlrCircleNode::timer_callback, this));
            // this : 指向当前对象的指针
        }
        
        // 成员函数
        void timer_callback()
        {
            auto msg = geometry_msgs::msg::Twist();
            msg.linear.x = 1.0;
            msg.angular.z = 0.5;
            publisher_ -> publish(msg);
        }
};


int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtlrCircleNode>("turtle_circle");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
