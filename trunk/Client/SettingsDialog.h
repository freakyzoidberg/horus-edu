#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

#include "ui_SettingsDialog.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(QWidget *parent);

private:
    Ui::Dialog  ui;
};

#endif // SETTINGSDIALOG_H
