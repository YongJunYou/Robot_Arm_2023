#include "ros/ros.h"
#include "std_msgs/UInt16.h"
#include "sensor_msgs/Joy.h"

class SubscribeAndPublish
{
public:
  SubscribeAndPublish()
  {
    //퍼블리쉬 할 토픽 선언
    pub_1_ = n_.advertise<std_msgs::UInt16>("mg966r_1", 100);
    pub_2_ = n_.advertise<std_msgs::UInt16>("mg966r_2", 100);
    pub_3_ = n_.advertise<std_msgs::UInt16>("mg966r_3", 100);

    //섭스크라이브 할 토픽픽 선언
    sub_ = n_.subscribe("joy", 100, &SubscribeAndPublish::callback, this);
  }
  void callback(const sensor_msgs::Joy::ConstPtr& input)
  {
    ROS_INFO("joystick L : %d", input->buttons[6]);
    ROS_INFO("joystick R : %d", input->buttons[7]);

    
    int stop = 340;
    int spin_cw = 360;
    int spin_ccw = 320;

    int power_spin_cw = 390;
    int power_spin_ccw = 290;

    int super_power_spin_cw = 440;
    int super_power_spin_ccw = 240;

    float up = 1.0;

    output_1.data = stop;
    output_2.data = stop;
    output_3.data = stop;

    if(input->buttons[4]==1)
    {
        output_1.data = power_spin_cw;
    }
    if(input->buttons[5]==1)
    {
        output_1.data = power_spin_ccw;
    }

    if(abs(input->axes[7]-1)<0.01)
    {
        output_2.data = super_power_spin_cw;
    }
    if(abs(input->axes[7]+1)<0.01)
    {
        output_2.data = super_power_spin_ccw;
    }

    if(abs(input->axes[2]+1)<0.01)
    {
        output_3.data = power_spin_cw;
    }
    if(abs(input->axes[5]+1)<0.01)
    {
        output_3.data = power_spin_ccw;
    }


    //callback 함수에서 받은 input을 사용해서 output을 만들고 이를 pub한다.
    pub_1_.publish(output_1);
    pub_2_.publish(output_2);
    pub_3_.publish(output_3);
    ROS_INFO("send msg = %d", output_1.data);
    ROS_INFO("send msg = %d", output_2.data);
    ROS_INFO("send msg = %d", output_3.data);
  }

private: //private으로 NodeHandle과 publisher, subscriber를 선언한다.
  ros::NodeHandle n_; 
  ros::Publisher pub_1_;
  ros::Publisher pub_2_;
  ros::Publisher pub_3_;
  ros::Subscriber sub_;
  std_msgs::UInt16 output_1;
  std_msgs::UInt16 output_2;
  std_msgs::UInt16 output_3;
};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "subscribe_and_publish_2");
  SubscribeAndPublish SAPObject; //클래스 객체 선을 하게 되면 모든게 된다.
  ros::spin();
  return 0;
}