#include "ros/ros.h"
#include "movement_servicer.h"
#include "transform_tracking.h"
using namespace std;



std::unique_ptr<ros::NodeHandle> nodePtr;

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "turtle_driver");
    ros::NodeHandle n;
    nodePtr = std::unique_ptr<ros::NodeHandle>(&n);


    TransfromTracker trasformTracker(nodePtr);
    MovementServicer movesMaster(nodePtr, &trasformTracker);
    movesMaster.InitializePosition();

    int mode;
    ROS_INFO("\n\n\n********** START TESTING **************");

    ros::spin();

    return 0;
}