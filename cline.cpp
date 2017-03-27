#include "cline.h"


CLine::CLine(QGraphicsScene *scene):CShape(scene)
{
    name="CLine";
    flag=true;
    clickpolygon=new QGraphicsPolygonItem();
}

CLine::CLine(QGraphicsScene *scene, QLineF _line, double angle):CShape(scene)
{
    name="CLine";
    flag=false;
    line=_line;
    Angle=angle;
    clickpolygon=new QGraphicsPolygonItem(createclickpol());
}

bool CLine::pointInside(QPointF point)
{
//    return clickpolygon->contains(point);
    return createclickpol().containsPoint(point,Qt::OddEvenFill);
}

void CLine::draw()
{
    item=new QGraphicsLineItem();
    redraw();
    mainscene->addItem(item);
    mainscene->addItem(clickpolygon);
    setStyle();
    item->show();
    item->setRotation(Angle);
    clickpolygon->setRotation(Angle);
    clickpolygon->hide();
}

void CLine::redraw()
{
    item->setLine(line);
    clickpolygon->setPolygon(createclickpol());
}

void CLine::setStyle()
{
    if(iscurrent&&isselected)item->setPen(selcurpen);
    else if(iscurrent)item->setPen(curpen);
    else if(isselected)item->setPen(selpen);
    else item->setPen(standardpen);
}

void CLine::removes()
{
    mainscene->removeItem(item);
    mainscene->removeItem(clickpolygon);
}

QString CLine::save()
{
    QStringList out;
    out<<classname();out<<":";
    out<<QString::number(Angle)<<" ";
    out<<QString::number(line.p1().x())<<" ";
    out<<QString::number(line.p1().y())<<" ";
    out<<QString::number(line.p2().x())<<" ";
    out<<QString::number(line.p2().y())<<"\n";
    return out.join(QString());
}

void CLine::load(QString str)
{
    QStringList list=str.split(":").last().split(" ");
    Angle=list.first().toInt();list.pop_front();
    double x1=list.first().toInt();list.pop_front();
    double y1=list.first().toInt();list.pop_front();
    double x2=list.first().toInt();list.pop_front();
    double y2=list.first().toInt();list.pop_front();
    line.setP1(QPointF(x1,y1));
    line.setP1(QPointF(x2,y2));
}

ISaveable *CLine::clone()
{
    return new CLine(mainscene,line,Angle);
}

void CLine::StartTempDraw(QPointF point)
{
    if(flag){
        line.setP1(point);
        line.setP2(point);
        draw();
    }
}

void CLine::ContTempDraw(QPointF point)
{
    if(flag){
        line.setP2(point);
        redraw();
    }
}

void CLine::FinishTempDraw(QPointF point)
{
    if(flag){
        line.setP2(point);
        redraw();
        flag=false;
        setRotationCenter(center());
    }
}

QPolygonF CLine::createclickpol()
{
    QPolygonF pol;
    QPointF down(15,15);QPointF up(-15,-15);
    pol<<(line.p1()+down)<<(line.p2()+down)<<(line.p2()+up)<<(line.p1()+up);
    return pol;
}

void CLine::Rotate(QPointF point)
{
    item->setRotation(calculateAngle(point));
    clickpolygon->setRotation(calculateAngle(point));
    Angle=calculateAngle(point);
}

void CLine::Move(QPointF destination)
{
    line.setP1(line.p1()+movedelta(destination));
    line.setP2(line.p1()+movedelta(destination));
    redraw();
}

QPointF CLine::center()
{
    QPointF a;
    a.setX((line.p1().x()+line.p2().x())/2);
    a.setY((line.p1().y()+line.p2().y())/2);
    return a;
}

void CLine::setRotationCenter(QPointF point)
{
    rotationcenter=point;
    item->setTransformOriginPoint(point);
    clickpolygon->setTransformOriginPoint(point);
}

QPolygonF CLine::checkpolygon()
{
    QPolygonF A;
    A<<line.p1()<<line.p2();
    return A;
}
