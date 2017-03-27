#ifndef CRECT_H
#define CRECT_H
#include <cshape.h>

class CRect:public CShape
{
public:
    CRect(QGraphicsScene *scene);
    CRect(QPointF topleft,QPointF bottomright,QGraphicsScene *scene,double angle);
    virtual void draw();
    void redraw();
    void StartTempDraw(QPointF point);
    void ContTempDraw(QPointF point);
    void FinishTempDraw(QPointF point);
    virtual QString save();
    virtual void load(QString);
    virtual ISaveable *clone();
    virtual void removes();
    virtual void Rotate(QPointF);
    virtual QPointF center();
    virtual void setRotationCenter(QPointF);
    virtual QPolygonF checkpolygon();
private:
    QRectF rect;
    QGraphicsRectItem *item;
};

#endif // CRECT_H
