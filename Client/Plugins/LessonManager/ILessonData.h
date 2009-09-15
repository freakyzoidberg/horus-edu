#ifndef ILESSONDATA_H
#define ILESSONDATA_H

#include <QObject>

class ILessonData : public QObject
{
    Q_OBJECT

public:
    ILessonData(QObject *parent) : QObject(parent) {}
    virtual ~ILessonData() {}

    virtual QVariant data(int column, int role = Qt::DisplayRole) const = 0;

    const QString& getTitle() { return _title; }
    void setTitle(const QString& title) { _title = title; }

 private:
    QString _title;
};

#endif // ILESSONDATA_H
