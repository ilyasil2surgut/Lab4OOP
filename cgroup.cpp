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
    for()
}
