#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_MainWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QObject *parent);

private slots:
    void editSettings();

private:
    void createActions();
    void createMenus();

    Ui::MainWindow ui;
    QObject *parent;

    QMenu   *fileMenu;
    QMenu   *editMenu;

    QAction *exitAction;
    QAction *settingsAction;
};

#endif // MAINWINDOW_H
