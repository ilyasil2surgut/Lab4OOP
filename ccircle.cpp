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
    Center=point;
    radius=R;
//    qDebug()<<"Circle added";
    name="CCircle";
    isselected=false;
    flag=false;
}

void CCircle::draw()
{
    item=new QGraphicsEllipseItem();
    setitem(item);
}

void CCircle::removes()
{
    mainscene->removeItem(item);
    qDebug()<<"Circle removed"<<Center;
}

QString CCircle::save()
{
    QStringList out;
    out<<classname();out<<":";
    out<<QString::number(Center.x())<<" ";
    out<<QString::number(Center.y())<<" ";
    out<<QString::number(radius)<<"\n";
    return out.join(QString());
}

void CCircle::load(QString str)
{
    if(str.split(":").first()==classname()){
        QStringList list=str.split(":").last().split(" ");
        double x=list.first().toInt();list.pop_front();
        double y=list.first().toInt();list.pop_front();
        Center=QPointF(x,y);
        radius=list.first().toInt();list.pop_front();
    }
}

ISaveable *CCircle::clone()
{
    return new CCircle(Center,mainscene,radius);
}

void CCircle::StartTempDraw(QPointF point)
{
    if(flag){
        Center=point;radius=0;
        draw();
    }
}
void CCircle::ContTempDraw(QPointF point)
{
    if(flag){
        radius=QLineF(Center,point).length();
        redraw();
    }
}
void CCircle::FinishTempDraw(QPointF point)
{
    if(flag){
        radius=QLineF(Center,point).length();
        flag=false;
        item->setTransformOriginPoint(QPointF(radius,radius));
        setRotationCenter(center());
        redraw();
    }
}

bool CCircle::canRotate(double)
{
    return true;
}

void CCircle::Rotate(QPointF)
{

}

QPointF CCircle::center()
{
    return Center;
}

void CCircle::redraw()
{
    QPointF topleft(Center.x()-radius,Center.y()-radius);
    QPointF topright(Center.x()+radius,Center.y()+radius);
    QRectF rect(topleft,topright);
    item->setRect(rect);
}
