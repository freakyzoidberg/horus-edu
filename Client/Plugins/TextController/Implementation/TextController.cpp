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
#include "TextController.h"

#include <QTextEdit>
#include <QTextEdit>
#include <QPushButton>

const QString       TextController::pluginName() const
{
    return ("textController");
}

const QString       TextController::pluginVersion() const
{
    return ("0.2");
}

const QString       TextController::getSupportedType() const
{
    return ("text");
}

QWidget*            TextController::createDocumentWidget(ILessonDocument *document)
{
	QTextEdit *textedit = 0;

    if (document->getParameters()["input"] == "content")
    {
                textedit = new QTextEdit;
		textedit->setReadOnly(true);
		textedit->setText(document->getContent());
    }
	return (textedit);
}

QWidget             *TextController::editDocument(QFile *, ILessonDocument *document)
{
    QTextEdit           *textEditor = new QTextEdit;
    //QPushButton         *save = new QPushButton("Save");
    QTextDocument       *text = new QTextDocument(document->getContent());

    textEditor->setDocument(text);
    document->setContent(textEditor->document()->toPlainText());
    //connect(save, SIGNAL(clicked()), this, SLOT(saveModifs()));
    return textEditor;
}
