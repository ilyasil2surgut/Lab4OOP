#ifndef CNPOLYGON_H
#define CNPOLYGON_H
#include <cshape.h>

class CNpolygon:public CShape
{
public:
    CNpolygon(QGraphicsScene *scene,int n=3);
    CNpolygon(QGraphicsScene *scene,QPolygonF pol,QPointF centerpoint, int n,double angle);
    virtual void StartTempDraw(QPointF point);
    virtual void ContTempDraw(QPointF point);
    virtual void FinishTempDraw(QPointF point);
    virtual void draw();
    virtual void redraw();
    virtual QString save();
    virtual void load(QString);
    virtual ISaveable *clone();
    virtual void removes();
    virtual void Rotate(QPointF);
    virtual void Move(QPointF);
    virtual QPointF center();
    virtual void setRotationCenter(QPointF);
    virtual QPolygonF checkpolygon();
private:
    QPolygonF createpolygon(QPointF centerpoint,double R,int n);
    int sides;
    QPointF Center;
    int radius;
    QPolygonF polygon;
    QGraphicsPolygonItem* item;
};

#endif // CNPOLYGON_H
