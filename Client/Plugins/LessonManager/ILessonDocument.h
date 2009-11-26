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
#ifndef ILESSONDOCUMENT_H
#define ILESSONDOCUMENT_H

#include <QObject>
#include <QHash>
#include <QVariant>
#include <QString>

#include "ILessonData.h"
#include "ILesson.h"
#include "ILessonSection.h"

class IController;

class ILessonDocument : public ILessonData
{
    Q_OBJECT

public:
	inline ILessonDocument(QObject *parent) : ILessonData(parent) {}
	inline ILessonDocument(ILesson *parent) : ILessonData(parent) {}
	inline ILessonDocument(ILessonSection *parent) : ILessonData(parent) {}
    virtual QHash<QString, QVariant> &getParameters() = 0;
	virtual void setId(int id) = 0;
	virtual int getId() = 0;
    virtual void setContent(QString content) = 0;
    virtual QString getContent() const = 0;
    virtual QString getType() const = 0;
    virtual void setType(QString type) = 0;
};

#endif // ILESSONDOCUMENT_H
