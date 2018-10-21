#include <cstdio>

#include "ksc/ksc.hpp"

#include <krpc.hpp>
#include <krpc/services/krpc.hpp>

// "main" in ros 2

int main(int argc, char ** argv)
{
    (void) argc;
    (void) argv;

    krpc::Client conn = krpc::connect("My Example Program", "192.168.1.10", 1000, 1001);

    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ksc::Ksc>(conn));
    rclcpp::shutdown();

    return 0;
}
