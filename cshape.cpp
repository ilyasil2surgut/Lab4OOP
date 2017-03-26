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
    qDebug()<<"Rotation initiated for "<<classname();
}

double CShape::calculateAngle(QPointF end)
{
    QLineF A(RotationCenter(),rotationstart);
    QLineF B(RotationCenter(),end);
    return -A.angleTo(B);
}

QPointF CShape::RotationCenter()
{
    return rotationcenter;
}

void CShape::setRotationCenter(QPointF point)
{
    rotationcenter=point;
}

bool CShape::checkpoints(QPolygonF check, double angle)
{
//    QPointF offset(280,50);
    for(int i=0;i<check.size();i++){
        QLineF A;
        A.setP1(RotationCenter());
        A.setP2(check[i]);
//        qDebug()<<A.p2()<<i;
        if(A.p1().x()<=A.p2().x())A.setAngle(angle+A.angle());
        else A.setAngle(angle+A.angle());
//        qDebug()<<A.p2()<<mainscene->sceneRect();
        A.setP2(A.p2());
        if((A.p2().x()<0)||(A.p2().y()<0)||(A.p2().x()>800)||(A.p2().y()>500)){
            qDebug()<<"Check fail"<<i<<A.p2()<<check;
            return false;
        }
    }
    return true;
}

bool CShape::checkpoints(QPolygonF check, QPointF delta)
{
    for(int i=0;i<check.size();i++){
        if(!(mainscene->sceneRect().contains(check[i]+delta)))return false;
    }
    return true;
}

bool CShape::canRotate(double angle)
{
    return checkpoints(checkpolygon(),angle);
}

bool CShape::pointInside(QPointF point)
{
    return baseitem->contains(point);
}
