#ifndef LOADER_H
#define LOADER_H

#include <QDialog>

#include "ui_Loader.h"

class ClientApplication;

class Loader : public QDialog
{
    Q_OBJECT

public:
    Loader(ClientApplication *parent);
    bool event(QEvent *event);

private:
    Ui::Window ui;
    int processes;
    int processesComplete;
    ClientApplication *parent;

    void    loadPlugins();
    void    loadNetwork();
    void    loadConfig();
};

#endif // LOADER_H
