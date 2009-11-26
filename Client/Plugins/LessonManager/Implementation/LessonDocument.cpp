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
#include "LessonDocument.h"

LessonDocument::LessonDocument(ILessonSection *parent) : ILessonDocument(parent)
{
	if (icon == NULL)
		icon = new QIcon(":/Icons/DocumentIcon.png");
}

LessonDocument::LessonDocument(ILesson *parent) : ILessonDocument(parent)
{
}

QVariant LessonDocument::data(int column, int role) const
{
    if (role == Qt::DisplayRole)
        return QVariant(getTitle());
    else if (role == Qt::DecorationRole)
		return QVariant(*icon);
    return QVariant();
}

void	LessonDocument::setId(int id)
{
	this->_id = id;
}

int	LessonDocument::getId()
{
	return (this->_id);
}

QString LessonDocument::getContent() const
{
        return (this->content);
}

void	LessonDocument::setContent(QString _content)
{
        this->content = _content;
}

QHash<QString, QVariant>	&LessonDocument::getParameters()
{
        return (this->parameters);
}

QString LessonDocument::getType() const
{
    return type;
}

void LessonDocument::setType(QString type)
{
    this->type = type;
}

QIcon *LessonDocument::icon = NULL;
