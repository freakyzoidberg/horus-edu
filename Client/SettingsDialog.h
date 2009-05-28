#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

#include "ui_SettingsDialog.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(QWidget *parent);
    ~SettingsDialog();

private:
    Ui::Dialog  ui;
    QSettings   *settings;

    void        FillGeneralTab();
    void        FillPluginTab();
    void        FillNetworkTab();

private slots:
    void        Save();
};

#endif // SETTINGSDIALOG_H
