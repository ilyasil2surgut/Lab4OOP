#ifndef CNPOLYGON_H
#define CNPOLYGON_H
#include <cshape.h>

class CNpolygon:public CShape
{
public:
    CNpolygon(QGraphicsScene *scene,int n=3);
    CNpolygon(QGraphicsScene *scene,QPolygonF pol,int n);
    virtual void StartTempDraw(QPointF point);
    virtual void ContTempDraw(QPointF point);
    virtual void FinishTempDraw(QPointF point);
    virtual void draw();
    virtual void redraw();
    virtual QString save();
    virtual void load(QString);
    virtual ISaveable *clone();
    virtual void removes();
private:
    QPolygonF createpolygon(QPointF center,double R,int n);
    int sides;
    QPointF center;
    int radius;
    QPolygonF polygon;
    QGraphicsPolygonItem* item;
};

#endif // CNPOLYGON_H
