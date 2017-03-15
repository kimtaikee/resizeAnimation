#ifndef IMAGECAROUSEL_H
#define IMAGECAROUSEL_H

#include <QWidget>

class ImageCarouselPrivate;
class ImageCarousel : public QWidget
{
    Q_OBJECT
public:
    explicit ImageCarousel(QWidget *parent = 0);
    ~ImageCarousel();

    void addImage(const QString& image);
    void removeImage(const QString& image);
    void clear();

private:
    ImageCarouselPrivate* d_ptr;
    Q_DISABLE_COPY(ImageCarousel)
};

#endif // IMAGECAROUSEL_H
