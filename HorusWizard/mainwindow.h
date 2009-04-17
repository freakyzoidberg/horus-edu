#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QFile>
#include <QFileInfo>
 //#include <QXmlStreamReader>
#include <QMap>
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
    void addvecserver(QString name, QString folder);
    void addvecclient(QString name, QString folder);


private:
    Ui::MainWindowClass *ui;
    qint64 written;

    typedef struct var {
    QString name;
    QString folder;
    } contentstruct;


    QVector<contentstruct> vecclient;
    QVector<contentstruct> vecserver;
};

#endif // MAINWINDOW_H
