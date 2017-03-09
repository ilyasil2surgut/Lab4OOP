#ifndef CRECT_H
#define CRECT_H
#include <cshape.h>

class CRect:public CShape
{
public:
    CRect(QGraphicsScene *scene);
    CRect(QPointF topleft,QPointF bottomright,QGraphicsScene *scene);
    virtual void setStyle();
    virtual void draw();
    void redraw();
    void StartTempDraw(QPointF point);
    void ContTempDraw(QPointF point);
    void FinishTempDraw(QPointF point);
    virtual bool pointInside(QPointF point);
    virtual QString save();
    virtual void load(QString);
    virtual ISaveable *clone();
    virtual void removes();
private:
    QRectF rect;
    QGraphicsRectItem *item;
    bool flag;
};

#endif // CRECT_H
