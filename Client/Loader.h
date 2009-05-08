#ifndef LOADER_H
#define LOADER_H

#include <QDialog>
#include "ui_Loader.h"

class Loader : public QDialog
{
    Q_OBJECT

public:
    Loader(QObject *parent = 0);
    bool event(QEvent *event);

private:
    Ui::Window ui;
    int processes;
    int processesComplete;
    QObject *parent;

    void    loadPlugins();
    void    loadNetwork();
    void    loadConfig();
};

#endif // LOADER_H
