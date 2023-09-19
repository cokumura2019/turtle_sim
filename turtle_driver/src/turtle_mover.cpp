#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include "turtlesim/TeleportAbsolute.h"
#include "vector2.h"
#include "turtle_driver/circle.h"
#include "turtle_driver/square.h"
#include "turtle_driver/custom.h"

ros::Publisher vel_publisher;
ros::Subscriber pos_subscriber;



bool drive_circle(turtle_driver::circle::Request  &req, turtle_driver::circle::Response &res);
bool drive_square (turtle_driver::square::Request &req, turtle_driver::square::Response &res);
void posecallback (const turtlesim::Pose &data);
//bool follow_points (const vector2* points, const int numPoints);
bool follow_points (turtle_driver::custom::Request &req, turtle_driver::custom::Response &res);
void reset_position();
void init_position();

const double rightBound = 11-.02;
const double leftBound = 0+.02;
const double topBound = 11-.02;
const double botBound = 0+.02;

ros::NodeHandle* nPtr;

double speed = 1;
const double PI = 3.141592653589793238;

const vector2 DEFAULT = {5.44445, 5.44445};
vector2 curPos = {5.44445, 5.44445};
double yaw = 0;
geometry_msgs::Twist stop_msg;

// Rais flag by settimg = 1
int out_of_bounds_flag = 0;

std::string pose_subscriber_topic_name;
std::string vel_publish_topic_name;
std::string tele_publish_topic_name;

/*
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

    stop_msg.linear.x = 0;
    stop_msg.linear.y = 0;
    stop_msg.linear.z = 0;
    stop_msg.angular.x = 0;
    stop_msg.angular.y = 0;
    stop_msg.angular.z = 0;
    init_position();

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
*/

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "turtle_driver");
    ros::NodeHandle n;
    nPtr = &n;

    ros::param::get("/turtle_controller/turtle_pose_topic", pose_subscriber_topic_name);
    ros::param::get("/turtle_controller/turtle_vel_topic", vel_publish_topic_name);
    ros::param::get("/turtle_controller/turtle_tele_topic", tele_publish_topic_name);


    pos_subscriber = n.subscribe<const turtlesim::Pose&>(pose_subscriber_topic_name, 1000, posecallback);
    vel_publisher = n.advertise<const geometry_msgs::Twist>(vel_publish_topic_name, 10);
    
    int mode;
    ROS_INFO("\n\n\n********** START TESTING **************");

    stop_msg.linear.x = 0;
    stop_msg.linear.y = 0;
    stop_msg.linear.z = 0;
    stop_msg.angular.x = 0;
    stop_msg.angular.y = 0;
    stop_msg.angular.z = 0;
    init_position();

    ros::ServiceServer cService = n.advertiseService("circle", drive_circle);
    ros::ServiceServer sService = n.advertiseService("square", drive_square);
    ros::ServiceServer custService = n.advertiseService("custom", follow_points);

    ros::spin();

    return 0;
}


void init_position ()
{
    ros::Rate loop_rate(100);

    geometry_msgs::Twist temp_msg;
    stop_msg.linear.x = 0.01;
    stop_msg.linear.y = 0;
    stop_msg.linear.z = 0;
    stop_msg.angular.x = 0;
    stop_msg.angular.y = 0;
    stop_msg.angular.z = 0.01;
    vel_publisher.publish(stop_msg);

    ros::spinOnce();
    loop_rate.sleep();

    vel_publisher.publish(stop_msg);
    ros::spinOnce();
    loop_rate.sleep();

    out_of_bounds_flag = 0;
}

void reset_position()
{
    // Stop all motion first
    vel_publisher.publish(stop_msg);

    ros::ServiceClient client = nPtr->serviceClient<turtlesim::TeleportAbsolute>(tele_publish_topic_name);
    turtlesim::TeleportAbsolute srv;
    srv.request.x = DEFAULT.x;
    srv.request.y = DEFAULT.y;
    srv.request.theta = 0;
    if (client.call(srv))
    {
        ROS_INFO("Reset turtle due to out-of-bounds;");
    }
    else
    {
        ROS_INFO("Failed to reset turtle");
    }
    out_of_bounds_flag=0;
}

