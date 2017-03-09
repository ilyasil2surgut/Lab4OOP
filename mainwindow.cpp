#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    state=new State();
    editor=new Editor(ui->graphicsView,ui->listWidget,state,ui->spinBox,this);
    connect(ui->pushButton_add,SIGNAL(clicked(bool)),state,SLOT(adds()));
    connect(ui->pushButton_select,SIGNAL(clicked(bool)),state,SLOT(selects()));
    connect(ui->pushButton_remove,SIGNAL(clicked(bool)),editor,SLOT(removes()));
    connect(ui->pb_circle,SIGNAL(clicked(bool)),state,SLOT(circle()));
    connect(ui->pb_rect,SIGNAL(clicked(bool)),state,SLOT(rectangle()));
    ui->spinBox->setValue(50);
    ui->spinBox->setMinimum(1);
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
