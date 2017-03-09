#include "cgroup.h"


CGroup::CGroup(QGraphicsScene *scene):CShape(scene)
{

}

void CGroup::addtogroup(CShape *item)
{
    group.append(item);
    qDebug()<<"Item added to group";
}

void CGroup::setStyle()
{
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        i->current()->setStyle();
    }
}

void CGroup::draw()
{
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        i->current()->draw();
    }
}

void CGroup::redraw()
{
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        i->current()->redraw();
    }
}

void CGroup::StartTempDraw(QPointF point)
{

}

void CGroup::ContTempDraw(QPointF point)
{

}

void CGroup::FinishTempDraw(QPointF point)
{

}

bool CGroup::pointInside(QPointF point)
{
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        if(i->current()->pointInside(point)) return true;
    }
    return false;
}
