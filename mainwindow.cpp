#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox->setValue(50);
    ui->spinBox->setMinimum(1);
    ui->sb_polygon->setMinimum(3);
    ui->sb_polygon->setValue(3);
    state=new State();
    editor=new Editor(ui->graphicsView,ui->listWidget,state,ui->sb_polygon,this);
    connect(ui->pushButton_add,SIGNAL(clicked(bool)),state,SLOT(adds()));
    connect(ui->pushButton_select,SIGNAL(clicked(bool)),state,SLOT(selects()));
    connect(ui->pushButton_remove,SIGNAL(clicked(bool)),editor,SLOT(removes()));
    connect(ui->pb_circle,SIGNAL(clicked(bool)),state,SLOT(circle()));
    connect(ui->pb_rect,SIGNAL(clicked(bool)),state,SLOT(rectangle()));
    connect(ui->pb_group,SIGNAL(clicked(bool)),editor,SLOT(groupItems()));
    connect(ui->pb_Ungroup,SIGNAL(clicked(bool)),editor,SLOT(ungroupItems()));
    connect(ui->pb_polygon,SIGNAL(clicked(bool)),state,SLOT(polygon()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSave_triggered()
{
    editor->saveItems();
}

void MainWindow::on_actionLoad_triggered()
{
    editor->loadItems();
}
