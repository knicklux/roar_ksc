#include "ksc/ksc.hpp"

#include <iostream>
#include <krpc.hpp>
#include <krpc/services/krpc.hpp>

using std::placeholders::_1;

// functionality goes into this file

namespace ksc
{

Ksc::Ksc(): Node("ros_ksc_node")
{
    // constructor
    auto conn = krpc::connect("ros_ksc_node", "127.0.0.1", 1000, 1001);
    krpc::services::KRPC krpc(&conn);
//    krpc::services::SpaceCenter sc(&conn);
    std::cout << krpc.get_status().version() << std::endl;

    subscription_ = this->create_subscription<std_msgs::msg::String>(
          "topic", std::bind(&Ksc::topic_callback, this, _1));
}

Ksc::~Ksc()
{
}

void Ksc::topic_callback(const std_msgs::msg::String::SharedPtr msg)
{
  RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
}

}  // namespace ksc
