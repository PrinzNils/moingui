#include "VideoStreamNode.hpp"
#include <cv_bridge/cv_bridge.h>

VideoStreamNode::VideoStreamNode() : Node("video_stream_node") {
    subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
        "/image_raw/compressed", 10,
        std::bind(&VideoStreamNode::imageCallback, this, std::placeholders::_1));
}

void VideoStreamNode::imageCallback(const sensor_msgs::msg::Image::SharedPtr msg) {
    try {
        auto cv_image = cv_bridge::toCvCopy(msg, "bgr8");
        cv::Mat frame = cv_image->image;

        // Optional: Bildverarbeitung hier einfügen
        QImage qt_image = matToQImage(frame);
        emit imageUpdated(qt_image);
    } catch (const cv_bridge::Exception &e) {
        RCLCPP_ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
    }
}

QImage VideoStreamNode::matToQImage(const cv::Mat &mat) {
    return QImage(mat.data, mat.cols, mat.rows, mat.step, QImage::Format_BGR888);
}

