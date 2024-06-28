### ROS1和ROS2有什么区别
1. 通信中间件（DDS vs. ROS1 Master）
ROS1 使用一个名为 "ROS Master" 的中心化节点注册和消息传递系统。所有的节点都必须通过ROS Master来交换信息，这种中心化的设计使得系统容易受到单点故障的影响。
ROS2 采用了DDS（Data Distribution Service）作为其底层的通信中间件。DDS是一个基于发布/订阅模式的分布式通信系统，它提供了更好的实时性、更高的可靠性和可伸缩性，以及跨多种操作系统和网络配置的互操作性。
2. 实时性能
ROS1 在设计时没有考虑实时性能，这使得它在需要严格实时性保证的应用中不是理想选择。
ROS2 设计时考虑了实时应用的需求，它支持实时编程，使得开发者能够创建满足实时性要求的机器人应用。
3. 跨平台支持
ROS1 主要支持Ubuntu和其他少数Linux发行版。
ROS2 支持更广泛的平台，包括Windows、macOS和多种Linux发行版，从而为开发者提供了更多的灵活性和选择。
4. 安全性
ROS1 缺乏安全特性，不支持消息加密或认证，这在商业和工业应用中是一个重大缺陷。
ROS2 在安全性方面有了显著改进，它支持基于DDS的安全通信协议，可以进行节点身份认证、消息加密等，从而更适合于安全性要求较高的应用环境。
5. 节点管理和服务
ROS1 的节点管理较为简单，主要依赖于ROS Master进行节点的注册和管理。
ROS2 引入了新的节点生命周期管理方式，允许更精细的控制和管理节点的状态，这对于构建更复杂的系统非常有用。

### ROS 订阅接收例子

1. 创建一个新的ROS2包
首先，创建一个名为example_interfaces的新ROS2包：

```bash
mkdir -p ~/ros2_ws/src
cd ~/ros2_ws/src
ros2 pkg create example_interfaces --build-type ament_cmake --dependencies rclcpp std_msgs
```
2. 定义消息类型
假设我们使用标准消息类型，因此无需创建新的消息类型。我们将使用`std_msgs/msg/String`。

3. 创建发布者 (Publisher)
编辑example_interfaces/src/publisher.cpp，添加以下代码：

```cpp
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class MyPublisher : public rclcpp::Node
{
public:
    MyPublisher() : Node("publisher_node"), count_(0)
    {
        publisher_ = this->create_publisher<std_msgs::msg::String>("topic", 10);
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&MyPublisher::publish_message, this));
    }

private:
    void publish_message()
    {
        auto message = std_msgs::msg::String();
        message.data = "Hello, world! " + std::to_string(count_++);
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        publisher_->publish(message);
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
    size_t count_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
```
4. 创建订阅者 (Subscriber)
编辑example_interfaces/src/subscriber.cpp，添加以下代码：

```cpp
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class MySubscriber : public rclcpp::Node
{
public:
    MySubscriber() : Node("subscriber_node")
    {
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "topic", 10, std::bind(&MySubscriber::topic_callback, this, std::placeholders::_1));
    }

private:
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
    {
        RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
    }

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MySubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
```
5. 编译和运行
首先，在`example_interfaces/CMakeLists.txt`文件中，确保你的发布者和订阅者节点被正确地添加到构建配置中：

```cmake
add_executable(publisher src/publisher.cpp)
ament_target_dependencies(publisher rclcpp std_msgs)

add_executable(subscriber src/subscriber.cpp)
ament_target_dependencies(subscriber rclcpp std_msgs)

install(TARGETS
  publisher
  subscriber
  DESTINATION lib/${PROJECT_NAME}
)
```

现在，在你的工作空间中构建并运行节点：

```bash
cd ~/ros2_ws
colcon build --packages-select example_interfaces
. install/setup.bash
ros2 run example_interfaces publisher
```
在另一个终端中，运行订阅者：
```bash
. install/setup.bash
ros2 run example_interfaces subscriber
```
现在，发布者节点每秒会向topic主题发送一条消息，订阅者节点会接收这些消息并打印出来。这个例子展示了如何在ROS2中设置基本的发布和订阅机制。