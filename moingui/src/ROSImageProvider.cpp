#include "ROSImageProvider.hpp"

void ROSImageProvider::setImage(const QImage &image) {
    QMutexLocker locker(&mutex_);
    currentImage_ = image;
}

QImage ROSImageProvider::requestImage(const QString &, QSize *, const QSize &) {
    QMutexLocker locker(&mutex_);
    return currentImage_;
}

