#include <cstdio>
#include <iostream>

#include "ksc/ksc.hpp"

#include <krpc.hpp>
#include <krpc/services/krpc.hpp>

// "main" in ros 2

int main(int argc, char ** argv)
{
    (void) argc;
    (void) argv;

    std::cout << "connecting...\n";
    krpc::Client conn = krpc::connect("My Example Program", "127.0.0.1", 50000, 50001);

    std::cout << "starting node\n";
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ksc::Ksc>(conn);
    std::cout << "running...\n";
    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}
