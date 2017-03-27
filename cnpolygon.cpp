#include "cnpolygon.h"


CNpolygon::CNpolygon(QGraphicsScene *scene, int n):CShape(scene)
{
    name="CNpolygon";
    flag=true;
    sides=n;
    qDebug()<<"CNpolygon with N:"<<sides;
}

CNpolygon::CNpolygon(QGraphicsScene *scene, QPolygonF pol, QPointF centerpoint, int n, double angle):CShape(scene)
{
    name="CNpolygon";
    flag=false;
    sides=n;
    polygon=pol;
    Center=centerpoint;
    Angle=angle;
}

QPolygonF CNpolygon::createpolygon(QPointF centerpoint, double R, int n)
{
    QPolygonF Pol;
    for(int i=0;i<n;i++){
        QPointF a;
        a.setX((R*qSin(2*M_PI/n*i)));
        a.setY((R*qCos(2*M_PI/n*i)));
        a+=centerpoint;
        Pol << a;
    }
    return Pol;
}

void CNpolygon::removes()
{
    mainscene->removeItem(item);
}

void CNpolygon::Rotate(QPointF end)
{
    item->setRotation(calculateAngle(end));
    Angle=calculateAngle(end);
}

void CNpolygon::Move(QPointF destination)
{
    Center=Center+movedelta(destination);
    polygon=createpolygon(Center,radius,sides);
    redraw();
}

QPointF CNpolygon::center()
{
    return Center;
}

void CNpolygon::setRotationCenter(QPointF point)
{
    rotationcenter=point;
    item->setTransformOriginPoint(RotationCenter());

}

QPolygonF CNpolygon::checkpolygon()
{
    return polygon;
}

ISaveable *CNpolygon::clone()
{
    return new CNpolygon(mainscene,polygon,Center,sides,Angle);
}

void CNpolygon::load(QString str)
{
    QStringList list=str.split(":").last().split(" ");
    sides=list.first().toInt();list.pop_front();
    Angle=list.first().toInt();list.pop_front();
    Center.setX(list.first().toInt());list.pop_front();
    Center.setY(list.first().toInt());list.pop_front();
    QPolygonF pol;
    for(int i=0;i<sides;i++){
        QPointF a(list[0].toInt(),list[1].toInt());
        pol<<a;
        list.pop_front();
        list.pop_front();
    }
    polygon=pol;
}

QString CNpolygon::save()
{
    QStringList out;
    out<<classname()<<":";
    out<<QString::number(sides)<<" ";
    out<<QString::number(Angle)<<" ";
    out<<QString::number(Center.x())<<" ";
    out<<QString::number(Center.y())<<" ";
    for(int i=0;i<sides;i++){
        out<<QString::number(polygon.at(i).x())<<" ";
        out<<QString::number(polygon.at(i).y())<<" ";
    }
    return out.join(QString());
}

void CNpolygon::redraw()
{
    item->setPolygon(polygon);
}

void CNpolygon::draw()
{
    item=new QGraphicsPolygonItem();
    setitem(item);
}

void CNpolygon::FinishTempDraw(QPointF point)
{
    if(flag){
        radius=QLineF(Center,point).length();
        polygon=createpolygon(Center,radius,sides);
        flag=false;
        setRotationCenter(center());
        redraw();
    }
}

void CNpolygon::ContTempDraw(QPointF point)
{
    if(flag){
        radius=QLineF(Center,point).length();
        polygon=createpolygon(Center,radius,sides);
        redraw();
    }
}

void CNpolygon::StartTempDraw(QPointF point)
{
    if(flag){
        Center=point;radius=0;
        polygon=createpolygon(Center,radius,sides);
        draw();
    }
}
