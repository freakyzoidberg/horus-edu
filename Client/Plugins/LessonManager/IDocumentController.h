#ifndef IDOCUMENTCONTROLLER_H
#define IDOCUMENTCONTROLLER_H

#include <QObject>
#include <QWidget>

#include "ILessonDocument.h"
#include "../Course/IItems.h"

class IDocumentController
{
public:
    virtual ~IDocumentController() {}
    virtual const QString  getSupportedType() const = 0;
    virtual QWidget*  createDocumentWidget(IItems *parent, ILessonDocument *document) = 0;
    virtual void      resizeWidget(IItems *) = 0;
    virtual void      clean(IItems *) = 0;
};

Q_DECLARE_INTERFACE(IDocumentController, "net.horus.Client.Plugin.LessonManager.ControllerInterface/1.0");

#endif // IDOCUMENTCONTROLLER_H
