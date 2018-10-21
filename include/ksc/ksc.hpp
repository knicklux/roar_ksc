#ifndef KSC__KSC_HPP_
#define KSC__KSC_HPP_

#include "ksc/visibility_control.h"
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

namespace ksc
{

class Ksc : public rclcpp::Node
{
public:
  Ksc();

  virtual ~Ksc();

private:

  void topic_callback(const std_msgs::msg::String::SharedPtr msg);
  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

}  // namespace ksc

#endif  // KSC__KSC_HPP_
