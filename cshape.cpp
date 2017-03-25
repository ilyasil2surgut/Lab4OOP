#include "cshape.h"

CShape::CShape(QGraphicsScene *scene)
{
    mainscene=scene;
    isselected=false;
    name="CShape";
//    qDebug()<<"CShape added";
    standardpen=QPen(Qt::blue);
    standardpen.setWidth(3);
    selcurpen=QPen(Qt::red);
    selcurpen.setWidth(3);
    selcurpen.setBrush(QBrush(Qt::red,Qt::Dense4Pattern));
    curpen=QPen(Qt::green);
    curpen.setWidth(5);
    curpen.setBrush(QBrush(Qt::blue,Qt::Dense4Pattern));
    selpen=QPen(Qt::red);
    selpen.setWidth(5);
}

bool CShape::isSelected()
{
    return isselected;
}

bool CShape::isCurrent()
{
    return iscurrent;
}

QString CShape::classname()
{
    return name;
}

void CShape::setitem(QAbstractGraphicsShapeItem *item)
{
    baseitem=item;
    redraw();
    mainscene->addItem(baseitem);
    setStyle();
    baseitem->show();
}

void CShape::selected()
{    
    if(!isselected){
        isselected=true;
        setStyle();
    }
}

void CShape::unselected()
{
    if(isselected){
        isselected=false;
        setStyle();
    }
}

void CShape::setcurrent()
{
    iscurrent=true;
    setStyle();
}

void CShape::removecurrent()
{
    if(iscurrent){
        iscurrent=false;
        setStyle();
    }
}

void CShape::setStyle()
{
    if(iscurrent&&isselected)baseitem->setPen(selcurpen);
    else if(iscurrent)baseitem->setPen(curpen);
    else if(isselected)baseitem->setPen(selpen);
    else baseitem->setPen(standardpen);
}

void CShape::removes()
{
    mainscene->removeItem(baseitem);
}

void CShape::initRotation(QPointF point)
{
    rotationstart=point;
}

double CShape::calculateAngle(QPointF end)
{
    QLineF A(center(),rotationstart);
    QLineF B(center(),end);
    return -A.angleTo(B);
}

bool CShape::pointInside(QPointF point)
{
    return baseitem->contains(point);
}
