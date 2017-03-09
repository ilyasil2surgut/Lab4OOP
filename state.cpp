#include "state.h"

State::State(QObject *parent) : QObject(parent)
{
    add_s=true;
    select_s=false;
    remove_s=false;
    circle_s=true;
    rectangle_s=false;
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

State::adds()
{
    add_s=true;
    select_s=false;
    remove_s=false;
    emit(addstate());
}

State::selects()
{
    add_s=false;
    select_s=true;
    remove_s=false;
    emit(selectstate());
}

State::removes()
{
    add_s=false;
    select_s=false;
    remove_s=true;
    emit(removestate());
}

State::circle()
{
    circle_s=true;
    rectangle_s=false;
    qDebug()<<"Circle state";
    emit(circlestate());
}
State::rectangle()
{
    circle_s=false;
    rectangle_s=true;
    qDebug()<<"Rectangle state";
    emit(rectstate());
}

