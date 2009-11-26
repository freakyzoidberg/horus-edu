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
#ifndef __PDFCONTROLLER_H__
# define __PDFCONTROLLER_H__

# include <QObject>
# include <QLabel>
# include <QRectF>

# include "../../../../Common/Plugin.h"
# include "../../../../Common/FileData.h"
# include "../../../../Common/FileDataPlugin.h"
# include "../../LessonManager/ILessonManager.h"
# include "../../LessonManager/IDocumentController.h"
# include "../../PdfDisplayer/IPdfRendering.h"
# include "../../Course/IItems.h"

class   PdfController : public Plugin, public IDocumentController
{
        Q_OBJECT
        Q_INTERFACES(Plugin)
        Q_INTERFACES(IDocumentController)

    public:
        PdfController();
        ~PdfController();

        //! Return the name of the plugin.
        /*!
          \return the variable name
        */
        const QString        pluginName() const;

        //! Return the version of the plugin
        /*!
          \return the variable version
        */
        const QString        pluginVersion() const;

         //! Indicates which type is supported by the plugin.
                /*!
                    \return A string matching a specific type of page object.
                */
        const QString   getSupportedType() const;

        QWidget*        createDocumentWidget(ILessonDocument *document);
        QWidget         *editDocument(QFile *metadata, ILessonDocument *);

     private slots:
        void            dl();
        void            reload();

     private:
        QLabel          *label;
        FileData        *data;
        QString         supportedType;
        IPdfRendering   *pdf;
        QRectF          *rect;
        int             page;
};

#endif /* __PDF_CONTROLLER_H__ */
