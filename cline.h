#ifndef CLINE_H
#define CLINE_H
#include <cshape.h>
#include <QLineF>

class CLine:public CShape
{
public:
    CLine(QGraphicsScene *scene);
    CLine(QGraphicsScene *scene,QLineF line);
    bool pointInside(QPointF point);
    void draw();
    void redraw();
    virtual void setStyle();
    virtual void removes();
    QString save();
    void load(QString);
    ISaveable *clone();
    void StartTempDraw(QPointF point);
    void ContTempDraw(QPointF point);
    void FinishTempDraw(QPointF point);
    QPolygonF createclickpol();
    virtual bool canRotate(double);
    virtual void Rotate(QPointF);
    virtual QPointF center();
    virtual void setRotationCenter(QPointF);
private:
    QLineF line;
    QGraphicsLineItem *item;
    QGraphicsPolygonItem *clickpolygon;
};

#endif // CLINE_H
