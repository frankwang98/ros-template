#include <iostream>
#include <chrono>
#include <sys/time.h>

#include <ros/ros.h>

using namespace std;
    
int main(int argc,char **argv){   
    
    ros::init(argc,argv,"hello_ros");   
    
    ros::NodeHandle nh;   

    ROS_INFO_STREAM("hello,ROS!");

    // c++ timestamp
    uint64_t sys_time = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    int32_t time_second = sys_time / 1000000;
    int32_t time_nsecs = sys_time % 1000000 * 1000;
    double timestamp = (double)time_second + 1e-9 * (double)time_nsecs;
    cout.precision(50);
    cout << "c++ time:" << sys_time << " time_second:" << time_second << " time_nsecs:" << time_nsecs << endl;
    cout << "c++ timestamp:" << timestamp << endl;

    // ros timestamp
    double ros_sys_time_sec = ros::Time::now().toSec();
    cout << "ros_sys_time_sec:" << ros_sys_time_sec << endl;
    ros::Time to_ros_time = ros::Time(time_second, time_nsecs);
    cout << "to_ros_time:" << to_ros_time.toSec() << endl;

    // c timestamp
    struct timeval ctime;
    gettimeofday(&ctime, NULL);
    double ctimestamp = (double)ctime.tv_sec + 1e-6 * (double)ctime.tv_usec;
    cout << "ctime second:" << ctime.tv_sec << " tv_usec:" << ctime.tv_usec << endl;
    cout << "ctimestamp:" << ctimestamp << endl;

    // 获取rostopic的时间戳
    /*
    msg会定义消息头，包含时间戳信息：
    Header header
    然后在代码里获取时间戳：
    video_info_msg_info.header.stamp.sec=sec;
    video_info_msg_info.header.stamp.nsec=nsec;
    video_info_msg_info.header.stamp = ros::Time::now();
    需要添加std_msgs依赖
    */

    return 0;
}