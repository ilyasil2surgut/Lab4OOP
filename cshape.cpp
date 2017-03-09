#include "cshape.h"

CShape::CShape(QGraphicsScene *scene)
{
    mainscene=scene;
    isselected=false;
    name="CShape";
    qDebug()<<"CShape added";
    standardpen=QPen(Qt::blue);
    standardpen.setWidth(3);
    selcurpen=QPen(Qt::yellow);
    selcurpen.setWidth(3);
    curpen=QPen(Qt::green);
    curpen.setWidth(8);
    selpen=QPen(Qt::red);
    selpen.setWidth(8);
}

bool CShape::isSelected()
{
    return isselected;
}

bool CShape::isCurrent()
{
    return iscurrent;
}

QString CShape::classname()
{
    return name;
}

void CShape::selected()
{
    if(isselected){
        isselected=false;
        setStyle();
    }
    else{
        isselected=true;
        setStyle();
    }
}

void CShape::setcurrent()
{
    iscurrent=true;
    setStyle();
}

void CShape::removecurrent()
{
    if(iscurrent){
        iscurrent=false;
        setStyle();
    }
}
