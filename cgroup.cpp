#include "cgroup.h"


CGroup::CGroup(QGraphicsScene *scene):CShape(scene)
{
    name="Group";
    mainscene=scene;
    group.addPrototype(new CCircle(mainscene));
    group.addPrototype(new CRect(mainscene));
}

void CGroup::addtogroup(CShape *item)
{
    group.append(item);
    if(item->isCurrent()) {
        iscurrent=true;
        setcurrent();
    }
    qDebug()<<"Item added to group";
    selected();
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

QString CGroup::save()
{

}

void CGroup::load(QString)
{

}

ISaveable *CGroup::clone()
{

}

void CGroup::removes()
{
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        i->current()->removes();
    }
}

bool CGroup::isSelected()
{
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        if(i->current()->isSelected())return true;
    }
    return false;
}

bool CGroup::isCurrent()
{
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        if(i->current()->isCurrent())return true;
    }
    return false;
}

void CGroup::selected()
{
    isselected=true;
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        i->current()->selected();
    }
}

void CGroup::unselected()
{
    isselected=false;
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        i->current()->unselected();
    }
}

void CGroup::setcurrent()
{
    iscurrent=true;
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        i->current()->setcurrent();
    }
}

void CGroup::removecurrent()
{
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        i->current()->removecurrent();
    }
}
