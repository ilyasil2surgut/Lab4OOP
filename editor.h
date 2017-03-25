#ifndef EDITOR_H
#define EDITOR_H

#include <QGraphicsView>
#include <../lab3oop/slstorage.h>
#include <ccircle.h>
#include <state.h>
#include <QGraphicsScene>
#include <QSpinBox>
#include <crect.h>
#include <cgroup.h>
#include <cnpolygon.h>

class Editor : public QGraphicsView
{
    Q_OBJECT
public:
    Editor(QGraphicsView *_view,QListWidget* _listwidget, State *_state,QSpinBox *polygon,QWidget * parent = 0);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseDoubleClickEvent(QMouseEvent *event);
    void drawlistwidget();
    void redraw();
    void saveItems();
    void loadItems();
    void ungroup(CGroup* object);

private:
    QGraphicsView *view;
    QGraphicsScene *scene;
    QListWidget *listwidget;
    QSpinBox *poly;
    State *state;
    void setup();
    SLStorage<CShape*> Objects;
    QPen *selectpen;

signals:
    void redraws();

public slots:
    removes();
    void groupItems();
    void ungroupItems();
};

#endif // EDITOR_H
