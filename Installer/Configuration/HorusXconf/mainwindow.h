#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
 #include <QAbstractButton>
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

private slots:
    void on_lineEdit_16_textChanged(QString );
    void on_pushButton_4_clicked();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
