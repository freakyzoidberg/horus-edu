#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QMessageBox>
#include <QSettings>
#include <QEvent>

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

protected:
     void closeEvent(QCloseEvent *event);

private:
    Ui::MainWindowClass *ui;
    void WriteSettings();
    void ReadSettings();

private slots:
    void on_ConnectButton_clicked();


};

#endif // MAINWINDOW_H
