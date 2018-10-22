#include "ksc/ksc.hpp"

#include <iostream>

#include "std_msgs/msg/string.hpp"
#include "roar_msg/msg/active_vessel_reply.hpp"

using std::placeholders::_1;
using krpc::services::SpaceCenter;

// functionality goes into this file

namespace ksc
{

Ksc::Ksc(krpc::Client connection): Node("ros_ksc_node"), conn{connection}, krpc(&conn), sc(&conn)
{
    // constructor
    std::cout << krpc.get_status().version() << std::endl;

    active_vessel_query_subscription = this->create_subscription<std_msgs::msg::String>(
          "active_vessel_query", std::bind(&Ksc::active_vessel_query_callback, this, _1));
    active_vessel_reply_publisher = this->create_publisher<roar_msg::msg::ActiveVesselReply>("active_vessel_reply");
}

Ksc::~Ksc()
{
}

bool Ksc::vessel_name_in_list(SpaceCenter::Vessel vessel, std::vector<SpaceCenter::Vessel> vessel_list){

    for (SpaceCenter::Vessel cur_vessel : vessel_list) {
        if (cur_vessel.name() == vessel.name()) {
            return true;
        }
    }
    return false;
}

void Ksc::active_vessel_query_callback(const std_msgs::msg::String::SharedPtr msg)
{
    /*
     * retrieves the active vessel and if the msg data is not empty, checks,
     * if the active vessel's name matches.
     * It will also publish a bool, which will be true if and only if there
     * is a second vessel with the active vessel's name.
     */
    bool matches;

    std::string vessel_name = msg->data.c_str();
    std::vector<SpaceCenter::Vessel> all_vessels = sc.vessels();
    SpaceCenter::Vessel active_vessel = sc.active_vessel();

    // check, if active vessel name is unique:
    bool vesselIsUnique = this->vessel_name_in_list(active_vessel, all_vessels);

    if (vessel_name.empty()){
        // just publish active vessel, this will match on any vessel's name as true
        matches = true;
    }
    else {
        // check, if the active vessel's name matches, then publish
        matches = active_vessel.name() == vessel_name;
    }
    RCLCPP_DEBUG(this->get_logger(), "I heard: '%s'", msg->data.c_str());

    // publish response
    roar_msg::msg::ActiveVesselReply reply = roar_msg::msg::ActiveVesselReply();
    reply.name = vessel_name;
    reply.unique = vesselIsUnique;
    reply.matches = matches;
    active_vessel_reply_publisher->publish(reply);
}

}  // namespace ksc
