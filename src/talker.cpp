/*
 * Copyright (C) 2008, Morgan Quigley and Willow Garage, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *   * Redistributions of source code must retain the above copyright notice,
 *     this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *   * Neither the names of Stanford University or Willow Garage, Inc. nor the names of its
 *     contributors may be used to endorse or promote products derived from
 *     this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include <sstream>
#include <string>
#include <tf/transform_broadcaster.h>
#include "ros/ros.h"
#include "std_msgs/String.h"

#include "beginner_tutorials/chatting_service.h"

bool chat(beginner_tutorials::chatting_service::Request &req,
  beginner_tutorials::chatting_service::Response &res) {
  ROS_DEBUG_STREAM("request: " << req.request_message);
  if (req.request_message == "y") {
    res.response_message = "Think again!";
  } else if (req.request_message == "n") {
    res.response_message = "wrong";
  } else {
    res.response_message = "warning";
  }
  ROS_DEBUG_STREAM("sending back response: " << res.response_message);
  return true;
}


/**
 * This tutorial demonstrates simple sending of messages over the ROS system.
 */
int main(int argc, char **argv) {
  /**
   * The ros::init() function needs to see argc and argv so that it can perform
   * any ROS arguments and name remapping that were provided at the command line.
   * For programmatic remappings you can use a different version of init() which takes
   * remappings directly, but for most command-line programs, passing argc and argv is
   * the easiest way to do it.  The third argument to init() is the name of the node.
   *
   * You must call one of the versions of ros::init() before using any other
   * part of the ROS system.
   */
  ros::init(argc, argv, "talker");

  ros::NodeHandle n;

  ros::ServiceServer server = n.advertiseService("Chatter", chat);

  // Create broadcaster intance
  static tf::TransformBroadcaster br;

    // Create quaternion & transform instance
  tf::Transform transform;

   while (ros::ok()) {
    // Set origin for the transform frame
    transform.setOrigin(tf::Vector3(1.0, 2.0, 0.0));

    // Set quaternion -> (Roll, Pitch Yaw) using fixed axis
    tf::Quaternion q;
    q.setRPY(0, 0, 10);

    // Set rotation of the transform using quaternion
    transform.setRotation(q);

    // Send the transform using @param instance of transform, time stamp, parent frame, child frame
    br.sendTransform(
        tf::StampedTransform(transform, ros::Time::now(), "world", "talk"));

    // Message object of topic std_msgs::String
    std_msgs::String msg;     
    std::stringstream ss; 
}
  ROS_INFO("Waiting for response");

  ros::spin();


  return 0;
}


