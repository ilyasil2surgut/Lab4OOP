#ifndef CLINE_H
#define CLINE_H
#include <cshape.h>
#include <QLineF>

class CLine:public CShape
{
public:
    CLine(QGraphicsScene *scene);
    CLine(QGraphicsScene *scene,QLineF line);
    bool pointInside(QPointF point);
    void draw();
    void redraw();
    virtual void setStyle();
    virtual void removes();
    QString save();
    void load(QString);
    ISaveable *clone();
    void StartTempDraw(QPointF point);
    void ContTempDraw(QPointF point);
    void FinishTempDraw(QPointF point);
    QPolygonF createclickpol();
private:
    QLineF line;
    QGraphicsLineItem *item;
};

#endif // CLINE_H
