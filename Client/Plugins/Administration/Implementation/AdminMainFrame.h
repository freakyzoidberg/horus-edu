#ifndef ADMINMAINFRAME_H
#define ADMINMAINFRAME_H

#include <QtGui/QWidget>
#include <QListWidget>
#include <QStackedWidget>
#include <QtGui>
#include "StudentsPage.h"
#include "TeacherPage.h"
#include "RoomPage.h"

class AdminMainFrame : public QWidget
{
    Q_OBJECT

public:
    AdminMainFrame(QWidget *parent = 0);
    ~AdminMainFrame();
public slots:
    void changeFrame(QListWidgetItem *current, QListWidgetItem *previous);

private:
    void createIcons();

    QListWidget *contentsWidget;
    QStackedWidget *framesWidget;
};

#endif // ADMINMAINFRAME_H
