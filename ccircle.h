#ifndef CCIRCLE_H
#define CCIRCLE_H

#include <QPointF>
#include <QGraphicsEllipseItem>
#include <QtGui>
#include "qmath.h"
#include <QDebug>
#include <QGraphicsScene>
#include <QListWidgetItem>
#include <../lab3oop/isaveable.h>
#include <cshape.h>
class CCircle:public CShape
{
public:
    CCircle(QGraphicsScene *scene);
    CCircle(QPointF point,QGraphicsScene *scene, int R);
    void draw();
    void redraw();
    void removes();
    QString save();
    void load(QString);
    ISaveable *clone();
    void StartTempDraw(QPointF point);
    void ContTempDraw(QPointF point);
    void FinishTempDraw(QPointF point);
    virtual bool canRotate(double);
    virtual void Rotate(QPointF);
    virtual QPointF center();
    void setRotationCenter(QPointF);
private:
    QPointF Center;
    int radius;
    QGraphicsEllipseItem *item;
};

#endif // CCIRCLE_H
