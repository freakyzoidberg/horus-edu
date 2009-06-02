#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    if (ui->pushButton->text() == "Reset")
    {
            ui->pushButton->setText("Check");
            ui->label_2->setText("");
            ui->pushButton_4->setEnabled(false);
             ui->lineEdit->setReadOnly(false);
             ui->lineEdit_2->setReadOnly(false);
             ui->lineEdit_3->setReadOnly(false);
             ui->lineEdit_4->setReadOnly(false);
             ui->lineEdit_9->setReadOnly(false);
                ui->lineEdit_11->setReadOnly(false);
                ui->lineEdit_14->setReadOnly(false);
                ui->lineEdit_15->setReadOnly(false);

    }
    else
    {
    QString host = ui->lineEdit->text();
    QString port = ui->lineEdit_2->text();
    QString dbname = ui->lineEdit_3->text();
    QString login = ui->lineEdit_4->text();
    QString pass = ui->lineEdit_9->text();
    bool ok;
     QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");

        db.setHostName(host);
        db.setDatabaseName(dbname);
        db.setUserName(login);
        db.setPassword(pass);
        db.setPort(port.toInt(&ok));
        QPalette Pal(ui->label_2->palette());
        if ((!db.open()) || (ui->lineEdit_14->text().size() == 0) || (ui->lineEdit_15->text().size() == 0) || (ui->lineEdit_15->text() != ui->lineEdit_11->text()))
             {
            Pal.setColor(QPalette::Foreground, Qt::red);
                ui->label_2->setPalette(Pal);

            ui->label_2->setText("Error");
            ui->pushButton_4->setEnabled(false);
            //ui->lineEdit_2->setForegroundRole(QPalette::Foreground green
            //qDebug() << db.lastError();
        }
        else
        {
            Pal.setColor(QPalette::Foreground, Qt::green);
            ui->label_2->setPalette(Pal);
             ui->label_2->setText("Connected");
             ui->lineEdit->setReadOnly(true);
             ui->lineEdit_2->setReadOnly(true);
             ui->lineEdit_3->setReadOnly(true);
             ui->lineEdit_4->setReadOnly(true);
             ui->lineEdit_9->setReadOnly(true);             
            ui->lineEdit_11->setReadOnly(true);
            ui->lineEdit_14->setReadOnly(true);
            ui->lineEdit_15->setReadOnly(true);
            ui->pushButton_4->setEnabled(true);
            ui->pushButton->setText("Reset");
             db.close();
         }

    }
}
