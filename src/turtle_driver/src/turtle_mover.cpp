#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
ros::Publisher vel_publisher;

void drive_circle(double radius, bool isForward);

double speed = 1;
const double PI = 3.141592653589793238;

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "turtle_mover");
    ros::NodeHandle n;

    vel_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);

    double radius =0;

    ROS_INFO("\n\n\n********** START TESTING **************");
    std::cout << "enter radius*: ";
    std::cin >> radius;

    drive_circle(radius, true);
}

void drive_circle(double radius, bool isForward)
{
    geometry_msgs::Twist vel_msg;

    double expected_length = 2 * PI * radius;

    vel_msg.linear.x=speed;

    vel_msg.linear.y=0;
    vel_msg.linear.z=0;
    vel_msg.angular.x=0;
    vel_msg.angular.y=0;

    // ang_vel * t = 360
    //   t = 360 / ang_vel
    //     d_total = speed * t = speed * 360 / ang_vel
    //     2 * pi * radius = speed * 360 / ang_vel
    //        ang_vel = speed * 360 / (2 * pi * radius)     

    // double compute_ang_vel = speed * (2*PI) / (2 * PI * radius);
    double compute_ang_vel = speed / radius;

    vel_msg.angular.z=compute_ang_vel;
    
    double t0 = ros::Time::now().toSec();
    double current_angle=0;
    ros::Rate loop_rate(10);
    do 
    {
        vel_publisher.publish(vel_msg);
        double t1 = ros::Time::now().toSec();
        current_angle = compute_ang_vel * (t1-t0);
        ros::spinOnce();
        loop_rate.sleep();
    } while (current_angle < 2 * PI);

    geometry_msgs::Twist stop_msg;
    stop_msg.linear.x = 0;
    stop_msg.linear.y = 0;
    stop_msg.linear.z = 0;
    stop_msg.angular.x = 0;
    stop_msg.angular.y = 0;
    stop_msg.angular.z = 0;

}
