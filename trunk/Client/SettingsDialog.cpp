#include "SettingsDialog.h"

#include <QtGui>
#include <QFormLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDir>
#include <QLineEdit>
#include <QGroupBox>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    this->settings = new QSettings(QDir::homePath() + "/.Horus/Horus Client.conf", QSettings::IniFormat, this);
    this->ui.setupUi(this);
    connect(this->ui.buttonBox, SIGNAL(accepted()), this, SLOT(Save()));
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
}

void SettingsDialog::FillPluginTab()
{
    QFormLayout *pluginLayout;
    QLineEdit   *line;

    pluginLayout = new QFormLayout(this->ui.PluginTab);
    settings->beginGroup("Plugins");
    foreach (QString key, settings->childKeys())
    {
        if (key == "Load")
            line = new QLineEdit(settings->value(key).toStringList().join(", "));
        else
            line = new QLineEdit(settings->value(key).toString());
        line->setObjectName(key);
        pluginLayout->addRow(key, line);
    }
    if (!settings->childKeys().contains("Load", Qt::CaseInsensitive))
    {
        line = new QLineEdit();
        line->setObjectName("Load");
        pluginLayout->insertRow(0, "Load", line);
    }
    if (!settings->childKeys().contains("SystemDirectoryPath", Qt::CaseInsensitive))
    {
        line = new QLineEdit();
        line->setObjectName("SystemDirectoryPath");
        pluginLayout->insertRow(0, "SystemDirectoryPath", line);
    }
    if (!settings->childKeys().contains("UserDirectoryPath", Qt::CaseInsensitive))
    {
        line = new QLineEdit();
        line->setObjectName("UserDirectoryPath");
        pluginLayout->insertRow(0, "UserDirectoryPath", line);
    }
    settings->endGroup();
}

void SettingsDialog::FillNetworkTab()
{
    QVBoxLayout *networkLayout;
    QFormLayout *generalLayout;
    QFormLayout *sessionLayout;
    QGroupBox   *generalBox;
    QGroupBox   *sessionBox;
    QLineEdit   *line;

    networkLayout = new QVBoxLayout(this->ui.NetworkTab);
    generalBox = new QGroupBox("General");
    sessionBox = new QGroupBox("Session");
    networkLayout->addWidget(generalBox);
    networkLayout->addWidget(sessionBox);
    generalLayout = new QFormLayout(generalBox);
    sessionLayout = new QFormLayout(sessionBox);
    settings->beginGroup("Network");
    foreach (QString key, settings->childKeys())
    {
        line = new QLineEdit(settings->value(key).toString());
        line->setObjectName(key);
        generalLayout->addRow(key, line);
    }
    if (!settings->childKeys().contains("Server", Qt::CaseInsensitive))
    {
        line = new QLineEdit();
        line->setObjectName("Server");
        generalLayout->insertRow(0, "Server", line);
    }
    if (!settings->childKeys().contains("Port", Qt::CaseInsensitive))
    {
        line = new QLineEdit();
        line->setObjectName("Port");
        generalLayout->insertRow(0, "Port", line);
    }
    settings->endGroup();
    settings->beginGroup("SESSIONS");
    foreach (QString key, settings->childKeys())
    {
        line = new QLineEdit(settings->value(key).toString());
        line->setObjectName("session_" + key);
        sessionLayout->addRow(key, line);
    }
    settings->endGroup();
}

void SettingsDialog::Save()
{
    foreach (QLineEdit *line, this->ui.GeneralTab->findChildren<QLineEdit *>())
        settings->setValue(line->objectName(), line->text());
    settings->beginGroup("Plugins");
    foreach (QLineEdit *line, this->ui.PluginTab->findChildren<QLineEdit *>())
        if (line->objectName() == "Load")
            settings->setValue(line->objectName(), QStringList(line->text().split(", ", QString::SkipEmptyParts)));
        else
            settings->setValue(line->objectName(), line->text());
    settings->endGroup();
    foreach (QLineEdit *line, this->ui.NetworkTab->findChildren<QLineEdit *>())
        if (line->objectName().contains("session_"))
            settings->setValue("SESSIONS/" + line->objectName().remove(0, 8), line->text());
        else
            settings->setValue("Network/" + line->objectName(), line->text());
}
