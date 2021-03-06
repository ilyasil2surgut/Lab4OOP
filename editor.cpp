#include "editor.h"
Editor::Editor(QGraphicsView *_view, QListWidget *_listwidget,State *_state,QSpinBox *polygon, QWidget *parent):QGraphicsView(parent)
{
    view=_view;
    state=_state;
    setup();
    listwidget=_listwidget;
    poly=polygon;
    Objects.addPrototype(new CCircle(scene));
    Objects.addPrototype(new CRect(scene));
    Objects.addPrototype(new CGroup(scene));
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
        else if(state->polstate())Objects.append(new CNpolygon(scene,poly->value()));
        else if(state->linestate())Objects.append(new CLine(scene));
        Objects.getlast()->StartTempDraw(event->pos());
        Objects.getlast()->setcurrent();
    }
    else if(state->rotatestate()){
        for(Iterator<CShape*>* i=Objects.CreateIterator();!i->Eol();i->next()){
            if(i->current()->isSelected()){
                i->current()->initRotation(event->pos());
            }
        }
    }
    else if(state->movestate()){
        for(Iterator<CShape*>* i=Objects.CreateIterator();!i->Eol();i->next()){
            if((i->current()->isSelected())&&(i->current()->pointInside(event->pos()))){
                i->current()->initMove(event->pos());
            }
        }
    }
}

void Editor::mouseReleaseEvent(QMouseEvent *event)
{
    if(!Objects.isEmpty()){
        if(state->addstate())Objects.getlast()->FinishTempDraw(event->pos());
        else if(state->rotatestate()){
            for(Iterator<CShape*>* i=Objects.CreateIterator();!i->Eol();i->next()){
                if(i->current()->isSelected()){
                    if(i->current()->canRotate(i->current()->calculateAngle(event->pos())))i->current()->Rotate(event->pos());
                }
            }
        }
//        else if(state->movestate()){
//            for(Iterator<CShape*>* i=Objects.CreateIterator();!i->Eol();i->next()){
//                if(i->current()->canMove(event->pos())){
//                    i->current()->Move(event->pos());
//                    i->current()->initMove(event->pos());
//                }
//            }
//        }
    }
    drawlistwidget();
}

void Editor::mouseMoveEvent(QMouseEvent *event)
{
    if(!Objects.isEmpty()){
        if(state->addstate())Objects.getlast()->ContTempDraw(event->pos());
        else if(state->rotatestate()){
            for(Iterator<CShape*>* i=Objects.CreateIterator();!i->Eol();i->next()){
                if(i->current()->isSelected()){
                    if(i->current()->canRotate(i->current()->calculateAngle(event->pos())))i->current()->Rotate(event->pos());
                }
            }
        }
        else if(state->movestate()){
            for(Iterator<CShape*>* i=Objects.CreateIterator();!i->Eol();i->next()){
                if((i->current()->isSelected())&&(i->current()->pointInside(event->pos()))){
                    if(i->current()->canMove(event->pos())){
                        i->current()->Move(event->pos());
                        i->current()->initMove(event->pos());
                    }
                }
            }
        }
    }

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

void Editor::ungroup(CGroup *object)
{
    while(!(object->isEmpty())){
        Objects.append(object->popfirst());
    }
}


void Editor::groupItems()
{
    int count=0;
    for(Iterator<CShape*>* i=Objects.CreateIterator();!i->Eol();i->next()){
        if(i->current()->isSelected()) count++;
        //if (count>1) break;
    }
    qDebug()<<count<<" items to be grouped";
    if(count>1){
        CGroup *group=new CGroup(scene);
        for(int i=0;i<Objects.length();){
            if(Objects.get(i)->isSelected()){
                qDebug()<<"i:"<<i<<"Adding to group:"<<Objects.get(i)->save();
                group->addtogroup(Objects.pop(i));
            }
            else i++;
        }
        Objects.append(group);
        drawlistwidget();
    }
    else qDebug()<<"Not enough elements selected";
}

void Editor::ungroupItems()
{
    int count=0;
    for(Iterator<CShape*>* i=Objects.CreateIterator();!i->Eol();i->next()){
        if(i->current()->isSelected()){
            CGroup *object=dynamic_cast<CGroup*>(i->current());
            if(object){
                Objects.pop(count);
                qDebug()<<"Ungrouping ";
                ungroup(object);
                drawlistwidget();
            }
        }
        count++;
    }
}

void Editor::setup()
{
    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0,view->width(),view->height());
    qDebug()<<scene->sceneRect();
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
                qDebug()<<"To remove1"<<Objects.get(i)->save();
                Objects.pop(i)->removes();
                Objects.getlast()->setcurrent();
                deleted=true;
            }
            else
            {
                qDebug()<<"To remove2"<<Objects.get(i)->save();
                Objects.pop(i)->removes();
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
                    qDebug()<<"To remove3"<<Objects.get(i)->save();
                    Objects.pop(i)->removes();
                    if(!Objects.isEmpty())Objects.getlast()->setcurrent();
                    break;
            }
            else i++;
        }
    }
    drawlistwidget();
}

