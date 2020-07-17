#include "ros/ros.h"
#include "std_msgs/Header.h"

unsigned int key = 0;
bool flag = false;
ros::Publisher host_b_pub;

void hostBCallback(const std_msgs::Header msg)
{
  key = msg.seq;
  printf("Received Key: %d\n", key);
  host_b_pub.publish(msg);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "host_b");

  ros::NodeHandle n;

  ros::Subscriber host_b_sub = n.subscribe("chatter_a", 1, hostBCallback);

  // Publishing on chatter_b to host_a
  host_b_pub = n.advertise<std_msgs::Header>("chatter_b", 1);

  ros::spin();

  return 0;
}