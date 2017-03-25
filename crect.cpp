#include "crect.h"


CRect::CRect(QGraphicsScene *scene):CShape(scene)
{
    name=QString("Rectangle");
    flag=true;
}

CRect::CRect(QPointF topleft, QPointF bottomright, QGraphicsScene *scene):CShape(scene)
{
    name=QString("Rectangle");
    flag=false;
    rect.setTopLeft(topleft);
    rect.setBottomRight(bottomright);
}

void CRect::draw()
{
    item=new QGraphicsRectItem();
    setitem(item);
}

void CRect::redraw()
{
    item->setRect(rect);
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
        item->setTransformOriginPoint(item->boundingRect().center());
        redraw();
    }
}

QString CRect::save()
{
    QStringList out;
    out<<classname();out<<":";
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
        double x1=list.first().toInt();list.pop_front();
        double y1=list.first().toInt();list.pop_front();
        double x2=list.first().toInt();list.pop_front();
        double y2=list.first().toInt();list.pop_front();
        rect.setCoords(x1,y1,x2,y2);
    }
}

ISaveable *CRect::clone()
{
    return new CRect(rect.topLeft(),rect.bottomRight(),mainscene);
}

void CRect::removes()
{
    mainscene->removeItem(item);
}

bool CRect::canRotate(double angle)
{
//    QGraphicsRectItem *temp=new QGraphicsRectItem(item->rect());
//    mainscene->addItem(temp);
//    temp->setTransformOriginPoint(QPointF(rect.width(),rect.height()));
//    temp->setRotation(angle);
//    if((temp->boundingRect().topLeft().x()<0)||(temp->boundingRect().topLeft().y()<0)) return false;
//    else return true;
    return true;
}

void CRect::Rotate(QPointF end)
{
    if(canRotate(calculateAngle(end)))item->setRotation(calculateAngle(end));
}

QPointF CRect::center()
{
    return item->boundingRect().center();
}
