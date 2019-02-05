#include <cstdio>

#include "ksc/ksc_demo.hpp"

#include <krpc.hpp>
#include <krpc/services/krpc.hpp>

// "main" in ros 2

int main(int argc, char ** argv)
{
    (void) argc;
    (void) argv;

    rclcpp::init(argc, argv);

    std::shared_ptr<ksc::KscDemo> node = std::make_shared<ksc::KscDemo>();
    bool should_exit = false;
    std::string vessel_name = "";

    while(!should_exit) {
        // node->publish_active_vessel_query("apollo");
        std::cout << "enter vessel name:\n" << std::flush;
        getline(std::cin, vessel_name);
        node->publish_active_vessel_query(vessel_name);
    }

    rclcpp::shutdown();

    return 0;
}
