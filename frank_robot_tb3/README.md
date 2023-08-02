# frank_robot simulation

# turtlebot3
## tb3 configure
sudo apt install ros-noetic-turtlebot3* ros-noetic-gmapping ros-noetic-navigation ros-noetic-multirobot-map-merge
robot class: burger waffler waffle_pi

## rviz sim
### fake仿真
export TURTLEBOT3_MODEL=burger
source devel/setup.bash && roslaunch turtlebot3_fake turtlebot3_fake.launch
### 键盘控制
roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch

## gazebo sim
### 将model复制到系统目录
mkdir -p ~/.gazebo/models/
cp -r  /data/frank_robot/src/turtlebot3_simulations/turtlebot3_gazebo/worlds/turtlebot3* ~/.gazebo/models/
### 空白地图
roslaunch turtlebot3_gazebo turtlebot3_empty_world.launch
### 复杂地图
roslaunch turtlebot3_gazebo turtlebot3_world.launch
roslaunch turtlebot3_gazebo turtlebot3_house.launch
### 键盘控制
roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch
### 仿真自动跑
export TURTLEBOT3_MODEL=burger
roslaunch turtlebot3_gazebo turtlebot3_simulation.launch
### rviz可视化
export TURTLEBOT3_MODEL=burger
roslaunch turtlebot3_gazebo turtlebot3_gazebo_rviz.launch

## slam&navigation
### gmapping
roslaunch turtlebot3_slam turtlebot3_slam.launch slam_methods:=gmapping
roslaunch turtlebot3_teleop turtlebot3_teleop_key.launch
rosrun map_server map_saver -f /data/frank_robot/map

### navigation
roslaunch turtlebot3_navigation turtlebot3_navigation.launch map_file:=/data/frank_robot/map.yaml

## multirobot
roslaunch turtlebot3_gazebo multi_turtlebot3.launch
#### 建图第一个终端
ROS_NAMESPACE=tb3_0 roslaunch turtlebot3_slam turtlebot3_gmapping.launch set_base_frame:=tb3_0/base_footprint set_odom_frame:=tb3_0/odom set_map_frame:=tb3_0/map
#### 建图第二个终端
ROS_NAMESPACE=tb3_1 roslaunch turtlebot3_slam turtlebot3_gmapping.launch set_base_frame:=tb3_1/base_footprint set_odom_frame:=tb3_1/odom set_map_frame:=tb3_1/map
#### 建图第三个终端
ROS_NAMESPACE=tb3_2 roslaunch turtlebot3_slam turtlebot3_gmapping.launch set_base_frame:=tb3_2/base_footprint set_odom_frame:=tb3_2/odom set_map_frame:=tb3_2/map
#### 合并地图
roslaunch turtlebot3_gazebo multi_map_merge.launch
rosrun rviz rviz -d `rospack find turtlebot3_gazebo`/rviz/multi_turtlebot3_slam.rviz
#### 键盘控制第一个终端
ROS_NAMESPACE=tb3_0 rosrun turtlebot3_teleop turtlebot3_teleop_key
#### 键盘控制第二个终端
ROS_NAMESPACE=tb3_1 rosrun turtlebot3_teleop turtlebot3_teleop_key
#### 键盘控制第三个终端
ROS_NAMESPACE=tb3_2 rosrun turtlebot3_teleop turtlebot3_teleop_key
#### 保存地图
rosrun map_server map_saver -f ~/map

## turtlebot3_autorace
roslaunch turtlebot3_gazebo turtlebot3_autorace.launch
### 启动Traffic Light，Parking和Toll Gate任务节点
roslaunch turtlebot3_gazebo turtlebot3_autorace_mission.launch
### 相机标定
export GAZEBO_MODE=true
export AUTO_IN_CALIB=action
roslaunch turtlebot3_autorace_camera turtlebot3_autorace_intrinsic_camera_calibration.launch
### 启动turtlebot3_autorace_core
export AUTO_EX_CALIB=action
export AUTO_DT_CALIB=action
export TURTLEBOT3_MODEL=burger
roslaunch turtlebot3_autorace_core turtlebot3_autorace_core.launch
### 启动自动驾驶节点
rostopic pub -1 /core/decided_mode std_msgs/UInt8 "data: 2"