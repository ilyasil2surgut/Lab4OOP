#ifndef CGROUP_H
#define CGROUP_H
#include <cshape.h>

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
private:
    SLStorage<CShape*> group;
};

#endif // CGROUP_H
