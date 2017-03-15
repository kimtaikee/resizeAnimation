#include "imagecarousel.h"

class ImageCarouselPrivate
{
public:

};

ImageCarousel::ImageCarousel(QWidget *parent) : QWidget(parent)
{
    d_ptr = new ImageCarouselPrivate;
}

ImageCarousel::~ImageCarousel()
{
    delete d_ptr;
}

void ImageCarousel::addImage(const QString& image)
{
    // TODO
}

void ImageCarousel::removeImage(const QString& image)
{
    // TODO
}

void ImageCarousel::clear()
{
    // TODO
}
