#include "state.h"

State::State(QObject *parent) : QObject(parent)
{
    add_s=true;
    select_s=false;
    remove_s=false;
    circle_s=true;
    rectangle_s=false;
    group_s=false;
    emit(addstate());
}

bool State::addstate()
{
    return add_s;
}

bool State::selectstate()
{
    return select_s;
}

bool State::removestate()
{
    return remove_s;
}

bool State::circlestate()
{
    return circle_s;
}

bool State::rectstate()
{
    return rectangle_s;
}

bool State::polstate()
{
    return polygon_s;
}

bool State::groupstate()
{
    return group_s;
}

State::adds()
{
    add_s=true;
    select_s=false;
    remove_s=false;
    group_s=false;
    emit(addstate());
}

State::selects()
{
    add_s=false;
    select_s=true;
    remove_s=false;
    group_s=false;
    emit(selectstate());
}

State::removes()
{
    add_s=false;
    select_s=false;
    remove_s=true;
    group_s=false;
    emit(removestate());
}

State::groups()
{
    add_s=false;
    select_s=false;
    remove_s=false;
    group_s=true;
    qDebug()<<"Group state";
    emit(groupstate());

}

State::circle()
{
    circle_s=true;
    rectangle_s=false;
    polygon_s=false;
    addstate();
    qDebug()<<"Circle state";
    emit(circlestate());
}
State::rectangle()
{
    circle_s=false;
    rectangle_s=true;
    polygon_s=false;
    addstate();
    qDebug()<<"Rectangle state";
    emit(rectstate());
}

State::polygon()
{
    circle_s=false;
    rectangle_s=false;
    polygon_s=true;
    addstate();
    qDebug()<<"Polygon state";
    emit(polstate());
}