void posecallback (const turtlesim::Pose &data)
{
    curPos = {data.x, data.y};
    yaw = data.theta;

    if (curPos.x > rightBound || curPos.x < leftBound || curPos.y > topBound || curPos.y < botBound)
    {
        out_of_bounds_flag = 1;
    }
//    ROS_INFO("Retrieved new angle %f", yaw);
}

bool drive_circle(turtle_driver::circle::Request  &req, turtle_driver::circle::Response &res)
{
    const double radius = req.r;
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
        if (out_of_bounds_flag == 1)
        {
            reset_position();
            res.response = 0;
            return false;
        }

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
    
    // Edit response object that the routine finished successfully
    res.response = 1;
    return true;
}

bool drive_square (turtle_driver::square::Request &req, turtle_driver::square::Response &res)
{
    const double sideLength = req.s;
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
            if (out_of_bounds_flag == 1)
            {
                reset_position();
                res.response = 0;
                return false;
            }

            
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

    vel_publisher.publish(stop_msg);

    // Mark that the function completed successfully
    res.response = 1;
    return 1;
}
//bool follow_points (const vector2* points, const int numPoints);

bool follow_points (turtle_driver::custom::Request &req, turtle_driver::custom::Response &res)
{
    vector2 all_points[20];
    const int numPoints = req.x.size();
    for (int i = 0 ; i < numPoints ; i++) all_points[i] = {req.x[i], req.y[i]};

    vector2* points = all_points;
    ros::Rate loop_rate(500);
    for (int i = 0; i < numPoints; ++i, ++points)
    {
        std::cout << "num: " << i << std::endl;
        const vector2 startPoint = curPos;
        const double startAngle = yaw;

        const vector2 point = *points;        
        const vector2 diff = point - startPoint;

        double angleToOrientTo = diff.get_angle();
        double angleDiff = abs(angleToOrientTo - startAngle);
        double distanceToTravel = diff.get_magnitude();

        geometry_msgs::Twist turn_msg;
        turn_msg.linear.x=0;
        turn_msg.linear.y=0;
        turn_msg.linear.z=0;
        turn_msg.angular.x=0;
        turn_msg.angular.y=0;
        turn_msg.angular.z=speed * (angleToOrientTo > 0 ? 1 : -1);
        double tolerance = 0.15;
        for (int i = 0 ; i < 7; i ++)
        {
            double t0 = ros::Time::now().toSec();
            do 
            {
                vel_publisher.publish(turn_msg);
                ros::spinOnce();
                loop_rate.sleep();
            //    angle_rotated = (t1 - t0) * abs(turn_msg.angular.z);
            } 
            while (abs(yaw - angleToOrientTo) >= tolerance);

            tolerance/= (2);
            turn_msg.angular.z /= 3;
        }


        std::cout <<point.x << " " << point.y << std::endl;
        geometry_msgs::Twist forward_msg;
        forward_msg.linear.x=speed;
        forward_msg.linear.y=0;
        forward_msg.linear.z=0;
        forward_msg.angular.x=0;
        forward_msg.angular.y=0;
        forward_msg.angular.z=0;

        tolerance = 0.3;
        for (int i = 0 ; i < 5; i++)
        {
            do {
                if (out_of_bounds_flag == 1)
                {
                    reset_position();
                    res.response = 0;
                    return false;
                }

                vel_publisher.publish(forward_msg);
                ros::spinOnce();
                loop_rate.sleep();
                std::cout <<curPos.x << " " << curPos.y << std::endl;
            } while ((curPos - point).get_magnitude() > tolerance );

            tolerance /= 2;
            forward_msg.linear.x /= 3.5;
        }

        
        vel_publisher.publish(stop_msg);
    }

    // mark as completed successful and end the function
    res.response = 1;
    return 1;
}