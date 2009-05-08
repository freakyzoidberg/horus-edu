#ifndef LOADER_H
#define LOADER_H

#include <QDialog>
#include "ui_Loader.h"

class Loader : public QDialog
{
    Q_OBJECT

public:
    Loader(QObject *parent = 0);

private:
    Ui::Window ui;
};

#endif // LOADER_H
