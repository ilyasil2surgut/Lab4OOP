#ifndef CGROUP_H
#define CGROUP_H
#include <cshape.h>
#include <ccircle.h>
#include <crect.h>

class CGroup:public CShape
{
public:
    CGroup(QGraphicsScene *scene);
    void addtogroup(CShape* item);
    virtual void setStyle();
    virtual void draw();
    void redraw();
    void StartTempDraw(QPointF point);
    void ContTempDraw(QPointF point);
    void FinishTempDraw(QPointF point);
    virtual bool pointInside(QPointF point);
    virtual QString save();
    virtual void load(QString);
    virtual ISaveable *clone();
    virtual void removes();
    virtual bool isSelected();
    virtual bool isCurrent();
    virtual void selected();
    virtual void unselected();
    virtual void setcurrent();
    virtual void removecurrent();
    virtual bool canRotate(double);
    virtual void Rotate(QPointF);
    virtual void Move(QPointF);
    virtual bool canMove(QPointF);
    virtual void initMove(QPointF);
    virtual void initRotation(QPointF);
    virtual QPolygonF checkpolygon();
    virtual QPointF center();
    CShape* popfirst();
    bool isEmpty();
private:
    SLStorage<CShape*> group;
};

#endif // CGROUP_H
