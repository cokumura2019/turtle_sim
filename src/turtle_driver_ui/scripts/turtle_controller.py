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
        return resp1
    except rospy.ServiceException as e:
        print("Circle Service call failed: %s"%e)

def drive_square(length):
    rospy.wait_for_service('square')
    try:
        drive = rospy.ServiceProxy('square', square)
        resp1 = drive(length)
        return resp1
    except rospy.ServiceException as e:
        print("Square Service call failed: %s"%e)

def drive_custom(x_points, y_points):
    rospy.wait_for_service('custom')
    try:
        drive = rospy.ServiceProxy('custom', custom)
        resp1 = drive(x_points, y_points)
        return resp1
    except rospy.ServiceException as e:
        print("Custom Service call failed: %s"%e)


if __name__ == "__main__":

    print("Requesting drive\n")
    while 1:
        cmd = input("Please insert command! Type 'h' for help\n")
        if (cmd == 'h'):
            print("""
            circle <radius> => drive in a circle of specified radius
            square <side_length> => drive in a square of specified side length
            custom <p1> <p2> <p3>... => follow these points sequentially where p1 in the form <x,y>         
            """)
        else:
            args = cmd.split()
            if (args[0] == 'circle'):
                drive_circle(float(args[1]))
            elif (args[0] == 'square'):
                drive_square(float(args[1]))
            elif (args[0] == 'custom'):
                x_pts = []
                y_pts =[]
                for i in range(1, len(args)):
                    split = args[i].split(',')
                    x_pts.append(float(split[0]))
                    y_pts.append(float(split[1]))
                drive_custom(x_pts, y_pts)

            else:
                print("Couldn't understand your command. Please ensure it is a supported command. See help for more")

        print("\n")

