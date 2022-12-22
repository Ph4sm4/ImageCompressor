#include "customview.h"

CustomView::CustomView(QWidget *parent) : QGraphicsView(parent)
{

}

void CustomView::wheelEvent(QWheelEvent *event)
{
    setTransformationAnchor(AnchorUnderMouse);
    double scaleFactor = 1.5;

    if(event->angleDelta().y() > 0) { // vertical scroll
        scale(scaleFactor, scaleFactor);
    }
    else {
        scale(1/scaleFactor, 1/scaleFactor);
    }
}

