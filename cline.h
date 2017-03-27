#ifndef CLINE_H
#define CLINE_H
#include <cshape.h>
#include <QLineF>

class CLine:public CShape
{
public:
    CLine(QGraphicsScene *scene);
    CLine(QGraphicsScene *scene,QLineF line,double angle);
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
    virtual void Rotate(QPointF);
    virtual QPointF center();
    virtual void setRotationCenter(QPointF);
    virtual QPolygonF checkpolygon();
private:
    QLineF line;
    QGraphicsLineItem *item;
    QGraphicsPolygonItem *clickpolygon;
};

#endif // CLINE_H
