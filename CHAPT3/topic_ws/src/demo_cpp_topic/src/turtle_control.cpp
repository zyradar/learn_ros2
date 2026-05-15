#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <chrono>
#include "turtlesim/msg/pose.hpp"

using namespace std::chrono_literals;       // 命名空间将参数自动转换为操作符

class TurtlrControlNode: public rclcpp::Node     // 继承来自rclcpp下的Node节点
{
    private:
    /* 声明变量 */
        // 先创建共享指针，不赋值
        // rclcpp::TimerBase::SharedPtr timer_;    // 定时器指针
        rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;     // 发布者的智能共享指针
        rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscriber_;      // 订阅者的智能共享指针
        double target_x_{1.0};
        double target_y_{1.0};
        double k_{1.0};             // 比例系数
        double max_speed_{3.0};     // 最大速度
        // double max_ang_{};
    public:
        explicit TurtlrControlNode(const std::string& node_name):Node(node_name)
        {
            // 共享指针赋值
            publisher_ = this-> create_publisher<geometry_msgs::msg::Twist>("/turtle1/cmd_vel", 10);
            subscriber_ = this -> create_subscription<turtlesim::msg::Pose>("/turtle1/pose"
                            , 10, std::bind(&TurtlrControlNode::on_pose_received_, this));
            // timer_ = this -> create_wall_timer(1000ms, std::bind(&TurtlrControlNode::timer_callback, this));
            // this : 指向当前对象的指针
        }
        
        // 成员函数, 参数：收到数据的共享指针
        void on_pose_received_(const turtlesim::msg::Pose::SharedPtr pose)
        {
            // 获取当前位置
            auto current_x = pose -> x;
            auto current_y = pose -> y;
            RCLCPP_INFO(get_logger(), "now:x=%f, y=%f", current_x, current_y);

            // 计算当前海龟位置与目标位置差
            auto distance = std::sqrt(
                (target_x_ - current_x) * (target_x_ - current_x)+
                (target_y_ - current_y) * (target_y_ - current_y)
            );
            auto angle = std::atan2(
                (target_y_ - current_y), (target_x_ - current_x)
            ) - pose->theta;

            // 控制策略
            auto msg = geometry_msgs::msg::Twist();
            if(distance > 0.1)
            {
                if(fabs(angle) > 0.2)
                {
                    msg.angular.z = fabs(angle);
                }
                else
                {
                    msg.linear.x = k_ * distance;
                }
            }

            // 限制线速度最大值
            if(msg.linear.x > max_speed_)
            {
                msg.linear.x = max_speed_;
            }
            
            // 发布话题
            publisher_->publish(msg);
        }
};


int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<TurtlrControlNode>("turtle_control");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
