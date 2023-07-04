## carla_ros_birdge_pnc
通过carla-ros-bridge在carla上实现自动驾驶planning and control。

## Table of Contents

#### [P1 - Controller](./controller)

横向控制：LQR, PurePuresuit, Stanley

纵向控制：PID

![LQR1](figure/LQR1.gif)





![LQR2](figure/LQR2.gif)





#### [P2 - Planning](./planning)

简易场景下的路径规划

Global planner: A* (carla_ros_bridge 自带) 

Local planner: Lattice Planner

![lp2-16872379376268](figure/lp2.gif)

![lp3](figure/lp3.gif)



## Build

#### 1.安装依赖：

- Ubuntu 18.04/20.04 

- ROS Melodic/Noetic

- Eigen

- cmake >= 3.5

- python3.X

  

- [Carla simulator (0.9.11)](https://github.com/carla-simulator/carla/releases/tag/0.9.11)  

  安装配置手册：https://carla.readthedocs.io/en/latest/start_quickstart/

  

- [ROS bridge for CARLA simulator(0.9.11)](https://github.com/carla-simulator/ros-bridge/tree/0.9.11)  

  安装配置手册：https://carla.readthedocs.io/projects/ros-bridge/en/latest/ros_installation_ros1/

  

- [Carla scenario_runner(0.9.11)](https://github.com/czjaixuexi/scenario_runner/tree/v0.9.11-czj)

​		安装配置手册：https://carla-scenariorunner.readthedocs.io/en/latest/getting_scenariorunner/



#### 2. 配置工作空间

**快速配置方式：**

```bash
cd scripts
./quickly_setup.sh
```

**手动配置方式：**

```
1.创建src文件，放置功能包源码：
  mkdir -p ~/catkin_ws/src

2.进入src文件夹
  cd ~/catkin_ws/src

3.将功能包复制到的src目录下

4.初始化文件夹
  catkin_init_workspace

5.编译工作空间
  catkin build
```

## Run Controller Demo

**终端1：启动carla**

```bash
cd path/to/carla/root

./CarlaUE4.sh
```

**终端2：启动控制结点**

```
source devel/setup.bash
```

Pure Pursuit

```
roslaunch controller controller_demo.launch control_method:="PurePursuit"
```

Stanley

```
roslaunch controller controller_demo.launch control_method:="Stanley"
```

LQR

```
roslaunch controller controller_demo.launch control_method:="LQR"
```

## Run Planning Demo

**终端1：启动carla**

```bash
cd path/to/carla/root

./CarlaUE4.sh
```

**终端2：启动Planning结点**

```bash
source devel/setup.bash

roslaunch planning planning_demo.launch
```



**终端3：启动scenario runner** 

scenario_runner-0.9.11目录下

```bash
python scenario_runner.py --scenario Avoid_and_Follow_1 --waitForEgo
```



**终端4：启动控制结点**

```bash
source devel/setup.bash

roslaunch controller controller.launch
```



## To-Do-List

- MPC的实现
- EM planner的实现
- local planner应用场景的泛化


## Reference

[Casper Auto](https://github.com/casper-auto)

[Optimal Trajectory Generation for Dynamic Street Scenarios in a Frenet Frame](https://www.researchgate.net/publication/224156269_Optimal_Trajectory_Generation_for_Dynamic_Street_Scenarios_in_a_Frenet_Frame)

