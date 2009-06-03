#ifndef COURSEWIDGET_H
#define COURSEWIDGET_H
#include <QFrame>
#include <QWidget>
#include <QTreeWidget>

class CourseWidget : public QFrame
{
    public:
CourseWidget();
~CourseWidget();
public slots:
    void explorer();
    void ViewLesson();
    private:
    QWidget *fenetre;
    QTreeWidget *tree;
};
#endif // COURSEWIDGET_H
