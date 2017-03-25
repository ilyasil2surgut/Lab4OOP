#include "cnpolygon.h"


CNpolygon::CNpolygon(QGraphicsScene *scene, int n):CShape(scene)
{
    name="CNpolygon";
    flag=true;
    sides=n;
    qDebug()<<"CNpolygon with N:"<<sides;
}

CNpolygon::CNpolygon(QGraphicsScene *scene, QPolygonF pol, int n):CShape(scene)
{
    name="CNpolygon";
    flag=false;
    sides=n;
    polygon=pol;
}

QPolygonF CNpolygon::createpolygon(QPointF center, double R, int n)
{
    QPolygonF Pol;
    for(int i=0;i<n;i++){
        QPointF a;
        a.setX((R*qSin(2*M_PI/n*i)));
        a.setY((R*qCos(2*M_PI/n*i)));
        a+=center;
        Pol << a;
    }
    return Pol;
}

void CNpolygon::removes()
{
    mainscene->removeItem(item);
}

ISaveable *CNpolygon::clone()
{
    return new CNpolygon(mainscene,polygon,sides);
}

void CNpolygon::load(QString)
{

}

QString CNpolygon::save()
{
    QStringList out;
    out<<classname()<<":";
    out<<QString::number(sides)<<" ";
    for(int i=0;i<sides;i++){
        out<<QString::number(polygon.at(i).x())<<" ";
        out<<QString::number(polygon.at(i).y())<<" ";
    }
    return out.join(QString());
}

bool CNpolygon::pointInside(QPointF point)
{
    return item->contains(point);
}

void CNpolygon::redraw()
{
    item->setPolygon(polygon);
}

void CNpolygon::draw()
{
    item=new QGraphicsPolygonItem();
    redraw();
    mainscene->addItem(item);
    setStyle();
    item->show();
}

void CNpolygon::setStyle()
{
    if(iscurrent&&isselected)item->setPen(selcurpen);
    else if(iscurrent)item->setPen(curpen);
    else if(isselected)item->setPen(selpen);
    else item->setPen(standardpen);
}

void CNpolygon::FinishTempDraw(QPointF point)
{
    if(flag){
        radius=QLineF(center,point).length();
        polygon=createpolygon(center,radius,sides);
        flag=false;
        redraw();
    }
}

void CNpolygon::ContTempDraw(QPointF point)
{
    if(flag){
        radius=QLineF(center,point).length();
        polygon=createpolygon(center,radius,sides);
        redraw();
    }
}

void CNpolygon::StartTempDraw(QPointF point)
{
    if(flag){
        center=point;radius=0;
        polygon=createpolygon(center,radius,sides);
        draw();
    }
}
