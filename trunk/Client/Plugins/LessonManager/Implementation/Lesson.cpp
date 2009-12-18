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
#include "Lesson.h"
#include "LessonSection.h"
#include "LessonDocument.h"
#include "../IDocumentController.h"

Lesson::Lesson(FileData *parent) : ILesson(NULL), _currentData(NULL)
{
	xmlFile = new QFile(parent->fileName());
    QXmlSimpleReader xmlReader;
    QXmlInputSource *source = new QXmlInputSource(xmlFile);
    xmlReader.setContentHandler(this);
    xmlReader.setErrorHandler(this);
    bool ok = xmlReader.parse(source);
    if (ok == false)
        qDebug() << "Error parsing metadata";
	_fileData = parent;
	if (icon == NULL)
		icon = new QIcon(":/Icons/LessonIcon.png");
}

QVariant Lesson::data(int, int role) const
{
    if (role == Qt::DisplayRole)
        return QVariant(getTitle());
    else if (role == Qt::DecorationRole)
		return QVariant(*icon);
    return QVariant();
}

bool    Lesson::startElement(const QString &, const QString &, const QString &qName, const QXmlAttributes &atts)
{
    int idx = -1;
    if (qName == "Lesson" && _currentData == NULL)
    {
        _currentData = this;
    }
    else if (qName == "Section" && _currentData)
    {
        Lesson *lesson = qobject_cast<Lesson *>(_currentData);
        LessonSection *section = qobject_cast<LessonSection *>(_currentData);
        if (lesson)
            _currentData = new LessonSection(lesson);
        else if (section)
            _currentData = new LessonSection(section);
        else
            return false;
    }
    else if (qName == "Document" && _currentData)
    {
        Lesson *lesson = qobject_cast<Lesson *>(_currentData);
        LessonSection *section = qobject_cast<LessonSection *>(_currentData);
        if (lesson)
            _currentData = new LessonDocument(lesson);
        else if (section)
            _currentData = new LessonDocument(section);
        else
            return false;
        LessonDocument *document = qobject_cast<LessonDocument *>(_currentData);
        if ((idx = atts.index("type")) != -1)
		{
            document->setType(atts.value(idx));
			if (docIcons.contains(atts.value(idx)))
				document->setIcon(docIcons[atts.value(idx)]);
		}
		else
		{
			return false;
		}
        if ((idx = atts.index("id")) != -1)
			document->setId(QVariant(atts.value(idx)).toInt());
		else
			return false;
        for (int i = 0; i < atts.count(); ++i)
        {
            if (atts.value(i) != "title" && atts.value(i) != "type")
                document->getParameters().insert(atts.qName(i), QVariant(atts.value(i)));
        }
        startCDATA();
    }
    else
    {
        return false;
    }
    if ((idx = atts.index("title")) != -1)
        _currentData->setTitle(atts.value(idx));
    return true;
}

bool    Lesson::endElement(const QString &, const QString &, const QString &)
{
    if (_currentData)
    {
        if (qobject_cast<LessonDocument *>(_currentData))
            endCDATA();
        _currentData = qobject_cast<ILessonData *>(_currentData->parent());
    }
    return true;
}

bool    Lesson::characters(const QString& ch)
{
    LessonDocument* document = qobject_cast<LessonDocument*>(_currentData);
    if (document)
        document->setContent(ch);
    return true;
}

QHash<FileData *, Lesson *> Lesson::lessons;
QHash<QString, QIcon> Lesson::docIcons;

Lesson *Lesson::createLesson(FileData *data, PluginManager *pluginManager)
{
	if (docIcons.empty())
	{
		QList<IDocumentController *> controllersList = pluginManager->findPlugins<IDocumentController *>();
		foreach (IDocumentController *controller, controllersList)
			docIcons[controller->getSupportedType()] = controller->getIcon();
	}
	if (lessons.contains(data))
		return *(lessons.find(data));
	Lesson *res = new Lesson(data);
	lessons.insert(data, res);
	return res;
}

QIcon *Lesson::icon = NULL;
