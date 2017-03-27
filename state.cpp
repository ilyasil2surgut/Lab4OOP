#include "state.h"

State::State(QObject *parent) : QObject(parent)
{
    add_s=true;
    select_s=false;
    remove_s=false;
    circle_s=true;
    rectangle_s=false;
    line_s=false;
    polygon_s=false;
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

bool State::rotatestate()
{
    return rotate_s;
}

bool State::movestate()
{
    return move_s;
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

bool State::linestate()
{
    return line_s;
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
    rotate_s=false;
    move_s=false;
    emit(addstate());
}

State::selects()
{
    add_s=false;
    select_s=true;
    remove_s=false;
    group_s=false;
    rotate_s=false;
    move_s=false;
    emit(selectstate());
}

State::removes()
{
    add_s=false;
    select_s=false;
    remove_s=true;
    group_s=false;
    rotate_s=false;
    move_s=false;
    emit(removestate());
}

State::groups()
{
    add_s=false;
    select_s=false;
    remove_s=false;
    group_s=true;
    rotate_s=false;
    move_s=false;
    qDebug()<<"Group state";
    emit(groupstate());

}

State::rotates()
{
    add_s=false;
    select_s=false;
    remove_s=false;
    group_s=false;
    rotate_s=true;
    move_s=false;
    qDebug()<<"Rotate state";
    emit(groupstate());
}

State::moves()
{
    add_s=false;
    select_s=false;
    remove_s=false;
    group_s=false;
    rotate_s=false;
    move_s=true;
    qDebug()<<"Rotate state";
    emit(groupstate());
}

State::circle()
{
    circle_s=true;
    rectangle_s=false;
    polygon_s=false;
    line_s=false;
    adds();
    qDebug()<<"Circle state";
    emit(circlestate());
}
State::rectangle()
{
    circle_s=false;
    rectangle_s=true;
    polygon_s=false;
    line_s=false;
    adds();
    qDebug()<<"Rectangle state";
    emit(rectstate());
}

State::polygon()
{
    circle_s=false;
    rectangle_s=false;
    polygon_s=true;
    line_s=false;
    adds();
    qDebug()<<"Polygon state";
    emit(polstate());
}

State::line()
{
    line_s=true;
    circle_s=false;
    rectangle_s=false;
    polygon_s=false;
    adds();
    qDebug()<<"Line state";
    emit(linestate());
}

