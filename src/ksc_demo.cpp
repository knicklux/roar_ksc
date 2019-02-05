#include "ksc/ksc_demo.hpp"

#include <iostream>

#include "std_msgs/msg/string.hpp"
#include "roar_msg/msg/active_vessel_reply.hpp"

using std::placeholders::_1;

// functionality goes into this file

namespace ksc
{

KscDemo::KscDemo(): Node("ksc_demo_node")
{
    active_vessel_query_publisher = this->create_publisher<std_msgs::msg::String>("active_vessel_query");
    active_vessel_reply_subscription = this->create_subscription<roar_msg::msg::ActiveVesselReply>(
          "active_vessel_reply", std::bind(&KscDemo::active_vessel_reply_callback, this, _1));
}

KscDemo::~KscDemo()
{
}

void KscDemo::active_vessel_reply_callback(const roar_msg::msg::ActiveVesselReply::SharedPtr msg) {
    std::string name = msg->name;
    bool matches = msg->matches;
    bool unique = msg->unique;
    std::cout << "Active vessel: " << name << " matches: " << matches << " is unique: " << unique;
}

void KscDemo::publish_active_vessel_query(const std::string &expected_name) {
    std_msgs::msg::String msg = std_msgs::msg::String();
    msg.data = expected_name.c_str();
    active_vessel_query_publisher->publish(msg);
}

}
