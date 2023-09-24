#ifndef TRANSFORM_TRACKING_H
#define TRANSFORM_TRACKING_H

#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "vector2.h"
using namespace std;

// This class (should just be a singleton) is used for tracking the position and angles of the turtle
class TransfromTracker
{
    private:
        const double rightBound = 11-.02;
        const double leftBound = 0+.02;
        const double topBound = 11-.02;
        const double botBound = 0+.02;

        vector2 position_;
        double yaw_;
        int out_of_bounds_flag_;
        ros::Subscriber position_subscriber;

        void posecallback (const turtlesim::Pose &data)
        {
            position_ = {data.x, data.y};
            yaw_ = data.theta;

            if (position_.x > rightBound || position_.x < leftBound || position_.y > topBound || position_.y < botBound)
            {
                out_of_bounds_flag_ = 1;
            }
            ROS_INFO("Position-angle : {%f, %f} - {%f}", position_.x, position_.y, yaw_);
        //    ROS_INFO("Retrieved new angle %f", yaw);
        }

    public:
        vector2 position() const { return this->position_;}
        double yaw() const {return this->yaw_;}
        int out_of_bounds_flag() const {return this->out_of_bounds_flag_;}

        TransfromTracker (std::unique_ptr<ros::NodeHandle>& n)
        {
            std::string pose_topic_name;
            ros::param::get("/turtle_controller/turtle_pose_topic", pose_topic_name);
            position_subscriber = n->subscribe<const turtlesim::Pose&>(pose_topic_name, 1000, &TransfromTracker::posecallback, this);
        }

        ~TransfromTracker()
        {
            this->position_subscriber.shutdown();
        }

        void ResetBoundsFlag ()
        {
            this->out_of_bounds_flag_ = 0;
        }
    
};

#endif