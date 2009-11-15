#ifndef IDOCUMENTCONTROLLER_H
#define IDOCUMENTCONTROLLER_H

#include <QObject>
#include <QWidget>

#include "ILessonDocument.h"

class IDocumentController
{
public:
    virtual ~IDocumentController() {}
    virtual const QString  getSupportedType() const = 0;
    virtual QWidget*  createDocumentWidget(ILessonDocument *document) = 0;
    virtual QWidget   *editDocument(QFile *metadata, ILessonDocument *) = 0;
};

Q_DECLARE_INTERFACE(IDocumentController, "net.horus.Client.Plugin.LessonManager.ControllerInterface/1.0");

#endif // IDOCUMENTCONTROLLER_H
