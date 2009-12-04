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
#include "ImageController.h"

#include <QLabel>
#include <QImage>
#include <QPixmap>
#include <QFileDialog>
#include <QPushButton>

const QString    ImageController::pluginName() const
{
    return ("imageController");
}

const QString    ImageController::pluginVersion() const
{
    return ("0.2");
}

const QString      ImageController::getSupportedType() const
{
    return ("image");
}

QWidget*            ImageController::createDocumentWidget(ILessonDocument *document)
{
        qDebug() << "doc:" << document;




    int fileId = 15;
    //fileId = document->getParameters().value("id").toInt();
    //fileId = document->getId();
    qDebug() << "file id:" << fileId;

   data = pluginManager->findPlugin<FileDataPlugin*>()->file(fileId);
    this->connect(data, SIGNAL(downloaded()), this, SLOT(dl()));

  //  if (document->getType() != this->getSupportedType())
    {
        qDebug() << "[Plugin ImageController] Type error:";
   //     qDebug() << "\tThe type of your IObject is" << document->getType();
        qDebug() << "\tThe controller ImageController handle " << this->getSupportedType() << " type.";
    }

    label = new QLabel("Loading image...");
    //if (data->isDownloaded())
       dl();
    qDebug() << "label geneted";
    return (label);
}

void        ImageController::dl()
{
    QString fileName;
    fileName = data->file()->fileName();
//fileName  = "/tmp/15";
    QImage  *image = new QImage(fileName);
    if (image->isNull())
    {
        qDebug() << "An error occured during image generation";
        return ;
    }
    QPixmap pix = QPixmap::fromImage(*image);
    label->setPixmap(pix);
    delete image;
}

void    ImageController::reload()
{
    QString fileName;
    fileName = data->file()->fileName();

    qDebug() << "Image name: " << fileName;
    QImage  *image = new QImage(fileName);
    if (image->isNull())
    {
        qDebug() << "An error occured during image generation";
        return ;
    }
    QPixmap pix = QPixmap::fromImage(*image);
    label->setPixmap(pix);
    //delete image;
}

QWidget        *ImageController::editDocument(QFile *, ILessonDocument *)
{
    return 0;
}

