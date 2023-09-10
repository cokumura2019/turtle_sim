#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
ros::Publisher vel_publisher;

void drive_circle(double r, double v, double theta, bool isClockwise);

const double PI = 3.141592653589793238;

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "turtle_mover");
    ros::NodeHandle n;

    vel_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);


    double radius=1;
    double velocity=1;
    double theta_d=360;
    bool isClockwise=0;
    if (argc < 5)
    {
        std::cout << "Setting radius to 1" << std::endl;
        std::cout << "Setting speed to 1" << std::endl;
        std::cout << "Setting theta to 360" << std::endl;
        std::cout << "Setting to CCW" << std::endl;
    }
    else
    {
        char* dummy;
        std::cout << "Setting radius to " << argv[1] << std::endl;
        std::cout << "Setting speed to " << argv[2] << std::endl;
        std::cout << "Setting theta to " << argv[3] << std::endl;
        std::cout << "Setting to " << (argv[4][0] == '0' ? "CCW" : "CW") << std::endl;
        radius =strtod(argv[1], &dummy);
        velocity=strtod(argv[2], &dummy);
        theta_d = strtod(argv[3], &dummy);
        isClockwise=atoi(argv[4]);
    }
    std::cout << "found: " << radius << std::endl;

    drive_circle(radius, velocity, theta_d * PI/180, isClockwise);
}

void drive_circle(double r, double v, double theta, bool isClockwise)
{
    geometry_msgs::Twist vel_msg;

    double expected_length = theta * r;
    std::cout << "found: " << theta << std::endl;

    vel_msg.linear.x=v;

    vel_msg.linear.y=0;
    vel_msg.linear.z=0;
    vel_msg.angular.x=0;
    vel_msg.angular.y=0;

    // ang_vel * t = 360
    //   t = 360 / ang_vel
    //     d_total = speed * t = speed * 360 / ang_vel
    //     2 * pi * radius = speed * 360 / ang_vel
    //        ang_vel = speed * 360 / (2 * pi * radius)  

    // 2pi = ang_vel * t   
    // 2pi * r = v * t
    // ang_vel = v/r

    // double compute_ang_vel = speed * (2*PI) / (2 * PI * radius);
    double compute_ang_vel = v / r * isClockwise ? 1 : -1;

    vel_msg.angular.z=compute_ang_vel;
    
    double t0 = ros::Time::now().toSec();
    double current_angle=0;
    double curr_dist =0;
    ros::Rate loop_rate(100);
    do 
    {
        vel_publisher.publish(vel_msg);
        double t1 = ros::Time::now().toSec();
        current_angle = compute_ang_vel * (t1-t0);
        curr_dist = v * (t1 - t0);
        ros::spinOnce();
        loop_rate.sleep();
    } while (abs(curr_dist) < expected_length);

    geometry_msgs::Twist stop_msg;
    stop_msg.linear.x = 0;
    stop_msg.linear.y = 0;
    stop_msg.linear.z = 0;
    stop_msg.angular.x = 0;
    stop_msg.angular.y = 0;
    stop_msg.angular.z = 0;
    vel_publisher.publish(stop_msg);
}
