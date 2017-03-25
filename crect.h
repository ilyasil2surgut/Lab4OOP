#ifndef CRECT_H
#define CRECT_H
#include <cshape.h>

class CRect:public CShape
{
public:
    CRect(QGraphicsScene *scene);
    CRect(QPointF topleft,QPointF bottomright,QGraphicsScene *scene);
    virtual void draw();
    void redraw();
    void StartTempDraw(QPointF point);
    void ContTempDraw(QPointF point);
    void FinishTempDraw(QPointF point);
    virtual QString save();
    virtual void load(QString);
    virtual ISaveable *clone();
    virtual void removes();
    virtual bool canRotate(double);
    virtual void Rotate(QPointF);
    virtual QPointF center();
    virtual void setRotationCenter(QPointF);
private:
    QRectF rect;
    QGraphicsRectItem *item;
};

#endif // CRECT_H
