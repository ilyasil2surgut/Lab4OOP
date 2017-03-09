#ifndef EDITOR_H
#define EDITOR_H

#include <QGraphicsView>
#include <../lab3oop/slstorage.h>
#include <../OOP4/ccircle.h>
#include <../OOP4/state.h>
#include <QGraphicsScene>
#include <QSpinBox>
#include <crect.h>

class Editor : public QGraphicsView
{
    Q_OBJECT
public:
    Editor(QGraphicsView *_view,QListWidget* _listwidget, State *_state,QSpinBox *_radius,QWidget * parent = 0);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void drawlistwidget();
    void redraw();
    void saveItems();
    void loadItems();
private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    QListWidget *listwidget;
    QSpinBox *radius;
    State *state;
    void setup();
    SLStorage<CShape*> Objects;
    QPen *selectpen;

signals:
    void redraws();

public slots:
    removes();
};

#endif // EDITOR_H
