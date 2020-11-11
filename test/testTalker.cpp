/*
 * Copyright: Aditya Goswami | goswami@umd.edu
 *  
 * @file: testTalker.cpp
 * @brief: test suites for Transform broadcaster and Service calls
 * @author: Aditya Goswami
 */

#include <gtest/gtest.h>
#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <beginner_tutorials/chatting_service.h>
#include <std_msgs/String.h>

/**
 * @brief: This test tests Tranform Broadcaster. Checks if transform messages are broadcasted by 
 * employing a transform listener
 * @param: Name of the test case, name of the test 
 * */
TEST(TransformBroadcaster, tfListener) {
    tf::TransformListener listener;
    EXPECT_TRUE(listener.waitForTransform("world", "talk", ros::Time(),
                                          ros::Duration(2.0)));
}

/**
 * @brief: Tests the service call by calling a service client
 * @param: Name of the test case, name of the test
 * */
TEST(ChangeString, callService) { 
    ros::NodeHandle n;
    ros::ServiceClient client =
        n.serviceClient<beginner_tutorials::chatting_service>("Chatter");
    EXPECT_TRUE(client.waitForExistence(ros::Duration(5.0)));
}