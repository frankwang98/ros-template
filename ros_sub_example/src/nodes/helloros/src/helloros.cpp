#include <iostream>
#include <chrono>
#include <sys/time.h>

#include <ros/ros.h>
#include "msg_system_vehicle/msg_system_vehicle.h"

using namespace std;

void callback(const msg_system_vehicle::msg_system_vehicle::ConstPtr& msg) {
    
    msg_system_vehicle::msg_system_vehicle msg_system_vehicle_;
    msg_system_vehicle_ = *msg;
    cout << "Receving..." << endl;
    for (std::size_t i = 0; i<msg_system_vehicle_.system_vehicles.size(); i++) {
        cout << "system_vehicle_x: " << msg_system_vehicle_.system_vehicles.at(i).x << endl;
        cout << "system_vehicle_y: " << msg_system_vehicle_.system_vehicles.at(i).y << endl;
        cout << "system_vehicle_yaw: " << msg_system_vehicle_.system_vehicles.at(i).heading_angle << endl;
    }
}
    
int main(int argc,char **argv){   
    
    ros::init(argc,argv,"hello_ros");   
    
    ros::NodeHandle nh;   

    msg_system_vehicle::msg_system_vehicle msg_system_vehicle_;

    ros::Subscriber sub = nh.subscribe("truck_6/msg_system_vehicle",1000,callback);

    ros::spin();

    ROS_INFO_STREAM("hello,ROS!");

    return 0;
}
