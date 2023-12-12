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

#include <chrono>
#include <thread>

class TrajectoryGen : public rclcpp::Node // MODIFY NAME
{
public:
  TrajectoryGen() : Node("trajectory_generator") // MODIFY NAME
  {
    //publisher_ = this->create_publisher<example_interfaces::msg::String>("motor_pos", 10);
    publisher1_ = this->create_publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>("set_position", 1);
    publisher2_ = this->create_publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>("set_position", 1);
    publisher3_ = this->create_publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>("set_position", 1);
    //create_publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>("set_position", 10) publisher_;
    //timer2_ = this->create_wall_timer(std::chrono::milliseconds(10), std::bind(&TrajectoryGen::publishPos2, this));
    timer1_ = this->create_wall_timer(std::chrono::milliseconds(60), std::bind(&TrajectoryGen::publishPos, this));
    //auto timer_ = this->create_wall_timer(std::chrono::milliseconds(10), std::bind(&TrajectoryGen::publishPos, this));
    //rclcpp::Time now = this->get_clock()->now();
    /*rclcpp::Clock simTime;
      this->NodeClock();*/
    RCLCPP_INFO(this->get_logger(), "trajectory generator has started");
    /*while(1)
    {
      publishPos1();
      publishPos2();
      }*/
  }
private:
  void publishPos()
  {
    //using namespace std::this_thread;
    //using namespace std::chrono;
    time += 0.1;
    publishPos1();
    //sleep_for(nanoseconds(10));
    //sleep_until(system_clock::now() + nanoseconds(1000));
    publishPos2();
    publishPos3();
  }
  void publishPos1()
  {
    //time += 0.00001;
    auto pos1 = dynamixel_sdk_custom_interfaces::msg::SetPosition();
    pos1.id = 4;
    uint16_t min = 490;
    uint16_t range = 330;
    pos1.position = int((sin(time)/2+0.5)*range+min);//650-840;
    publisher1_->publish(pos1);
  }

  void publishPos2()
  {
    //time += 0.01;
    auto pos2 = dynamixel_sdk_custom_interfaces::msg::SetPosition();
    pos2.id = 3;
    pos2.position = int((-sin(time)/2+0.5)*250+620);//650-840;                                                          
    publisher2_->publish(pos2);
    }

  void publishPos3()
  {
    //time += 0.01;                                                                                                   
    auto pos3 = dynamixel_sdk_custom_interfaces::msg::SetPosition();
    pos3.id = 6;
    pos3.position = int((-sin(time)/2+0.5)*130+570);//650-840; 
    publisher3_->publish(pos3);
    }

  double time = 0.0;

  rclcpp::Publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>::SharedPtr publisher3_;
  
  rclcpp::Publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>::SharedPtr publisher2_;
  //rclcpp::TimerBase::SharedPtr timer2_;

  rclcpp::Publisher<dynamixel_sdk_custom_interfaces::msg::SetPosition>::SharedPtr publisher1_;
  rclcpp::TimerBase::SharedPtr timer1_;
};
  
int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  auto node = std::make_shared<TrajectoryGen>(); // MODIFY NAME
  rclcpp::spin(node);
  rclcpp::shutdown();
  return 0;
}
