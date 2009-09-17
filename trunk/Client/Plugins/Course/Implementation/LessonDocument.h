#ifndef LESSONDOCUMENT_H
#define LESSONDOCUMENT_H

#include <QObject>

#include "../../LessonManager/ILessonDocument.h"

class LessonDocument : public ILessonDocument
{
    Q_OBJECT

public:
	LessonDocument(QObject *parent, int id, QString title, QString type, QString content, QHash<QString, QVariant> parameters);
	QVariant data(int column, int role) const;
    QHash<QString, QVariant> &getParameters();
    void setContent(QString content);
	void setId(int id);
	int	 getId();
    QString getContent() const;
    QString getType() const;
    void setType(QString type);

private:
    QHash<QString, QVariant> parameters;
    QString	content;
    QString type;
	int		_id;
};

#endif // LESSONDOCUMENT_H
