# 创建ros模板

## 创建功能包
cd catkin_ws/src
catkin_create_pkg helloros roscpp rospy std_msgs

cd helloros
mkdir src

sudo gedit helloros.cpp
```cpp
#include<ros/ros.h>
    
int main(int argc,char **argv){   
    
    ros::init(argc,argv,"hello_ros");   
    
    ros::NodeHandle nh;

    // 设置循环的频率
	ros::Rate loop_rate(10);
    
    while (ros::ok){
        ROS_INFO_STREAM("hello,ROS!");

        // 按照循环频率延时
	    loop_rate.sleep();
    }
    return 0;
}
```

sudo gedit CMakeLists.txt
```cpp
cmake_minimum_required(VERSION 2.8.3)
project(helloros)
#添加需要的依赖库 roscpp
find_package(catkin REQUIRED COMPONENTS roscpp)
include_directories(
${catkin_INCLUDE_DIRS}
)
#声明想要的可执行文件的文件名，以及所需要的源列表，如果有多个源列表，空格列在此处
add_executable(helloros_node src/helloros.cpp)
#告诉Cmake当链接此可执行文件时需要链接哪些库
target_link_libraries(helloros_node ${catkin_LIBRARIES})
```

sudo gedit package.xml
```xml
<build_depend>roscpp</build_depend>
<exec_depend>roscpp</exec_depend>
```

cd ~/catkin_ws
catkin_make

source devel/setup.bash
roscore&
rosrun helloros helloros_node

## 时间
catkin_create_pkg rostime roscpp rospy std_msgs

sudo gedit rostime_node.cpp

```cpp
#include "ros/ros.h"

void cb(const ros::TimerEvent &event)
{
    ROS_INFO("函数被调用时刻为：%.2f",event.current_real.toSec());
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"rostime_node");

    //没有这步，会导致时间API调用失败，在nodehandle中要初始化时间操作
    ros::NodeHandle nh;

    //-------------------------1.时刻---------------------------------
    ROS_INFO("-----------1.时刻输出-----------");
    //获取当前时间,now被调用执行那刻
    //参考系：1970年01月01日 00：00：00
    ros::Time right_now = ros::Time::now();

    ROS_INFO("当前时刻-toSec()格式：%.2f",right_now.toSec());
    ROS_INFO("当前时刻-sec()格式：%d",right_now.sec);

    //设置指定时间
    ros::Time t1(20,312345678);  //20.31秒
    ros::Time t2(100.35);    //100.35秒
    ROS_INFO("t1 = %.2f",t1.toSec());
    ROS_INFO("t2 = %.2f\n",t2.toSec());

    //-------------------------2.持续时间-------------------------------
    ROS_INFO("-----------2.持续时间-----------");
    //创建时间持续对象
    ros::Time start = ros::Time::now();
    ROS_INFO("开始休眠：%.2f",start.toSec());
    ROS_INFO("休眠中...");
    ros::Duration du(2);
    du.sleep();
    // int counts = 6;
    // while(counts != 1)
    // {
    //     counts--;
    //     ROS_INFO("倒计时：%d S",counts);
    // }
    ros::Time end = ros::Time::now();
    ROS_INFO("结束休眠：%.2f\n",end.toSec());

    //-------------------------3.时间运算-------------------------------
    ROS_INFO("-----------3.时刻与持续时间之间运算-----------");
    //获取开始时间
    ros::Time begin = ros::Time::now();
    ROS_INFO("开始时刻：%.2f",begin.toSec());

    //模拟运行时间（N秒）
    ros::Duration du1(5);
    ros::Duration du2(5);

    //计算结束时间 = 开始时间 ± 模拟运行时间
    ros::Time stop1 = begin + du1;
    ros::Time stop2 = begin - du2;
    ROS_INFO("结束时刻（+）：%.2f",stop1.toSec());
    ROS_INFO("结束时刻（-）：%.2f\n",stop2.toSec());

    //-------------------------4.时刻与时刻之间运算-----------------------
    ROS_INFO("-----------4.时刻与时刻之间运算-----------");
    ros::Duration du3 = begin - stop1;      //(只可以相减，不可以相加)
    ROS_INFO("时刻之间相减：%.2f \n",du3.toSec());

    //--------------------5.持续时间与持续时间之间运算---------------------
    ROS_INFO("-----------5.持续时间与持续时间之间运算-----------");
    ros::Duration du4 = du1 + du2;
    ros::Duration du5 = du1 - du2;
    ROS_INFO("du1+du2 = %.2f S",du4.toSec());
    ROS_INFO("du1-du2 = %.2f S\n",du5.toSec());

    //--------------------6.定时器输出---------------------
    ROS_INFO("-----------6.定时器输出-----------");
    /**
     * @brief nh.createTimer:
     *          参数1：时间间隔
     *          参数2：回调函数（时间事件 TimerEvent）
     *          参数3：是否只执行一次
     *          参数4：是否自动启动（false：需要手动调用 timer.start()）
     *          
     *        定时器启动后，需要调用ros::spin()回旋函数
     */
    // ros::Timer timer = nh.createTimer(ros::Duration(1),cb);           //调用回调函数cb，间隔1s输出“---哈哈---”
    // ros::Timer timer = nh.createTimer(ros::Duration(1),cb,true);      //第3参数true，只输出一次“---哈哈---”
    ros::Timer timer = nh.createTimer(ros::Duration(1),cb,false,false);  //第4参数false，不会输出“---哈哈---”，需要下面的手动启动指令去启动（默认第3，4参数为false，true）
    timer.start();
    ros::spin();     //回调函数的使用

    return 0;
}
```

## 日志
DEBUG(调试):只在调试时使用，此类消息不会输出到控制台；

INFO(信息):标准消息，一般用于说明系统内正在执行的操作；

WARN(警告):提醒一些异常情况，但程序仍然可以执行；

ERROR(错误):提示错误信息，此类错误会影响程序运行；

FATAL(严重错误):此类错误将阻止节点继续运行。

roslog.cpp
```cpp
#include "ros/ros.h"
#include <ros/console.h>


int main(int argc, char *argv[])
{
    setlocale(LC_ALL,"");
    ros::init(argc,argv,"hello_log");

    if( ros::console::set_logger_level(ROSCONSOLE_DEFAULT_NAME, ros::console::levels::Debug) ) {
        ros::console::notifyLoggerLevelsChanged();
    }

    ros::NodeHandle nh;

    ROS_DEBUG("ROS_DEBUG 调试信息------不显示");  //不会打印在控制台
    ROS_INFO("ROS_INFO 一般信息------白色");
    ROS_WARN("ROS_WARN 警告信息------黄色");
    ROS_ERROR("ROS_ERROR 错误信息------红色");
    ROS_FATAL("ROS_FATAL 严重错误------红色");

    return 0;
}
```