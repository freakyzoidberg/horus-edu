#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_MainWindow.h"
#include "NetworkManager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QObject *parent);

private slots:
    void on_connectButton_clicked();
    void on_pushButton_clicked();
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
