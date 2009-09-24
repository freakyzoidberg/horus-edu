#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QCryptographicHash>
#include <QDir>
#include <QCheckBox>
 #include <QLayout>
 #include <QCompleter>
 #include <QDirModel>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
        QVBoxLayout *mylayout = new QVBoxLayout();

        ui->scrollArea->setLayout(mylayout);
#ifdef WIN32
        ui->lineEdit_16->setText("C:\\Program Files\\Horus\\");
#else
        ui->lineEdit_16->setText("/opt/Horus/Horus-server/");
#endif
        on_lineEdit_16_textChanged("");
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
    QString driver;
if (ui->sqldriver->currentText() == "MySQL")
    driver = "QMYSQL";
else if (ui->sqldriver->currentText() == "PostgreSQL")
    driver = "QPSQL";
else
    driver = "QMYSQL";
        QSqlDatabase db = QSqlDatabase::addDatabase(driver);



        db.setHostName(host);
        db.setDatabaseName(dbname);
        db.setUserName(login);
        db.setPassword(pass);
        db.setPort(port.toInt(&ok));
        QPalette Pal(ui->label_2->palette());
        if (!db.open())
        {
            Pal.setColor(QPalette::Foreground, Qt::red);
                ui->label_2->setPalette(Pal);

            //ui->label_2->setText("Error at DB connection");
                ui->label_2->setText(db.lastError().text());
            ui->pushButton_4->setEnabled(false);
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
            ui->pushButton_4->setEnabled(false);
            if ((ui->lineEdit_14->text().size() > 0) &&  (ui->lineEdit_15->text() == ui->lineEdit_11->text()) && (ui->lineEdit_15->text().size() > 0))
             {
                ui->pushButton_4->setEnabled(true);
            }
            else if ((ui->lineEdit_14->text().size() > 0))
            {
                Pal.setColor(QPalette::Foreground, Qt::red);
                ui->label_2->setPalette(Pal);
                ui->label_2->setText("Error Missing default Admins credentials");
            //ui->lineEdit_2->setForegroundRole(QPalette::Foreground green
            //qDebug() << db.lastError();
            }

            ui->pushButton->setText("Reset");
             db.close();
         }

    }
}

void MainWindow::on_pushButton_4_clicked()
{
    QString host = ui->lineEdit->text();
    QString port = ui->lineEdit_2->text();
    QString dbname = ui->lineEdit_3->text();
    QString login = ui->lineEdit_4->text();
    QString pass = ui->lineEdit_9->text();
    bool ok;

    QString driver;
if (ui->sqldriver->currentText() == "MySQL")
    driver = "QMYSQL";
else if (ui->sqldriver->currentText() == "PostgreSQL")
    driver = "QPSQL";
else
    driver = "QMYSQL";
        QSqlDatabase db = QSqlDatabase::addDatabase(driver);

	db.setHostName(host);
	db.setDatabaseName(dbname);
	db.setUserName(login);
	db.setPassword(pass);
	db.setPort(port.toInt(&ok));
	if (db.open())
	{
            QFile dump;

if (ui->sqldriver->currentText() == "MySQL")
    dump.setFileName(":/dump-mysql.sql");
else if (ui->sqldriver->currentText() == "PostgreSQL")
    dump.setFileName(":/dump-pgsql.sql");
else
    dump.setFileName(":/dump-pgsql.sql");


		dump.open(QIODevice::ReadOnly);
		const QByteArray content = dump.readAll();
		bool ok = true;
		QSqlQuery query(db);
		foreach (QByteArray line, content.split(';'))
		{
			line = line.trimmed();
			if (line.isEmpty())
				continue;

			if ( ! query.exec(line))
			{
				qDebug() << query.lastError().text();
				ok = false;
			}
		}

 if (ui->sqldriver->currentText() == "MySQL")
                     query.prepare("INSERT INTO `users` (`enabled`, `login`, `level`, `password`, `surname`, `name`, `id_tree`) VALUES "\
                                                                                  "(        1,       ?,       0,          ?,  'Father',  'God',  0)");
 else if (ui->sqldriver->currentText() == "PostgreSQL")
    query.prepare("INSERT INTO users (id, enabled, login, level, password, surname, name, id_tree) VALUES (       1, 1,       ?,       0,          ?,  'Father',  'God',  0)");
else
query.prepare("INSERT INTO 'users' ('enabled', 'login', 'level', 'password', 'surname', 'name', 'id_tree') VALUES (        1,       ?,       0,          ?,  'Father',  'God',  0)");


		query.addBindValue(ui->lineEdit_14->text());
		query.addBindValue(QCryptographicHash::hash(QVariant(ui->lineEdit_15->text()).toByteArray(), QCryptographicHash::Sha1).toHex());
		if ( ! query.exec())
		{
			qDebug() << query.lastError().text();
			ok = false;
		}

		QPalette Pal(ui->label_2->palette());
		if (ok)
		{
			Pal.setColor(QPalette::Foreground, Qt::green);
			ui->label_2->setPalette(Pal);
			ui->label_2->setText("Database deployed !");
		}
		else
		{
			Pal.setColor(QPalette::Foreground, Qt::red);
			ui->label_2->setPalette(Pal);
			ui->label_2->setText("Error while deploying. See debug messages.");
		}
	}
}

