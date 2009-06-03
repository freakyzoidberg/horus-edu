#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QTreeWidget>
#include <QPushButton>

namespace Ui
{
    class MainWindowClass;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void explorer();
    void ViewLesson();
private:
    Ui::MainWindowClass *ui;
    QWidget *fenetre;
    QTreeWidget *tree;
    QPushButton *french;
    QPushButton *english;
    QPushButton *math;
    QPushButton *svt;

};

#endif // MAINWINDOW_H
