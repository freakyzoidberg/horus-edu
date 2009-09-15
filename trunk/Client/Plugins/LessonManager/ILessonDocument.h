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
    ILessonDocument(ILesson *parent);
    ILessonDocument(ILessonSection *parent);
    virtual QHash<QString, QVariant> &getParameters() = 0;
    virtual void setContent(QString content) = 0;
    virtual QString getContent() const = 0;
    virtual QString getType() const = 0;
    virtual void setType(QString type) = 0;
};

#endif // ILESSONDOCUMENT_H
