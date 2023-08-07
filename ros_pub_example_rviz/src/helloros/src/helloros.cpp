#include <iostream>
#include <chrono>
#include <sys/time.h>
#include <fstream>

#include <ros/ros.h>
#include <visualization_msgs/Marker.h>

using namespace std;

void displayMap()
{
  // 创建ROS节点
  ros::NodeHandle nh;
  ros::Publisher marker_pub = nh.advertise<visualization_msgs::Marker>("map_marker", 10);

  // 创建Marker消息 - frame_id stamp ns action type
  visualization_msgs::Marker marker;
  marker.header.frame_id = "map";
  marker.header.stamp = ros::Time();
//   marker.ns = "map_markers";
  marker.action = visualization_msgs::Marker::ADD;
  marker.type = visualization_msgs::Marker::POINTS;

  // 设置点的大小和颜色
  marker.scale.x = 0.1;
  marker.scale.y = 0.1;
  marker.color.r = 1.0;
  marker.color.g = 0.0;
  marker.color.b = 0.0;
  marker.color.a = 1.0;

  // 读取txt文件
  std::string file_path = "map.txt";
  std::ifstream file(file_path.c_str());
  if (!file)
  {
    ROS_ERROR_STREAM("Failed to open file: " << file_path);
    return;
  }

  std::string line;
  while (std::getline(file, line))
  {
    std::istringstream iss(line);
    float x, y;
    if (!(iss >> x >> y))
      break;

    geometry_msgs::Point point;
    point.x = x;
    point.y = y;
    point.z = 0.0;
    std::cout << "map " << "x: " << x << " y: " << y << std::endl;
    marker.points.push_back(point);
  }

  file.close();
  
  ros::Publisher marker_pub2 = nh.advertise<visualization_msgs::Marker>("path_marker", 10);
  // 创建Marker消息 - frame_id stamp ns action type
  visualization_msgs::Marker marker2;
  marker2.header.frame_id = "map";
  marker2.header.stamp = ros::Time();
//   marker.ns = "map_markers";
  marker2.action = visualization_msgs::Marker::ADD;
  marker2.type = visualization_msgs::Marker::POINTS;

  // 设置点的大小和颜色
  marker2.scale.x = 0.1;
  marker2.scale.y = 0.1;
  marker2.color.r = 0.0;
  marker2.color.g = 1.0;
  marker2.color.b = 0.0;
  marker2.color.a = 1.0;

  // 读取txt文件
  std::string file_path2 = "path.txt";
  std::ifstream file2(file_path2.c_str());
  if (!file2)
  {
    ROS_ERROR_STREAM("Failed to open file: " << file_path2);
    return;
  }

  std::string line2;
  while (std::getline(file2, line2))
  {
    std::istringstream iss(line2);
    float x, y;
    if (!(iss >> x >> y))
      break;

    geometry_msgs::Point point;
    point.x = x;
    point.y = y;
    point.z = 0.0;
    std::cout << "path " << "x: " << x << " y: " << y << std::endl;
    marker2.points.push_back(point);
  }

  file2.close();

  // 发布Marker消息
  while (marker_pub.getNumSubscribers() < 1)
  {
    if (!ros::ok())
      return;
      
    ROS_WARN_ONCE("Please create a subscriber to the marker");
    sleep(1);
  }

  marker_pub.publish(marker);
  marker_pub2.publish(marker2);
}
    
int main(int argc,char **argv){   
    
    ros::init(argc, argv, "map_display_node");
    displayMap();
    ros::spin();

    return 0;
}