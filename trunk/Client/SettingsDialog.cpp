#include "SettingsDialog.h"

#include <QtGui>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDir>
#include <QLineEdit>
#include <QGroupBox>
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

SettingsDialog::~SettingsDialog()
{
    delete this->settings;
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
    foreach (QString key, settings->childKeys())
        pluginLayout->addRow(key, new QLineEdit(settings->value(key).toString()));
    if (!settings->childKeys().contains("Load", Qt::CaseInsensitive))
        pluginLayout->insertRow(0, "Load", new QLineEdit(""));
    if (!settings->childKeys().contains("SystemDirectoryPath", Qt::CaseInsensitive))
        pluginLayout->insertRow(0, "SystemDirectoryPath", new QLineEdit(""));
    if (!settings->childKeys().contains("UserDirectoryPath", Qt::CaseInsensitive))
        pluginLayout->insertRow(0, "UserDirectoryPath", new QLineEdit(""));
    settings->endGroup();
    ui.PluginTab->setLayout(pluginLayout);
}

void SettingsDialog::FillNetworkTab()
{
    QVBoxLayout *networkLayout;
    QFormLayout *generalLayout;
    QFormLayout *sessionLayout;
    QGroupBox   *generalBox;
    QGroupBox   *sessionBox;

    networkLayout = new QVBoxLayout(this->ui.NetworkTab);
    generalBox = new QGroupBox("General");
    sessionBox = new QGroupBox("Session");
    networkLayout->addWidget(generalBox);
    networkLayout->addWidget(sessionBox);
    generalLayout = new QFormLayout(generalBox);
    sessionLayout = new QFormLayout(sessionBox);
    settings->beginGroup("Network");
    foreach (QString key, settings->childKeys())
        generalLayout->addRow(key, new QLineEdit(settings->value(key).toString()));
    if (!settings->childKeys().contains("Server", Qt::CaseInsensitive))
        generalLayout->insertRow(0, "Server", new QLineEdit(""));
    if (!settings->childKeys().contains("Port", Qt::CaseInsensitive))
        generalLayout->insertRow(0, "Port", new QLineEdit(""));
    settings->endGroup();
    settings->beginGroup("SESSIONS");
    foreach (QString key, settings->childKeys())
        sessionLayout->addRow(key, new QLineEdit(settings->value(key).toString()));
    settings->endGroup();
    ui.NetworkTab->setLayout(networkLayout);
}
