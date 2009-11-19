#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QAbstractButton>
#include <QSettings>
#include <QCompleter>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QScrollArea>
#include "../../../Common/Defines.h"
namespace Ui
{
    class MainWindowClass;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindowClass *ui;
    void writesettings();
    void extract_files();
    QSettings *Gsettings;
    QCompleter *completer;
    QCompleter *completer2;
    QWidget *checkboxes;
    QVBoxLayout* area;
QVBoxLayout *vlayo;
QFrame* frame;

//protected:
//    void keyPressEvent(QKeyEvent *e);


private slots:
    void on_buttonBox_2_clicked(QAbstractButton* button);
    void on_buttonBox_clicked(QAbstractButton* button);
    void on_lineEdit_16_textChanged(QString );
    void on_lineEdit_10_textChanged(QString );
    void on_pushButton_4_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
