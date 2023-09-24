#ifndef MOVEMENT_SERVICER_H
#define MOVEMENT_SERVICER_H

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/TeleportAbsolute.h"
#include "turtle_driver/circle.h"
#include "turtle_driver/square.h"
#include "turtle_driver/custom.h"
#include "transform_tracking.h"
#include "vector2.h"

using namespace std;

static const double PI = 3.141592653589793238;

class MovementServicer
{


    // Topic Messages
    ros::Publisher vel_topic_publisher;

    // Service PRoviders
    ros::ServiceServer cService;
    ros::ServiceServer sService;
    ros::ServiceServer custService;

    // Service Clients
    ros::ServiceClient resetClient;

    shared_ptr<TransfromTracker> tracker_helper;

    const geometry_msgs::Twist stop_msg;

    double speed = 1;
    const vector2 DEFAULT = {5.44445, 5.44445};

    public:

        MovementServicer(std::unique_ptr<ros::NodeHandle>& n,  TransfromTracker* tracker, const double default_speed = 1) : stop_msg(geometry_msgs::Twist())
        {
            tracker_helper = shared_ptr<TransfromTracker>(tracker);
            this->speed = default_speed;

            std::string* vel_publish_topic_name = new std::string();
            std::string* teleport_topic_name = new std::string();

            ros::param::get("/turtle_controller/turtle_vel_topic", *vel_publish_topic_name);
            ros::param::get("/turtle_controller/turtle_tele_topic", *teleport_topic_name);

            this->vel_topic_publisher = n->advertise<const geometry_msgs::Twist>(*vel_publish_topic_name, 10);
            this->cService = n->advertiseService("circle", &MovementServicer::drive_circle, this);
            this->sService = n->advertiseService("square", &MovementServicer::drive_square, this);
            this->custService = n->advertiseService("custom", &MovementServicer::follow_points, this);
        
            this->resetClient = n->serviceClient<turtlesim::TeleportAbsolute>(*teleport_topic_name);

            // Cleanup temp resources
            delete vel_publish_topic_name;
            delete teleport_topic_name;
        }

        ~MovementServicer()
        {
            this->vel_topic_publisher.shutdown();
            this->cService.shutdown();
            this->sService.shutdown();
            this->custService.shutdown();
        }

        void InitializePosition ()
        {
            ros::Rate loop_rate(100);
            
            geometry_msgs::Twist temp_msg;
            temp_msg.linear.x = 0.01;
            temp_msg.linear.y = 0;
            temp_msg.linear.z = 0;
            temp_msg.angular.x = 0;
            temp_msg.angular.y = 0;
            temp_msg.angular.z = 0.01;
            vel_topic_publisher.publish(temp_msg);

            ros::spinOnce();
            loop_rate.sleep();

            this->vel_topic_publisher.publish(stop_msg);
            ros::spinOnce();
            loop_rate.sleep();
        }

        void reset_position()
        {
            // Stop all motion first
            this->vel_topic_publisher.publish(stop_msg);

            turtlesim::TeleportAbsolute srv;
            srv.request.x = DEFAULT.x;
            srv.request.y = DEFAULT.y;
            srv.request.theta = 0;
            if (this->resetClient.call(srv))
            {
                ROS_INFO("Reset turtle due to out-of-bounds;");
            }
            else
            {
                ROS_ERROR("Failed to reset turtle");
            }
            this->tracker_helper->ResetBoundsFlag();
        }
        
        bool drive_circle(turtle_driver::circle::Request  &req, turtle_driver::circle::Response &res)
        {
            const double radius = req.r;
            const double expected_length = 2 * PI * radius;
            geometry_msgs::Twist vel_msg;

            vel_msg.linear.x=this->speed;

            vel_msg.linear.y=0;
            vel_msg.linear.z=0;
            vel_msg.angular.x=0;
            vel_msg.angular.y=0;

            // ang_vel * t = 360
            //   t = 360 / ang_vel
            //     d_total = speed * t = speed * 360 / ang_velS
            //     2 * pi * radius = speed * 360 / ang_vel
            //        ang_vel = speed * 360 / (2 * pi * radius)     

            // double compute_ang_vel = speed * (2*PI) / (2 * PI * radius);
            double compute_ang_vel = this->speed / radius;

            vel_msg.angular.z=compute_ang_vel;
            
            double t0 = ros::Time::now().toSec();
            double current_angle=0;
            ros::Rate loop_rate(1000);
            while (current_angle < 2 * PI)
            {
                if (this->tracker_helper->out_of_bounds_flag() == 1)
                {
                    this->reset_position();
                    res.response = 0;
                    return false;
                }

                this->vel_topic_publisher.publish(vel_msg);
                double t1 = ros::Time::now().toSec();
                current_angle = compute_ang_vel * (t1-t0);
                ros::spinOnce();
                loop_rate.sleep(); 
            }

            this->vel_topic_publisher.publish(stop_msg);
            
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
                while (distance_traversed < sideLength)
                {
                    if (this->tracker_helper->out_of_bounds_flag() == 1)
                    {
                        reset_position();
                        res.response = 0;
                        return false;
                    }

                    
                    vel_topic_publisher.publish(forward_msg);
                    double t1 = ros::Time::now().toSec();
                    ros::spinOnce();
                    loop_rate.sleep();
                    distance_traversed = (t1 - t0) * forward_msg.linear.x;
                }

                double angle_rotated = 0;
                t0 = ros::Time::now().toSec();
                while(angle_rotated < PI/2)
                {
                    vel_topic_publisher.publish(turn_msg);
                    double t1 = ros::Time::now().toSec();
                    ros::spinOnce();
                    loop_rate.sleep();
                    angle_rotated = (t1 - t0) * abs(turn_msg.angular.z);
                }
            }

            vel_topic_publisher.publish(stop_msg);

            // Mark that the function completed successfully
            res.response = 1;
            return 1;
        }
        //bool follow_points (const vector2* points, const int numPoints);

        bool follow_points (turtle_driver::custom::Request &req, turtle_driver::custom::Response &res)
        {
            std::array<vector2, 20> all_points;
            const int numPoints = req.x.size();
            for (int i = 0 ; i < numPoints ; i++) all_points.at(i) = {req.x[i], req.y[i]};

            ros::Rate loop_rate(500);
            for (int i = 0; i < numPoints; ++i)
            {
                const vector2 startPoint = this->tracker_helper->position();
                const double startAngle = this->tracker_helper->yaw();

                const vector2 point = all_points.at(i);        
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
                    while (abs(this->tracker_helper->yaw() - angleToOrientTo) >= tolerance)
                    {
                        this->vel_topic_publisher.publish(turn_msg);
                        ros::spinOnce();
                        loop_rate.sleep();
                    //    angle_rotated = (t1 - t0) * abs(turn_msg.angular.z);
                    }

                    tolerance/= (2);
                    turn_msg.angular.z /= 3;
                }

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
                    while ((this->tracker_helper->position() - point).get_magnitude() > tolerance )
                    {
                        if (this->tracker_helper->out_of_bounds_flag() == 1)
                        {
                            this->reset_position();
                            res.response = 0;
                            return false;
                        }

                        this->vel_topic_publisher.publish(forward_msg);
                        ros::spinOnce();
                        loop_rate.sleep();
                    }

                    tolerance /= 2;
                    forward_msg.linear.x /= 3.5;
                }

                
                this->vel_topic_publisher.publish(stop_msg);
            }

            // mark as completed successful and end the function
            res.response = 1;
            return 1;
        }
};



#endif