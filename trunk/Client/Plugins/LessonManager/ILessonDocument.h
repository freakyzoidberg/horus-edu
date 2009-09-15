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
	QHash<QVariant, QVariant> &getParameters();
	void setContent(QString content);
	QString getContent() const;

protected:
	QHash<QVariant, QVariant> parameters;
	QString	content;
};

#endif // ILESSONDOCUMENT_H
