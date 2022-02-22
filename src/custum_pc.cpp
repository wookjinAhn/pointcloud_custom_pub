#include <ros/ros.h>
#include <sensor_msgs/PointCloud.h>
#include <string>
#include <random>

void getRandomPointCloud(sensor_msgs::PointCloud& pc,
                         double centerX,
                         double centerY,
                         int& sizeOfCloud) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> distX(centerX, 2.);
    std::normal_distribution<> distY(centerY, 2.);

    for (int i = 0; i < pc.points.size(); i++) {
        double xValue = distX(gen);
        double yValue = distY(gen);
        pc.points[i].x = xValue;
        pc.points[i].y = yValue;
        pc.points[i].z =
                std::exp(-((xValue * xValue) + (yValue * yValue)) / 4.);
    }
    sensor_msgs::ChannelFloat32 depth_channel;
    depth_channel.name = "distance";
    for (int i = 0; i < pc.points.size(); i++) {
        depth_channel.values.push_back(pc.points[i].z); // or set to a random value if you like
    }
    // add channel to point cloud
    pc.channels.push_back(depth_channel);
}

int main(int argc, char** argv) {
    ros::init(argc, argv, "point_cloud_test");
    auto nh = ros::NodeHandle();

    int sizeOfCloud = 100000;
    sensor_msgs::PointCloud keypoints;
    keypoints.points.resize(sizeOfCloud);
    getRandomPointCloud(keypoints, 0.5, 0.5, sizeOfCloud);

    keypoints.header.frame_id = "map";
    keypoints.header.stamp = ros::Time::now();

    auto keypoints_publisher = nh.advertise<sensor_msgs::PointCloud>("point_cloud", 10);
    ros::Rate rate(30);
    while (ros::ok()) {
        keypoints.header.stamp = ros::Time::now();
        keypoints_publisher.publish(keypoints);
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}