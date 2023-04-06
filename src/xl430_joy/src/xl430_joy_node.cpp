#include "ros/ros.h"
#include "std_msgs/UInt16.h"
#include "sensor_msgs/Joy.h"

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    //퍼블리쉬 할 토픽 선언
    pub_1_ = n_.advertise<std_msgs::UInt16>("xl430_1", 100);
    pub_2_ = n_.advertise<std_msgs::UInt16>("xl430_2", 100);

    //섭스크라이브 할 토픽픽 선언
    sub_ = n_.subscribe("joy", 100, &SubscribeAndPublish::callback, this);

    output_1.data = 1000;
    output_2.data = 2500;
  }
  void callback(const sensor_msgs::Joy::ConstPtr& input)
  {
    ROS_INFO("joystick 0 : %d", input->buttons[0]);
    ROS_INFO("joystick 1 : %d", input->buttons[1]);
    ROS_INFO("joystick 2 : %d", input->buttons[2]);
    ROS_INFO("joystick 3 : %d", input->buttons[3]);

    if(input->buttons[0]==1)
    {
        output_1.data += 100;
    }
    if(input->buttons[1]==1)
    {
        output_1.data -= 100;
    }

    if(input->buttons[2]==1)
    {
        output_2.data += 100;
    }
    if(input->buttons[3]==1)
    {
        output_2.data -= 100;
    }
    //callback 함수에서 받은 input을 사용해서 output을 만들고 이를 pub한다.
    pub_1_.publish(output_1);
    pub_2_.publish(output_2);
    ROS_INFO("send msg = %d", output_1.data);
    ROS_INFO("send msg = %d", output_2.data);
  }

private: //private으로 NodeHandle과 publisher, subscriber를 선언한다.
  ros::NodeHandle n_; 
  ros::Publisher pub_1_;
  ros::Publisher pub_2_;
  ros::Subscriber sub_;
  std_msgs::UInt16 output_1;
  std_msgs::UInt16 output_2;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "subscribe_and_publish_1");
  SubscribeAndPublish SAPObject; //클래스 객체 선을 하게 되면 모든게 된다.
  ros::spin();
  return 0;
}