/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include "SettingsDialog.h"
#include "../Common/LocalSettings.h"

#include <QtGui>
#include <QFormLayout>
#include <QLabel>
#include <QDir>
#include <QLineEdit>
#include <QGroupBox>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
	ui.setupUi(this);
	connect(ui.buttonBox, SIGNAL(accepted()), this, SLOT(save()));
	fillGeneralTab();
	fillPluginTab();
	fillNetworkTab();
}

void SettingsDialog::fillGeneralTab()
{
    QFormLayout *generalLayout;
    QLineEdit   *line;
	LocalSettings settings;

	generalLayout = new QFormLayout(ui.GeneralTab);
	foreach (QString key, settings.childKeys())
    {
		line = new QLineEdit(settings.value(key).toString());
        if (key == "Version")
            line->setDisabled(true);
        line->setObjectName(key);
        generalLayout->addRow(key, line);
    }
	if ( ! settings.childKeys().contains("LessonsDirectoryPath", Qt::CaseInsensitive))
    {
        line = new QLineEdit();
        line->setObjectName("LessonsDirectoryPath");
        generalLayout->insertRow(0, "LessonDirectoryPath", line);
    }
}

void SettingsDialog::fillPluginTab()
{
    QFormLayout *pluginLayout;
    QLineEdit   *line;
	LocalSettings settings;

	pluginLayout = new QFormLayout(ui.PluginTab);
	settings.beginGroup("Plugins");
	foreach (QString key, settings.childKeys())
    {
		line = new QLineEdit(settings.value(key).toString());
        line->setObjectName(key);
        pluginLayout->addRow(key, line);
    }
	if ( ! settings.childKeys().contains("SystemDirectoryPath", Qt::CaseInsensitive))
    {
        line = new QLineEdit();
        line->setObjectName("SystemDirectoryPath");
        pluginLayout->insertRow(0, "SystemDirectoryPath", line);
    }
	if ( ! settings.childKeys().contains("UserDirectoryPath", Qt::CaseInsensitive))
    {
        line = new QLineEdit();
        line->setObjectName("UserDirectoryPath");
        pluginLayout->insertRow(0, "UserDirectoryPath", line);
    }
	settings.endGroup();
}

void SettingsDialog::fillNetworkTab()
{
    QVBoxLayout *networkLayout;
    QFormLayout *generalLayout;
    QGroupBox   *generalBox;
    QLineEdit   *line;
	LocalSettings settings;

	networkLayout = new QVBoxLayout(ui.NetworkTab);
    generalBox = new QGroupBox(tr("General"));
    networkLayout->addWidget(generalBox);
    generalLayout = new QFormLayout(generalBox);
	settings.beginGroup("Network");
	foreach (QString key, settings.childKeys())
    {
		line = new QLineEdit(settings.value(key).toString());
        line->setObjectName(key);
        generalLayout->addRow(key, line);
    }
	if ( ! settings.childKeys().contains("Server", Qt::CaseInsensitive))
    {
        line = new QLineEdit();
        line->setObjectName("Server");
        generalLayout->insertRow(0, tr("Server"), line);
    }
	if ( ! settings.childKeys().contains("Port", Qt::CaseInsensitive))
    {
        line = new QLineEdit();
        line->setObjectName("Port");
        generalLayout->insertRow(0, tr("Port"), line);
    }
	if ( ! settings.childKeys().contains("PortTransfert", Qt::CaseInsensitive))
    {
        line = new QLineEdit();
        line->setObjectName("PortTransfert");
        generalLayout->insertRow(0, tr("PortTransfert"), line);
    }
	settings.endGroup();
}

void SettingsDialog::save()
{
	LocalSettings settings;

	foreach (QLineEdit *line, ui.GeneralTab->findChildren<QLineEdit *>())
		settings.setValue(line->objectName(), line->text());

	settings.beginGroup("Plugins");
	foreach (QLineEdit *line, ui.PluginTab->findChildren<QLineEdit *>())
		settings.setValue(line->objectName(), line->text());
	settings.endGroup();

	foreach (QLineEdit *line, ui.NetworkTab->findChildren<QLineEdit *>())
		settings.setValue("Network/" + line->objectName(), line->text());
}
