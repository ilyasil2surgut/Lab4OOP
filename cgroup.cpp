#include "cgroup.h"


CGroup::CGroup(QGraphicsScene *scene):CShape(scene)
{
    name="CGroup";
    mainscene=scene;
    group.addPrototype(new CCircle(mainscene));
    group.addPrototype(new CRect(mainscene));
//    group.addPrototype(new CGroup(mainscene));
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
        i->current()->setRotationCenter(center());
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
    QStringList out;
    out<<classname();out<<":";
    out<<QString::number(Angle)<<"|";
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        QString temp=i->current()->save();temp.chop(1);temp.replace(":",";");
        out<<temp;
        out<<"|";
    }
    out<<"\n";
    return out.join(QString());
}

void CGroup::load(QString str)
{
    //group.clear();
    QStringList list=str.split(":").last().split("|");
    Angle=list.first().toInt();list.pop_front();
    list.pop_back();
    Storage<ISaveable*> prototypes=group.Prototypes();
    for(;!list.isEmpty();){
        QString current=list.first();
        list.removeFirst();
        current.replace(";",":");
        QString classname=current.split(":").first();
        for(int j=0;j<prototypes.length();j++){
            if(classname==prototypes.get(j)->classname()){
                prototypes.get(j)->load(current);
                CShape* add=dynamic_cast<CShape*>(prototypes.get(j)->clone());
                if(add){
                    add->draw();
                    addtogroup(add);
                }
            }
        }
    }
}

ISaveable *CGroup::clone()
{
    CGroup* out= new CGroup(mainscene);
    for(int i=0;i<group.length();i++){
        out->addtogroup(group.get(i));
    }
    return out;
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
    iscurrent=false;
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        i->current()->removecurrent();
    }
}

bool CGroup::canRotate(double angle)
{
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        if(!(i->current()->canRotate(angle))){
            return false;
        }
    }
    return true;
}

void CGroup::Rotate(QPointF end)
{
    Angle=calculateAngle(end);
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        i->current()->Rotate(end);
    }

}

void CGroup::Move(QPointF destination)
{
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        i->current()->Move(destination);
    }
}

bool CGroup::canMove(QPointF destination)
{
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        if(!(i->current()->canMove(destination))) return false;
    }
    return true;
}

void CGroup::initMove(QPointF destination)
{
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        i->current()->initMove(destination);
    }
}

void CGroup::initRotation(QPointF point)
{
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        i->current()->initRotation(point);
        i->current()->setRotationCenter(center());
    }
}

QPolygonF CGroup::checkpolygon()
{
    QPolygonF A;
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        A=A.united(i->current()->checkpolygon());
    }
    return A;
}

QPointF CGroup::center()
{
    QPointF A;
    double x,y;
    for(Iterator<CShape*>* i=group.CreateIterator();!i->Eol();i->next()){
        x+=i->current()->center().x();
        y+=i->current()->center().y();
    }
    A.setX(x/group.length());
    A.setY(y/group.length());
    return A;
}

CShape *CGroup::popfirst()
{
    group.getfirst()->setRotationCenter(group.getfirst()->center());
    group.getfirst()->determineAngle();
    return group.pop(0);
}

bool CGroup::isEmpty()
{
    return group.isEmpty();
}
