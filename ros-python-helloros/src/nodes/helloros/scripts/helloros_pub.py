#!/usr/bin/env python
# -*- coding: utf-8 -*-

import threading
import rospy
from std_msgs.msg import String

def thread_ros_message_core():
    print('thread_ros_message_core create success!!!')

def thread_receive_monitor_data():
    print('thread_receive_monitor_data create success!!!')

def thread_send_monitor_data():
    print('thread_send_monitor_data create success!!!')

def talker():
     pub = rospy.Publisher('chatter', String, queue_size=10)
    #  rospy.init_node('talker', anonymous=True)
     rate = rospy.Rate(10) # 10hz
     while not rospy.is_shutdown():
         hello_str = "hello world talker %s" % rospy.get_time()
         rospy.loginfo(hello_str)
         pub.publish(hello_str)
         rate.sleep()

if __name__ == '__main__':
    try:
        rospy.init_node('helloros', anonymous=True)
        rospy.loginfo( "hello world %s" % rospy.get_time())
        talker()
        
        t1 = threading.Thread(target=thread_ros_message_core)
        t2 = threading.Thread(target=thread_receive_monitor_data)
        t3 = threading.Thread(target=thread_send_monitor_data)
        t1.start()
        t3.start()
        t1.join()
        t3.join()
    except rospy.ROSInterruptException:
        pass
