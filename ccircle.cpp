#include "ccircle.h"


CCircle::CCircle(QGraphicsScene *scene):CShape(scene)
{
//    qDebug()<<"Circle added";
    name="CCircle";
    isselected=false;
    flag=true;
}

CCircle::CCircle(QPointF point,  QGraphicsScene *scene, int R):CShape(scene)
{
    center=point;
    radius=R;
//    qDebug()<<"Circle added";
    name="CCircle";
    isselected=false;
    flag=false;
}

bool CCircle::pointInside(QPointF point)
{
    return item->contains(point);
}

void CCircle::setStyle()
{
    if(iscurrent&&isselected)item->setPen(selcurpen);
    else if(iscurrent)item->setPen(curpen);
    else if(isselected)item->setPen(selpen);
    else item->setPen(standardpen);
}

void CCircle::draw()
{
    item=new QGraphicsEllipseItem();
    redraw();
    mainscene->addItem(item);
    setStyle();
    item->show();
}

void CCircle::removes()
{
    mainscene->removeItem(item);
    qDebug()<<"Circle removed"<<center;
}

QString CCircle::save()
{
    QStringList out;
    out<<classname();out<<":";
    out<<QString::number(center.x())<<" ";
    out<<QString::number(center.y())<<" ";
    out<<QString::number(radius)<<"\n";
    return out.join(QString());
}

void CCircle::load(QString str)
{
    if(str.split(":").first()==classname()){
        QStringList list=str.split(":").last().split(" ");
        double x=list.first().toInt();list.pop_front();
        double y=list.first().toInt();list.pop_front();
        center=QPointF(x,y);
        radius=list.first().toInt();list.pop_front();
    }
}

ISaveable *CCircle::clone()
{
    return new CCircle(center,mainscene,radius);
}

void CCircle::StartTempDraw(QPointF point)
{
    if(flag){
        center=point;radius=0;
        draw();
    }
}
void CCircle::ContTempDraw(QPointF point)
{
    if(flag){
        radius=QLineF(center,point).length();
        redraw();
    }
}
void CCircle::FinishTempDraw(QPointF point)
{
    if(flag){
        radius=QLineF(center,point).length();
        flag=false;
        redraw();
    }
}

void CCircle::redraw()
{
    QPointF topleft(center.x()-radius,center.y()-radius);
    QPointF topright(center.x()+radius,center.y()+radius);
    QRectF rect(topleft,topright);
    item->setRect(rect);
}
