//#include <cstdio>
//#include <memory>
//#include <string>

//#include "dynamixel_sdk/dynamixel_sdk.h"
#include "dynamixel_sdk_custom_interfaces/msg/set_position.hpp"
#include "dynamixel_sdk_custom_interfaces/srv/get_position.hpp"
#include "rclcpp/rclcpp.hpp"
#include "rcutils/cmdline_parser.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "example_interfaces/msg/string.hpp"

class TrajectoryGen : public rclcpp::Node // MODIFY NAME
{
public:
  TrajectoryGen() : Node("trajectory_generator") // MODIFY NAME
  {
    //publisher_ = this->create_publisher<example_interfaces::msg::String>("motor_pos", 10);
    publisher_ = this->create_publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>("set_position", 10);
    //publisher_ = this->create_publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>("set_position", 10);
    //create_publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>("set_position", 10) publisher_;
    timer_ = this->create_wall_timer(std::chrono::milliseconds(10), std::bind(&TrajectoryGen::publishPos, this));
    //auto timer_ = this->create_wall_timer(std::chrono::milliseconds(10), std::bind(&TrajectoryGen::publishPos2, this));
    //rclcpp::Time now = this->get_clock()->now();
    
    RCLCPP_INFO(this->get_logger(), "trajectory generator has started");
  }
private:
  void publishPos()
  {
    time += 0.01;
    auto pos = dynamixel_sdk_custom_interfaces::msg::SetPosition();
    pos.id = 3;
    pos.position = int((sin(time)/2+0.5)*250+590);//650-840;
    publisher_->publish(pos);

    /*auto pos2 = dynamixel_sdk_custom_interfaces::msg::SetPosition();
    pos2.id = 4;
    pos2.position = int((sin(time)/2+0.5)*250+590);
    publisher_->publish(pos2);*/

  }

  /*void publishPos2()
  {
    time += 0.01;
    auto pos = dynamixel_sdk_custom_interfaces::msg::SetPosition();
    pos.id = 4;
    pos.position = int((sin(time)/2+0.5)*250+590);//650-840;                                                          
    publisher_->publish(pos);
    }*/


  //auto pos = dynamixel_sdk_custom_interfaces::msg::SetPosition();
  //dynamixel_sdk_custom_interfaces::msg::SetPosition() pos[2];
  double time = 0.0;
  rclcpp::Publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};
  
int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TrajectoryGen>(); // MODIFY NAME
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
