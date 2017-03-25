#ifndef CNPOLYGON_H
#define CNPOLYGON_H
#include <cshape.h>

class CNpolygon:public CShape
{
public:
    CNpolygon(QGraphicsScene *scene,int n);
    CNpolygon(QGraphicsScene *scene,QPolygonF pol,int n);
    virtual void StartTempDraw(QPointF point);
    virtual void ContTempDraw(QPointF point);
    virtual void FinishTempDraw(QPointF point);
    virtual void setStyle();
    virtual void draw();
    virtual void redraw();
    virtual bool pointInside(QPointF point);
    virtual QString save();
    virtual void load(QString);
    virtual ISaveable *clone();
    virtual void removes();
private:
    QPolygonF createpolygon(QPointF center,double R,int n);
    int sides;
    QPointF center;
    int radius;
    bool flag;
    QPolygonF polygon;
    QGraphicsPolygonItem* item;
};

#endif // CNPOLYGON_H
