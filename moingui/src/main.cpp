#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <rclcpp/rclcpp.hpp>
#include <QDir>
#include <QDebug>
#include "VideoStreamNode.hpp"
#include "ROSImageProvider.hpp"

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    auto node = std::make_shared<VideoStreamNode>();
    auto imageProvider = new ROSImageProvider();

    QObject::connect(
    node.get(), &VideoStreamNode::imageUpdated,
    imageProvider, &ROSImageProvider::setImage
    );

    
    engine.addImageProvider("videoProvider", imageProvider);
    engine.load(QUrl::fromLocalFile("src/moingui/main.qml"));

    std::thread rosThread([&]() {
        rclcpp::spin(node);
    });

    int ret = app.exec();
    rclcpp::shutdown();
    rosThread.join();
    return ret;
}

