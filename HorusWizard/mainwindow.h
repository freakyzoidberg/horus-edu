#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
 #include <QFile>
#include <QFileInfo>
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
public slots:
    void done();
    void InstallServer();
    void InstallClient();



private:
    Ui::MainWindowClass *ui;
    qint64 written;
};

#endif // MAINWINDOW_H
