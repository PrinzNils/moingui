#ifndef VIDEO_STREAM_NODE_HPP
#define VIDEO_STREAM_NODE_HPP

#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <opencv2/opencv.hpp>
#include <QObject>
#include <QImage>

class VideoStreamNode : public QObject, public rclcpp::Node {
    Q_OBJECT
public:
    VideoStreamNode();

signals:
    void imageUpdated(const QImage &image);

private:
    void imageCallback(const sensor_msgs::msg::Image::SharedPtr msg);
    QImage matToQImage(const cv::Mat &mat);

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
};

#endif

