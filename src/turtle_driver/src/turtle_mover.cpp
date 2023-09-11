#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include "vector2.h"

ros::Publisher vel_publisher;
ros::Subscriber pos_subscriber;

void drive_circle(double radius, bool isForward);
void drive_square (double sideLength);
void posecallback (const turtlesim::Pose &data);
void follow_points (const vector2* points, const int numPoints);


double speed = 1;
const double PI = 3.141592653589793238;

vector2 curPos;
double yaw;


int main(int argc, char *argv[])
{
    ros::init(argc, argv, "turtle_mover");
    ros::NodeHandle n;

    pos_subscriber = n.subscribe("/turtle1/pose", 1000, posecallback);
    vel_publisher = n.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 10);
    
    int mode;
    ROS_INFO("\n\n\n********** START TESTING **************");
    std::cout << "Enter mode: ";
    std::cin >> mode;

  //  drive_circle(radius, true);
    if (mode == 0)
    {         
        double radius = 1;
        try
        {
            radius = atoi(argv[1]);
        }
        catch(const std::exception& e)
        {
        }
        drive_circle(radius, true);   
    }
    else if (mode == 1)
    {            
        double sideLength = 1;
        try
        {
            sideLength = atoi(argv[1]);
        }
        catch(const std::exception& e)
        {
        }
        drive_square(sideLength);   
    }
    else
    {
        int numPoints = (argc - 1) / 2;
        vector2 points[numPoints];
        char* dummyptr;
        for (int i = 0 ; i < numPoints ;i++)
        {
            
            points[i] = {strtof(argv[i * 2 + 1], &dummyptr), strtof(argv[i*2 +2], &dummyptr)};
        }
        std::cout << points[1].x << std::endl;
        follow_points(points, numPoints);
    }

    return 0;
}

void posecallback (const turtlesim::Pose &data)
{
    curPos = {data.x, data.y};
    yaw = data.theta;
    ROS_INFO("Retrieved new angle %f", yaw);
}


void drive_circle(const double radius, const bool isForward)
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
    ros::Rate loop_rate(1000);
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

    vel_publisher.publish(stop_msg);
}

void drive_square (const double sideLength)
{
    bool isCCW = 1;
    // For now, we will just have the turtle start the square from the angle it is currently at
    geometry_msgs::Twist forward_msg;
    forward_msg.linear.x=speed;
    forward_msg.linear.y=0;
    forward_msg.linear.z=0;
    forward_msg.angular.x=0;
    forward_msg.angular.y=0;
    forward_msg.angular.z=0;

    geometry_msgs::Twist turn_msg;
    turn_msg.linear.x=0;
    turn_msg.linear.y=0;
    turn_msg.linear.z=0;
    turn_msg.angular.x=0;
    turn_msg.angular.y=0;
    turn_msg.angular.z=speed * (isCCW ? 1 : -1);
    

    ros::Rate loop_rate(100);
    for (int i = 0 ; i < 4; i++)
    {
        double distance_traversed = 0;
        double t0 = ros::Time::now().toSec();
        do 
        {
            vel_publisher.publish(forward_msg);
            double t1 = ros::Time::now().toSec();
            ros::spinOnce();
            loop_rate.sleep();
            distance_traversed = (t1 - t0) * forward_msg.linear.x;
        } 
        while (distance_traversed < sideLength);

        double angle_rotated = 0;
        t0 = ros::Time::now().toSec();
        do 
        {
            vel_publisher.publish(turn_msg);
            double t1 = ros::Time::now().toSec();
            ros::spinOnce();
            loop_rate.sleep();
            angle_rotated = (t1 - t0) * abs(turn_msg.angular.z);
        } 
        while (angle_rotated < PI/2);
    }

    geometry_msgs::Twist stop_msg;
    stop_msg.linear.x = 0;
    stop_msg.linear.y = 0;
    stop_msg.linear.z = 0;
    stop_msg.angular.x = 0;
    stop_msg.angular.y = 0;
    stop_msg.angular.z = 0;

    vel_publisher.publish(stop_msg);
}

void follow_points (const vector2* points, const int numPoints)
{

    ros::Rate loop_rate(100);
    for (int i = 0 ; i < numPoints; ++i, ++points)
    {
        std::cout << "num: " << i << std::endl;
        const vector2 currentPoint = curPos;
        const vector2 point = *points;        
        const vector2 diff = point - currentPoint;

        double angleToTurn = diff.get_angle();
        double distanceToTravel = diff.get_magnitude();

        geometry_msgs::Twist turn_msg;
        turn_msg.linear.x=0;
        turn_msg.linear.y=0;
        turn_msg.linear.z=0;
        turn_msg.angular.x=0;
        turn_msg.angular.y=0;
        turn_msg.angular.z=speed * (angleToTurn > 0 ? 1 : -1);

        double angle_rotated = 0;
        do 
        {
            vel_publisher.publish(turn_msg);
            ros::spinOnce();
            loop_rate.sleep();
        //    angle_rotated = (t1 - t0) * abs(turn_msg.angular.z);
        } 
        while (abs(yaw - angleToTurn) >= 0.1);


        geometry_msgs::Twist forward_msg;
        forward_msg.linear.x=speed;
        forward_msg.linear.y=0;
        forward_msg.linear.z=0;
        forward_msg.angular.x=0;
        forward_msg.angular.y=0;
        forward_msg.angular.z=0;
        do
        {
            vel_publisher.publish(forward_msg);
            ros::spinOnce();
            loop_rate.sleep();
        } while ((curPos - point).get_magnitude() > .2 );
        
        geometry_msgs::Twist stop_msg;
        stop_msg.linear.x = 0;
        stop_msg.linear.y = 0;
        stop_msg.linear.z = 0;
        stop_msg.angular.x = 0;
        stop_msg.angular.y = 0;
        stop_msg.angular.z = 0;
        vel_publisher.publish(stop_msg);

    }
}