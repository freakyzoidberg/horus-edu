#ifndef LESSON_H
#define LESSON_H

#include <QMap>
#include <QString>
#include <QIcon>

class IController;

class LElement
{
public:
    LElement(LElement *parent);

    LElement    *getParent();
    const QString&  getTitle() const;
    void            setTitle(const QString& title);

private:
    LElement    *parent;
    QString     title;
};

class LSection : public LElement
{
public:    
    LSection(LElement *parent);
    ~LSection() {}

    QList<LElement *>&       getElementsP();
    const QList<LElement *>& getElements() const;

private:
    QList<LElement *>    elements;
};

class LObject : public LElement
{
public:
    LObject(LElement *parent);
    const QString&      getType() const;
    void                setType(const QString& type);
    QWidget*            getWidget();
    void                setWidget(QWidget *widget);
    const QList<quint32>&    getRequiredFiles() const;
    void                addRequiredFile(quint32 id);
    const QString&      getParameters() const;
    void                setParameters(const QString& params);
    const QString&      getContent() const;
    void                setContent(const QString& content);
    IController*        getController();
    void                setController(IController *ctrl);

private:
    IController         *ctrl;
    QPointF             position;
    QSizeF              size;
    QString             type;
    QString             params;
    QString             content;
    QWidget*            widget;
    QList<quint32>      requiredFiles;
};

class Lesson
{
public:
    Lesson();
    ~Lesson() {}
    const QString&          getTitle() const;
    void                    setTitle(const QString& title);
    const QList<LElement *>&  getElements() const;
    void               addElement(LElement *element);

private:
    QList<LElement *>  elements;
    QString  title;

    static QIcon    lessonIcon;
    static QIcon    sectionIcon;
    static QIcon    pageIcon;
};

#endif // LESSON_H
