#ifndef ROS_IMAGE_PROVIDER_HPP
#define ROS_IMAGE_PROVIDER_HPP

#include <QQuickImageProvider>
#include <QMutex>
#include <QObject>

class ROSImageProvider : public QObject, public QQuickImageProvider {
    Q_OBJECT
public:
    ROSImageProvider() : QQuickImageProvider(QQuickImageProvider::Image) {}
    void setImage(const QImage &image);
    QImage requestImage(const QString &, QSize *, const QSize &) override;

private:
    QImage currentImage_;
    QMutex mutex_;
};

#endif

