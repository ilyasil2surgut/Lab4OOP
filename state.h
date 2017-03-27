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
    bool rotatestate();
    bool movestate();

    bool circlestate();
    bool rectstate();
    bool polstate();
    bool linestate();

    bool groupstate();
private:
    bool add_s;
    bool select_s;
    bool remove_s;
    bool rotate_s;
    bool move_s;

    bool circle_s;
    bool rectangle_s;
    bool polygon_s;
    bool line_s;

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
    rotates();
    moves();

    circle();
    rectangle();
    polygon();
    line();
};

#endif // STATE_H
