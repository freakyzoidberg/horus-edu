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
	Ui::Dialog		ui;

	void			fillGeneralTab();
	void			fillPluginTab();
	void			fillNetworkTab();

private slots:
	void			save();
};

#endif // SETTINGSDIALOG_H
