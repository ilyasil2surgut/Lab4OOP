#include "crect.h"


CRect::CRect(QGraphicsScene *scene):CShape(scene)
{
    name=QString("Rectangle");
    flag=true;
}

CRect::CRect(QPointF topleft, QPointF bottomright, QGraphicsScene *scene, double angle):CShape(scene)
{
    name=QString("Rectangle");
    flag=false;
    rect.setTopLeft(topleft);
    rect.setBottomRight(bottomright);
    Angle=angle;
}

void CRect::draw()
{
    item=new QGraphicsRectItem();
    setitem(item);
}

void CRect::redraw()
{
    item->setRect(rect);
    item->setRotation(Angle);
}

void CRect::StartTempDraw(QPointF point)
{
    if(flag){
        rect.setTopLeft(point);
        rect.setBottomRight(point);
        draw();
    }

}

void CRect::ContTempDraw(QPointF point)
{
    if(flag){
        rect.setBottomRight(point);
        redraw();
    }
}

void CRect::FinishTempDraw(QPointF point)
{
    if(flag){
        rect.setBottomRight(point);
        flag=false;
        redraw();
        setRotationCenter(center());
    }
}

QString CRect::save()
{
    QStringList out;
    out<<classname();out<<":";
    out<<QString::number(Angle)<<" ";
    out<<QString::number(rect.topLeft().x())<<" ";
    out<<QString::number(rect.topLeft().y())<<" ";
    out<<QString::number(rect.bottomRight().x())<<" ";
    out<<QString::number(rect.bottomRight().y())<<"\n";
    return out.join(QString());
}

void CRect::load(QString str)
{
    if(str.split(":").first()==classname()){
        QStringList list=str.split(":").last().split(" ");
        Angle=list.first().toInt();list.pop_front();
        double x1=list.first().toInt();list.pop_front();
        double y1=list.first().toInt();list.pop_front();
        double x2=list.first().toInt();list.pop_front();
        double y2=list.first().toInt();list.pop_front();
        rect.setCoords(x1,y1,x2,y2);
    }
}

ISaveable *CRect::clone()
{
    return new CRect(rect.topLeft(),rect.bottomRight(),mainscene,Angle);
}

void CRect::removes()
{
    mainscene->removeItem(item);
}

void CRect::Rotate(QPointF end)
{
    item->setRotation(calculateAngle(end));
    Angle=calculateAngle(end);
}

void CRect::Move(QPointF destination)
{
    item->setRotation(0);
    rect.setTopLeft(rect.topLeft()+movedelta(destination));
    rect.setBottomRight(rect.bottomRight()+movedelta(destination));
    setRotationCenter(RotationCenter()+movedelta(destination));
    redraw();
}

QPointF CRect::center()
{
    QPointF A;
    A.setX((rect.topLeft().x()+rect.topRight().x())/2);
    A.setY((rect.topLeft().y()+rect.bottomRight().y())/2);
    return A;
}

void CRect::setRotationCenter(QPointF point)
{
    rotationcenter=point;
    item->setTransformOriginPoint(point);
}

QPolygonF CRect::checkpolygon()
{
    QPolygonF A(rect);
    return A;
}
