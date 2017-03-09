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
class CShape:public ISaveable
{
public:
    CShape(QGraphicsScene *scene);

    virtual bool isSelected();    
    virtual bool isCurrent();
    virtual void selected();
    virtual void setcurrent();
    virtual void removecurrent();

    virtual void StartTempDraw(QPointF point)=0;
    virtual void ContTempDraw(QPointF point)=0;
    virtual void FinishTempDraw(QPointF point)=0;
    virtual void setStyle()=0;
    virtual void draw()=0;
    virtual void redraw()=0;
    virtual bool pointInside(QPointF point)=0;
    virtual QString save()=0;
    virtual void load(QString)=0;
    virtual QString classname();
    virtual ISaveable *clone()=0;
    virtual void removes()=0;
protected:
    QGraphicsScene* mainscene;
    bool isselected;
    bool iscurrent;
    QString name;
    QPen selpen;
    QPen curpen;
    QPen selcurpen;
    QPen standardpen;
};

#endif // CSHAPE_H
