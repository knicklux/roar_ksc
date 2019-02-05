#ifndef KSC__KSC_HPP_
#define KSC__KSC_HPP_

#include "ksc/visibility_control.h"
#include "rclcpp/rclcpp.hpp"

#include "std_msgs/msg/string.hpp"
#include "roar_msg/msg/active_vessel_reply.hpp"

#include <krpc.hpp>
#include <krpc/services/krpc.hpp>
#include <krpc/services/space_center.hpp>

namespace ksc
{

class KscDemo : public rclcpp::Node
{
public:
  KscDemo();

  virtual ~KscDemo();

  void publish_active_vessel_query(const std::string& expected_name);

private:

  void active_vessel_reply_callback(const roar_msg::msg::ActiveVesselReply::SharedPtr msg);

  rclcpp::Publisher<std_msgs::msg::String>::SharedPtr active_vessel_query_publisher;
  rclcpp::Subscription<roar_msg::msg::ActiveVesselReply>::SharedPtr active_vessel_reply_subscription;
};

}  // namespace ksc

#endif  // KSC__KSC_HPP_
