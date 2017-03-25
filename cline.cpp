#include "cline.h"


CLine::CLine(QGraphicsScene *scene):CShape(scene)
{
    name="CLine";
    flag=true;
}

CLine::CLine(QGraphicsScene *scene, QLineF _line):CShape(scene)
{
    name="CLine";
    flag=false;
    line=_line;
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
//    clickpolygon=new QGraphicsPolygonItem();
    mainscene->addItem(item);
    //mainscene->addItem(clickpolygon);
    setStyle();
    item->show();
}

void CLine::redraw()
{
    item->setLine(line);
    //createclickpol();
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
//    mainscene->removeItem(clickpolygon);
}

QString CLine::save()
{
    QStringList out;
    out<<classname();out<<":";
    out<<QString::number(line.p1().x())<<" ";
    out<<QString::number(line.p1().y())<<" ";
    out<<QString::number(line.p2().x())<<" ";
    out<<QString::number(line.p2().y())<<"\n";
    return out.join(QString());
}

void CLine::load(QString str)
{
    QStringList list=str.split(":").last().split(" ");
    double x1=list.first().toInt();list.pop_front();
    double y1=list.first().toInt();list.pop_front();
    double x2=list.first().toInt();list.pop_front();
    double y2=list.first().toInt();list.pop_front();
    line.setP1(QPointF(x1,y1));
    line.setP1(QPointF(x2,y2));
}

ISaveable *CLine::clone()
{
    return new CLine(mainscene,line);
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
    QPointF down(0,50);QPointF up(0,-50);
    pol<<(line.p1()+down)<<(line.p1()+up)<<(line.p2()+down)<<(line.p2()+up);
    //qDebug()<<pol;
    return pol;
    //    clickpolygon->setPolygon(pol);
}

bool CLine::canRotate(double)
{
    return false;
}

void CLine::Rotate(QPointF)
{

}

QPointF CLine::center()
{
    return createclickpol().boundingRect().center();
}
