#include "ros/ros.h"
#include "std_msgs/Header.h"
#include <iostream>

void hostACallback(std_msgs::Header msg)
{
  printf("Receiving ID: %d \t Latency: %f ms\n", msg.seq, ((ros::Time::now() - msg.stamp).toSec()) * 1000.0);
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "host_a");
  ros::NodeHandle n;
  ros::Publisher host_a_pub = n.advertise<std_msgs::Header>("chatter_a", 1);
  ros::Rate loop_rate(10);

  // Subscribing to chatter_b from host_b
  ros::Subscriber host_a_sub = n.subscribe("chatter_b", 1, hostACallback);

  int count = 0;
  ros::AsyncSpinner spinner(2);
  spinner.start();
  while (ros::ok())
  {
    std_msgs::Header msg;
    msg.seq = count;
    msg.stamp = ros::Time::now();
    // ROS_INFO("Seq ID: %d \t", msg.seq);
    host_a_pub.publish(msg);
    loop_rate.sleep();
    ++count;
  }
  spinner.stop();
  return 0;
}