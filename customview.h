#ifndef CUSTOMVIEW_H
#define CUSTOMVIEW_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWheelEvent>

class CustomView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit CustomView(QWidget *parent = nullptr);

protected:
    virtual void wheelEvent(QWheelEvent* event);
    using QGraphicsView::QGraphicsView;
};

#endif // CUSTOMVIEW_H
