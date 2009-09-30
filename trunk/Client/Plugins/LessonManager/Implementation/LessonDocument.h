#ifndef LESSONDOCUMENT_H
#define LESSONDOCUMENT_H

#include <QIcon>

#include "../ILessonDocument.h"

class LessonDocument : public ILessonDocument
{
    Q_OBJECT

public:
    LessonDocument(ILessonSection *parent);
    LessonDocument(ILesson *parent);

    QVariant data(int column, int role) const;

    QHash<QString, QVariant> &getParameters();
	void setId(int id);
	int getId();
    void setContent(QString content);
    QString getContent() const;
    QString getType() const;
    void setType(QString type);

private:
    QHash<QString, QVariant> parameters;
    QString 	content;
    QString     type;
	int			_id;
	static QIcon *icon;
};

#endif // LESSONDOCUMENT_H