void MainWindow::on_lineEdit_16_textChanged(QString )
{
int found;

QLayoutItem *child;
while ((child = ui->scrollArea->layout()->takeAt(0)) != 0) {
        child->widget()->deleteLater();
        delete child;
}
QPalette Pal(ui->label_9->palette());
QDir dir(ui->lineEdit_16->text()+"/Plugins/");
if (dir.exists())
     {
QDir dir3(ui->lineEdit_16->text()+"/ssl/");
    if (dir3.exists())
        {
        Pal.setColor(QPalette::Foreground, Qt::green);
                ui->label_9->setPalette(Pal);
        }
    else
        {
        Pal.setColor(QPalette::Foreground, Qt::red);
                ui->label_9->setPalette(Pal);
        }
            dir.setFilter(QDir::Dirs| QDir::NoDotAndDotDot);
            QFileInfoList list = dir.entryInfoList();
            for (int i = 0; i < list.size(); ++i)
             {
               QFileInfo fileInfo = list.at(i);

                QDir dirfils(fileInfo.absoluteFilePath());
                found = 0;
                if (dirfils.exists())
                    {
                    dirfils.setFilter(QDir::Files| QDir::NoDotAndDotDot);
                    QFileInfoList listfils = dirfils.entryInfoList();

                    for (int j = 0; ((j < listfils.size()) && (found == 0)); ++j)
                        {
                        QFileInfo filefilsInfo = listfils.at(j);
                            if ((filefilsInfo.fileName().endsWith(".so") && filefilsInfo.fileName().count(".so") == 1) || (filefilsInfo.fileName().endsWith(".dll") && filefilsInfo.fileName().count(".dll") == 1))
                            {
                                QCheckBox * pCheckBox = new QCheckBox
                                    (fileInfo.fileName()+"/"+filefilsInfo.fileName());
                                 ui->scrollArea->layout()->addWidget(pCheckBox);
                                 //ui->scrollAreaWidgetContents->repaint();
                                 found = 1;
                             }
                        }
                    }
             }
        }
    else
    {

        Pal.setColor(QPalette::Foreground, Qt::red);
                ui->label_9->setPalette(Pal);

       // QCompleter *completer = new QCompleter(this);
        completer = new QCompleter(this);
         completer->setWrapAround(true);
        completer->setCompletionMode(QCompleter::PopupCompletion);
        completer->setModel(new QDirModel(completer));

        ui->lineEdit_16->setCompleter(completer);
    }
}


void MainWindow::writesettings()
{
    QString host = ui->lineEdit->text();
    QString port = ui->lineEdit_2->text();
    QString dbname = ui->lineEdit_3->text();
    QString login = ui->lineEdit_4->text();
    QString pass = ui->lineEdit_9->text();
    QString servport = ui->lineEdit_13->text();
    QString path = ui->lineEdit_16->text();


    QString driver;
    if (ui->sqldriver->currentText() == "MySQL")
    driver = "QMYSQL";
else if (ui->sqldriver->currentText() == "PostgreSQL")
    driver = "QPSQL";
else
    driver = "QMYSQL";

    if (this->Gsettings.status() == 0)
    {
    this->Gsettings.clear();
    this->Gsettings.beginGroup("SQL");
    this->Gsettings.setValue("SQL_DRIVER", (driver));
    this->Gsettings.setValue("SQL_HOSTNAME", (host));
    this->Gsettings.setValue("SQL_DBNAME", (dbname));
    this->Gsettings.setValue("SQL_USERNAME", (login));
    this->Gsettings.setValue("SQL_PASSWD", (pass));
    this->Gsettings.setValue("SQL_PORT", (port));
    this->Gsettings.endGroup();
    this->Gsettings.beginGroup("SERVER");
    this->Gsettings.setValue("SRV_PORT", (servport));
    this->Gsettings.endGroup();
    this->Gsettings.beginGroup("SETTINGS");
    this->Gsettings.setValue("Version", "5");
    this->Gsettings.setValue("PluginsBase", ( path+"/Plugins/"));
    this->Gsettings.setValue("SoftFullPath", (path+"/"));
    this->Gsettings.endGroup();
    this->Gsettings.beginGroup("PLUGINS");;
    qDebug() << this->Gsettings.fileName();
    for (int i = 0; (i < ui->scrollArea->layout()->count()); i++)
    {

        if (((QCheckBox *)(ui->scrollArea->layout()->itemAt(i)->widget()))->isChecked())
        {

        this->Gsettings.setValue(((QCheckBox *)(ui->scrollArea->layout()->itemAt(i)->widget()))->text().split("/").first(),

                                 #ifdef WIN32
                                (((QCheckBox *)(ui->scrollArea->layout()->itemAt(i)->widget()))->text()));
                                 #else
                                (((QCheckBox *)(ui->scrollArea->layout()->itemAt(i)->widget()))->text()));
                                #endif
        }

    }
    this->Gsettings.endGroup();
    this->Gsettings.sync();

                    QPalette Pal(ui->label_6->palette());
                    Pal.setColor(QPalette::Foreground, Qt::green);
                   ui->label_6->setPalette(Pal);
                   ui->label_6->setText("Configuration saved");
    }

}

void MainWindow::on_buttonBox_clicked(QAbstractButton* button)
{
        if (this->ui->buttonBox->buttonRole(button) == QDialogButtonBox::AcceptRole)
	    writesettings();
}

void MainWindow::on_buttonBox_2_clicked(QAbstractButton* button)
{
	if (this->ui->buttonBox_2->buttonRole(button) == QDialogButtonBox::RejectRole)
	    exit(0);
}

    /*
void MainWindow::keyPressEvent(QKeyEvent *e)
 {
     if (completer && completer->popup()->isVisible()) {
         // The following keys are forwarded by the completer to the widget
        switch (e->key()) {
        case Qt::Key_Enter:
        case Qt::Key_Return:
        case Qt::Key_Escape:
        case Qt::Key_Tab:
        case Qt::Key_Backtab:
        case Qt::Key_Down:
        case Qt::Key_Up:
             e->ignore();
             return; // let the completer do default behavior
        default:
            break;
        }
     }
 }
     */
