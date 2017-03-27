#ifndef CSHAPE_H
#define CSHAPE_H

#include <QPointF>
#include <QGraphicsEllipseItem>
#include <QtGui>
#include "qmath.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QListWidgetItem>
#include <../lab3oop/isaveable.h>
#include <../lab3oop/slstorage.h>
class CShape:public ISaveable
{
public:
    CShape(QGraphicsScene *scene);

    virtual bool isSelected();    
    virtual bool isCurrent();
    virtual void selected();
    virtual void unselected();
    virtual void setcurrent();
    virtual void removecurrent();
    virtual bool pointInside(QPointF point);
    virtual QString classname();
    virtual void setStyle();
    virtual void removes();
    virtual void initRotation(QPointF);
    double calculateAngle(QPointF);
    virtual QPointF RotationCenter();
    virtual void setRotationCenter(QPointF);
    virtual bool checkpoints(QPolygonF,double);
    virtual bool checkpoints(QPolygonF,QPointF);
    virtual bool canRotate(double);
    virtual void setAngle(double);
    virtual void determineAngle();

    virtual void StartTempDraw(QPointF point)=0;
    virtual void ContTempDraw(QPointF point)=0;
    virtual void FinishTempDraw(QPointF point)=0;    
    virtual void draw()=0;
    virtual void redraw()=0;    
    virtual QString save()=0;
    virtual void load(QString)=0;    
    virtual ISaveable *clone()=0;
    virtual void Rotate(QPointF)=0;
    virtual QPointF center()=0;
    virtual QPolygonF checkpolygon()=0;
protected:
    void setitem(QAbstractGraphicsShapeItem* item);
    QGraphicsScene* mainscene;
    QAbstractGraphicsShapeItem* baseitem;
    bool isselected;
    bool iscurrent;
    bool flag;
    double Angle;
    QPointF rotationstart;
    QString name;
    QPen selpen;
    QPen curpen;
    QPen selcurpen;
    QPen standardpen;
    QPointF rotationcenter;
};

#endif // CSHAPE_H
