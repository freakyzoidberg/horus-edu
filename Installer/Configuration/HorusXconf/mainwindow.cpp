#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtSql>
#include <QCryptographicHash>
#include <QDir>
#include <QCheckBox>
 #include <QLayout>
 #include <QCompleter>
 #include <QDirModel>
#include <QWidget>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <Qt>
#include <QProgressBar>
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindowClass)
{
    ui->setupUi(this);
	this->Gsettings = new QSettings(QSettings::SystemScope, ORGANIZATION_NAME, SERVER_NAME);
        checkboxes = new QWidget;

        //area = new QScrollArea(0);


        area = new QVBoxLayout;
        QSizePolicy policy;
        area->setSpacing(10);
        //ui->scrollArea->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
        //ui->scrollArea->setWidgetResizable(true);
        checkboxes->setLayout(area);
        ui->scrollArea->setWidget(checkboxes); // A

    //      QVBoxLayout *mylayout = new QVBoxLayout();

//        ui->scrollArea->setLayout(mylayout);
#ifdef WIN32
        ui->lineEdit_16->setText("C:\\Program Files\\Horus\\");
#else
        ui->lineEdit_16->setText("/opt/Horus/Horus-server/");
#endif
        on_lineEdit_16_textChanged("");

        completer2 = new QCompleter(this);
         completer2->setWrapAround(true);
        completer2->setCompletionMode(QCompleter::PopupCompletion);
        completer2->setModel(new QDirModel(completer2));
        ui->lineEdit_10->setCompleter(completer2);

                        completer = new QCompleter(this);
         completer->setWrapAround(true);
        completer->setCompletionMode(QCompleter::PopupCompletion);
        completer->setModel(new QDirModel(completer));
        ui->lineEdit_16->setCompleter(completer);



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
query.prepare("INSERT INTO user (`enabled`, `login`, `level`, `password`, `surname`, `name`) VALUES (        1,       ?,       0,          ?,  'Father',  'God')");
 else if (ui->sqldriver->currentText() == "PostgreSQL")
	query.prepare("INSERT INTO user (id, enabled, login, level, password, surname, name) VALUES (       1, 1,       ?,       0,          ?,  'Father',  'God')");
else
query.prepare("INSERT INTO 'user' ('enabled', 'login', 'level', 'password', 'surname', 'name') VALUES (        1,       ?,       0,          ?,  'Father',  'God')");


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


while ((child = ui->scrollArea->widget()->layout()->takeAt(0)) != 0) {
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
                                QCheckBox *pCheckBox = new QCheckBox
                                    (fileInfo.fileName()+"/"+filefilsInfo.fileName());



                                area->addWidget(pCheckBox);
                                ui->scrollArea->updateGeometry();
                                ui->scrollArea->adjustSize();
                                ui->scrollArea->repaint();
                                //ui->scrollArea->layout()->addWidget(pCheckBox);
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

    QString mailhost = ui->lineEdit_5->text();
    QString maildmn = ui->lineEdit_6->text();
    QString mailport = ui->lineEdit_7->text();

    QString mailssl = (ui->checkBox->isChecked() ? "y" : "n");
    QString maillogin = (ui->checkBox_2->isChecked() ? "y" : "n");
    QString servfileport = ui->lineEdit_8->text();
    QString servfilepath = ui->lineEdit_10->text();

    QString driver;
    if (ui->sqldriver->currentText() == "MySQL")
    driver = "QMYSQL";
else if (ui->sqldriver->currentText() == "PostgreSQL")
    driver = "QPSQL";
else
    driver = "QMYSQL";

    if (this->Gsettings->status() == 0)
    {
    this->Gsettings->clear();
    this->Gsettings->beginGroup("SQL");
    this->Gsettings->setValue("SQL_DRIVER", (driver));
    this->Gsettings->setValue("SQL_HOSTNAME", (host));
    this->Gsettings->setValue("SQL_DBNAME", (dbname));
    this->Gsettings->setValue("SQL_USERNAME", (login));
    this->Gsettings->setValue("SQL_PASSWD", (pass));
    this->Gsettings->setValue("SQL_PORT", (port));
    this->Gsettings->endGroup();
    this->Gsettings->beginGroup("SERVER");
    this->Gsettings->setValue("SRV_PORT", (servport));
    this->Gsettings->setValue("SRV_FILE_TRANSFERT_PORT", (servfileport));
    this->Gsettings->endGroup();
    this->Gsettings->beginGroup("SETTINGS");
    this->Gsettings->setValue("Version", "6");
    this->Gsettings->setValue("PluginsBase", ( path+"/Plugins/"));
    this->Gsettings->setValue("SoftFullPath", (path+"/"));
    this->Gsettings->setValue("FilesDirectory",servfilepath);
    this->Gsettings->endGroup();
    this->Gsettings->beginGroup("PLUGINS");;
    qDebug() << this->Gsettings->fileName();
    for (int i = 0; (i < ui->scrollArea->widget()->layout()->count()); i++)
    {

        if (((QCheckBox *)(ui->scrollArea->widget()->layout()->itemAt(i)->widget()))->isChecked())
        {

        this->Gsettings->setValue(((QCheckBox *)(ui->scrollArea->widget()->layout()->itemAt(i)->widget()))->text().split("/").first(),

                                 #ifdef WIN32
                                (((QCheckBox *)(ui->scrollArea->widget()->layout()->itemAt(i)->widget()))->text()));
                                 #else
                                (((QCheckBox *)(ui->scrollArea->widget()->layout()->itemAt(i)->widget()))->text()));
                                #endif
        }

    }
    this->Gsettings->endGroup();
    this->Gsettings->beginGroup("MAIL");
    this->Gsettings->setValue("MAIL_HOSTNAME", (mailhost));
    this->Gsettings->setValue("MAIL_DOMAIN", (maildmn));
    this->Gsettings->setValue("MAIL_PORT", (mailport));
    this->Gsettings->setValue("MAIL_SSLTLS", (mailssl));
    this->Gsettings->setValue("MAIL_LOGIN", (maillogin));
    this->Gsettings->endGroup();

    this->Gsettings->sync();


    if (this->Gsettings->status() == 0)
    {
                    QPalette Pal(ui->label_6->palette());
                    Pal.setColor(QPalette::Foreground, Qt::green);
                   ui->label_6->setPalette(Pal);
                   ui->label_6->setText("Configuration saved");
               }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("need sudo");
        msgBox.exec();
    }

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



void MainWindow::on_lineEdit_10_textChanged(QString )
{
int found;

QLayoutItem *child;
QPalette Pal(ui->label_9->palette());


       // QCompleter *completer = new QCompleter(this);
}


void MainWindow::on_pushButton_2_clicked()
{
    extract_files();
}

void MainWindow::extract_files()
{

//vlayo  = new QVBoxLayout();
//frame=new QFrame(this,Qt::SplashScreen);
//frame->setLayout(vlayo);
//frame->setFrameShape(QFrame::NoFrame);
  //frame->setMinimumWidth(300);
  //frame->setMinimumHeight(100);
//frame->setAttribute(Qt::WA_TranslucentBackground);


  //frame->setAutoFillBackground(true);

    //frame->show();





  //QColor semi_red_color(255,0,0,127);



















    int totalsize = 0;
     QDir rhdl = QDir(":/Files/Files/");
     rhdl.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
     rhdl.setSorting(QDir::Size | QDir::Reversed);
     QFileInfoList list = rhdl.entryInfoList();


     for (int i = 0; i < list.size(); ++i) {
         QFileInfo fileInfo = list.at(i);
         qDebug() << qPrintable(QString("%1 %2").arg(fileInfo.size(), 10)
                                                 .arg(fileInfo.fileName()));
         totalsize += fileInfo.size();

     }


QString result;
bool ok = false;


  QPalette Pal(ui->label_6->palette());




//QLabel *finishf = new QLabel("Error");
     for (int i = 0; i < list.size(); ++i) {
         QFileInfo fileInfo = list.at(i);
         QFile file(fileInfo.absoluteFilePath());
         QDir mydir;
         qDebug() << fileInfo.absoluteFilePath();
		 mydir.mkpath(ui->lineEdit_10->text()+QDir::separator());
           if (file.copy(ui->lineEdit_10->text()+QDir::separator()+fileInfo.fileName()))
            {
            qDebug() << "ok";
               ok = true;
               Pal.setColor(QPalette::Foreground, Qt::green);
               ui->label_6->setPalette(Pal);
                                ui->label_6->setText("Finished Copying Files");

               //finishf->setText("Finished Copying Files");

           }
           else
           {
               qDebug() << "ko [" << ui->lineEdit_10->text()+QDir::separator()+fileInfo.fileName() << "]";
               Pal.setColor(QPalette::Foreground, Qt::red);
               ui->label_6->setPalette(Pal);
                 ui->label_6->setText("Error while copying");

                //finishf->setText("Error while copying");

           }

    }


//QPalette Pal(finishf->palette());

  //                         Pal.setColor(QPalette::Foreground, Qt::white);

//                            Pal.setColor(QPalette::Foreground, Qt::red);
    //    finishf->setPalette(Pal);
        //vlayo->addWidget(finishf);
        //vlayo->activate();

}
