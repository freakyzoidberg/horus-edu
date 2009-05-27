#include "SettingsDialog.h"

#include <QtGui>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDir>
#include <QLineEdit>
#include <QDebug>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    this->settings = new QSettings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat, this);
    this->ui.setupUi(this);
    this->FillGeneralTab();
    this->FillPluginTab();
    this->FillNetworkTab();
}

void SettingsDialog::FillGeneralTab()
{
    QVBoxLayout *generalLayout;

    generalLayout = new QVBoxLayout(this->ui.GeneralTab);
    generalLayout->addWidget(new QLabel("No general settings for now..."));
    ui.GeneralTab->setLayout(generalLayout);
}

void SettingsDialog::FillPluginTab()
{
    QFormLayout *pluginLayout;

    pluginLayout = new QFormLayout(this->ui.PluginTab);
    settings->beginGroup("Plugins");
    qDebug() << settings->childKeys();
    foreach (QString key, settings->childKeys())
        pluginLayout->addRow(key, new QLineEdit(settings->value(key).toString()));
    settings->endGroup();
    ui.PluginTab->setLayout(pluginLayout);
}

void SettingsDialog::FillNetworkTab()
{
}
