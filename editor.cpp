#include "editor.h"
Editor::Editor(QGraphicsView *_view, QListWidget *_listwidget,State *_state,QSpinBox *_radius, QWidget *parent):QGraphicsView(parent)
{
    view=_view;
    state=_state;
    setup();
    listwidget=_listwidget;
    radius=_radius;
    Objects.addPrototype(new CCircle(scene));
    Objects.addPrototype(new CRect(scene));
    connect(this,SIGNAL(redraws()),scene,SLOT(clear()));
}

void Editor::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"Mouse clicked"<<event->pos();
    if(state->selectstate()){
        int j=0;
        for(Iterator<CShape*>* i=Objects.CreateIterator();!i->Eol();i->next()){
            if(i->current()->pointInside(event->pos())){
                if(i->current()->isSelected())i->current()->unselected();
                else {
                    i->current()->selected();
                    listwidget->setCurrentRow(j);
                    qDebug()<<i->current()->classname()<<" selected";
                }
            }
            j++;
        }
    }
    else if(state->addstate()){
        if(Objects.length()>0)Objects.getlast()->removecurrent();
        if(state->circlestate())Objects.append(new CCircle(scene));
        else if(state->rectstate())Objects.append(new CRect(scene));
        Objects.getlast()->StartTempDraw(event->pos());
        Objects.getlast()->setcurrent();
    }
}

void Editor::mouseReleaseEvent(QMouseEvent *event)
{
    if(!Objects.isEmpty()&&state->addstate()){Objects.getlast()->FinishTempDraw(event->pos());}
    drawlistwidget();
}

void Editor::mouseMoveEvent(QMouseEvent *event)
{
    if(!Objects.isEmpty()&&state->addstate())Objects.getlast()->ContTempDraw(event->pos());
}

void Editor::mouseDoubleClickEvent(QMouseEvent *event)
{

}

void Editor::drawlistwidget()
{
    listwidget->clear();
    for(Iterator<CShape*>* i=Objects.CreateIterator();!i->Eol();i->next()){
        listwidget->addItem(i->current()->save());
    }
}

void Editor::redraw()
{
    //emit redraws();
    for(Iterator<CShape*>* i=Objects.CreateIterator();!i->Eol();i->next()){
        i->current()->draw();
    }
}

void Editor::saveItems()
{
    Objects.Save("../Lab4OOP/storage.txt");
}

void Editor::loadItems()
{
    Objects.Load("../Lab4OOP/storage.txt");
    redraw();
    drawlistwidget();
}

void Editor::setup()
{
    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0,view->width(),view->height());
    setScene(scene);
    setFixedSize(view->width(),view->height());
    move(view->pos()+QPoint(0,40));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setMouseTracking(true);
    show();
    view->hide();
}

Editor::removes()
{
    qDebug()<<"Objects.length()"<<Objects.length();
    bool deleted=false;
    for(int i=0;i<Objects.length();){
        if(Objects.get(i)->isSelected()){
            if(Objects.get(i)->isCurrent()){
                qDebug()<<"To remove"<<Objects.get(i)->save();
                Objects.pop(i)->removes();
                Objects.getlast()->setcurrent();
                i=0;
                deleted=true;
            }
            else
            {
                qDebug()<<"To remove"<<Objects.get(i)->save();
                Objects.pop(i)->removes();
                i=0;
                deleted=true;
            }
        }
        else i++;
    }
    if(!(deleted)){
        for(int i=0;i<Objects.length();)
        {
            if(Objects.get(i)->isCurrent())
            {
                    qDebug()<<"To remove"<<Objects.get(i)->save();
                    Objects.pop(i)->removes();
                    if(!Objects.isEmpty())Objects.getlast()->setcurrent();
                    i=0;
                    break;
            }
            else i++;
        }
    }
    drawlistwidget();
}

