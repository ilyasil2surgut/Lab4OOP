#ifndef STATE_H
#define STATE_H

#include <QObject>
#include <QDebug>

class State : public QObject
{
    Q_OBJECT
public:
    explicit State(QObject *parent = 0);
    bool addstate();
    bool selectstate();
    bool removestate();

    bool circlestate();
    bool rectstate();
    bool polstate();

    bool groupstate();
private:
    bool add_s;
    bool select_s;
    bool remove_s;

    bool circle_s;
    bool rectangle_s;
    bool polygon_s;

    bool group_s;
/*signals:
    s_addstate();
    s_selectstate();
    s_removestate();*/

public slots:
    adds();
    selects();
    removes();
    groups();

    circle();
    rectangle();
    polygon();
};

#endif // STATE_H
