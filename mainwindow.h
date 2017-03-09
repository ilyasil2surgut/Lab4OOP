#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <state.h>
#include <editor.h>
#include <ccircle.h>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionSave_triggered();

    void on_actionLoad_triggered();

private:
    Ui::MainWindow *ui;
    Editor* editor;
    State* state;
};

#endif // MAINWINDOW_H
