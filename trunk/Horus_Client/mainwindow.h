#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QMessageBox>

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
    QLabel *hostLabel;
     QLabel *portLabel;
     QLineEdit *hostLineEdit;
     QLineEdit *portLineEdit;
     QLabel *statusLabel;
     QPushButton *getFortuneButton;
     QPushButton *quitButton;
     QDialogButtonBox *buttonBox;

     QTcpSocket *tcpSocket;
     QString currentFortune;
     quint16 blockSize;
private slots:
    void on_ConnectButton_clicked();
    void requestNewFortune();
    void readFortune();
    void displayError(QAbstractSocket::SocketError socketError);
    void enableGetFortuneButton();

};

#endif // MAINWINDOW_H
