#include "cshape.h"

CShape::CShape(QGraphicsScene *scene)
{
    mainscene=scene;
    isselected=false;
    name="CShape";
    Angle=0;
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
    baseitem->setRotation(Angle);
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
    rotationcenter=center();
    qDebug()<<"Rotation initiated for "<<classname();
}

void CShape::initMove(QPointF point)
{
    movestart=point;
}

QPointF CShape::movedelta(QPointF destination)
{
    return destination-movestart;
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
    for(int i=0;i<check.size();i++){
        QLineF A;
        A.setP1(RotationCenter());
        A.setP2(check[i]);
        A.setAngle(angle+A.angle());
        if((A.p2().x()<0)||(A.p2().y()<0)||(A.p2().x()>800)||(A.p2().y()>500)){
            return false;
        }
    }
    return true;
}

bool CShape::checkpoints(QPolygonF check, QPointF destination)
{
    qDebug()<<"MOving"<<classname()<<check<<destination;
    QPolygonF moved;
    for(int i=0;i<check.size();i++){
        moved<<(check[i]+movedelta(destination));
    }
    for(int i=0;i<moved.size();i++){
        QLineF A;
//        A.setP1(RotationCenter());
        //        A.setP2(moved[i]);
        A.setP1(center());
        A.setP2(moved[i]);
//        A.setAngle(Angle);
//        if(!(mainscene->sceneRect().contains(A.p2()))){
//            return false;
//        }
        if((A.p2().x()<0)||(A.p2().y()<0)||(A.p2().x()>800)||(A.p2().y()>500)){
            qDebug()<<"Cant move to"<<A.p2()<<check;
            return false;
        }
    }
    return true;
}

bool CShape::canRotate(double angle)
{
    return checkpoints(checkpolygon(),angle);
}

void CShape::setAngle(double a)
{
    Angle=a;
}

void CShape::determineAngle()
{
    Angle=baseitem->rotation();
}

bool CShape::canMove(QPointF destination)
{
    return checkpoints(checkpolygon(),destination);
}

bool CShape::pointInside(QPointF point)
{
    return baseitem->contains(point);
}
