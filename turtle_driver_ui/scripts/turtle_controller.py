#!/usr/bin/env python

from __future__ import print_function

import sys
import rospy
from turtle_driver.srv import *
from abc import ABC, abstractmethod


class drive_command_parser(ABC):
    @abstractmethod
    def on_message_received(self, str_mode, params):
        pass

class circle_driver(drive_command_parser):

    def on_message_received(self, str_mode, params):
        response = 0
        if (str_mode == 'circle'):
            radius = float(params[0])

            rospy.wait_for_service('circle')
            try:
                drive = rospy.ServiceProxy('circle', circle)
                resp1 = drive(radius)
                response = resp1.response
            except rospy.ServiceException as e:
                pass

            if (response == 1):
                print("Circle maneuever succeeded")
            else:
                print("Circle maneuever has failed")

        return response 

class square_driver(drive_command_parser):
    
    def on_message_received(self, str_mode, params):
        response = 0
        if (str_mode == 'square'):
            length = float(params[0])

            rospy.wait_for_service('square')
            try:
                drive = rospy.ServiceProxy('square', square)
                resp1 = drive(length)
                response = resp1.response
            except rospy.ServiceException as e:
                pass

            if (response == 1):
                print("Square maneuever succeeded")
            else:
                print("Square maneuever has failed")

        return response 

class custom_driver(drive_command_parser):

    def on_message_received(self, str_mode, params):
        response = 0
        if (str_mode == 'custom'):
            x_pts = []
            y_pts =[]
            for i in range(0, len(params)):
                split = params[i].split(',')
                x_pts.append(float(split[0]))
                y_pts.append(float(split[1]))

            rospy.wait_for_service('custom')
            try:
                drive = rospy.ServiceProxy('custom', custom)
                resp1 = drive(x_pts, y_pts)
                response = resp1.response
            except rospy.ServiceException as e:
                pass

            if (response == 1):
                print("Custom maneuever succeeded")
            else:
                print("Custom maneuever has failed")

        return response 

class help_printer(drive_command_parser):
    def on_message_received(self, str_mode, params):
        if (str_mode == 'h'):
            print("""
            circle <radius> => drive in a circle of specified radius
            square <side_length> => drive in a square of specified side length
            custom <p1> <p2> <p3>... => follow these points sequentially where p1 in the form <x,y>         
            """)
            return 1
        return 0



if __name__ == "__main__":
    rospy.init_node("turtle_controller_ui_cli")

    command_parsers = [circle_driver(), square_driver(), custom_driver(), help_printer()]

    print("Requesting drive\n")
    while not rospy.is_shutdown():
        cmd = input("Please insert command! Type 'h' for help.\n")
        args = cmd.split()

        success = 0
        for parser in command_parsers: 
            success |= parser.on_message_received(args[0], args[1:] if len(args) >= 2 else None)

        if (not success):
                print("Couldn't understand your command. Please ensure it is a supported command. See help for more")    
        print("\n")

