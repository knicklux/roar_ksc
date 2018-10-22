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

class Ksc : public rclcpp::Node
{
public:
  Ksc(krpc::Client connection);

  virtual ~Ksc();

private:

  bool vessel_name_in_list(krpc::services::SpaceCenter::Vessel vessel, std::vector<krpc::services::SpaceCenter::Vessel> vessel_list);
  void active_vessel_query_callback(const std_msgs::msg::String::SharedPtr msg);

  rclcpp::Subscription<std_msgs::msg::String>::SharedPtr active_vessel_query_subscription;
  rclcpp::Publisher<roar_msg::msg::ActiveVesselReply>::SharedPtr active_vessel_reply_publisher;

  krpc::Client conn;
  krpc::services::KRPC krpc;
  krpc::services::SpaceCenter sc;
};

}  // namespace ksc

#endif  // KSC__KSC_HPP_
