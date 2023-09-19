#!/usr/bin/env python

from __future__ import print_function

import sys
import rospy
from turtle_driver.srv import *


def drive_circle(radius):
    rospy.wait_for_service('circle')
    try:
        drive = rospy.ServiceProxy('circle', circle)
        resp1 = drive(radius)
        return resp1.response
    except rospy.ServiceException as e:
        return 0

def drive_square(length):
    rospy.wait_for_service('square')
    try:
        drive = rospy.ServiceProxy('square', square)
        resp1 = drive(length)
        return resp1.response
    except rospy.ServiceException as e:
        return 0

def drive_custom(x_points, y_points):
    rospy.wait_for_service('custom')
    try:
        drive = rospy.ServiceProxy('custom', custom)
        resp1 = drive(x_points, y_points)
        return resp1.response
    except rospy.ServiceException as e:
        return 0

if __name__ == "__main__":
    rospy.init_node("turtle_controller_ui_cli")
    
    print("Requesting drive\n")
    while not rospy.is_shutdown():
        cmd = input("Please insert command! Type 'h' for help.\n")

        if (cmd == 'h'):
            print("""
            circle <radius> => drive in a circle of specified radius
            square <side_length> => drive in a square of specified side length
            custom <p1> <p2> <p3>... => follow these points sequentially where p1 in the form <x,y>         
            """)
        else:
            args = cmd.split()
            if (args[0] == 'circle'):
                if drive_circle(float(args[1])):
                    print("Circle maneuever succeeded")
                else:
                    print("Circle maneuever has failed")
            elif (args[0] == 'square'):
                if drive_square(float(args[1])):
                    print("Square maneuever succeeded")
                else:
                    print("Square maneuever has failed")
            elif (args[0] == 'custom'):
                x_pts = []
                y_pts =[]
                for i in range(1, len(args)):
                    split = args[i].split(',')
                    x_pts.append(float(split[0]))
                    y_pts.append(float(split[1]))
                if drive_custom(x_pts, y_pts):
                    print("Custom maneuever succeeded")
                else:
                    print("Custom maneuever has failed")
            else:
                print("Couldn't understand your command. Please ensure it is a supported command. See help for more")

        print("\n")

