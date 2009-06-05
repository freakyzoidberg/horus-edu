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

void MainWindow::on_pushButton_4_clicked()
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
        if (db.open())
        {
            QSqlQuery *query1 = new QSqlQuery(db);
            query1->prepare("SET SQL_MODE='NO_AUTO_VALUE_ON_ZERO';");
            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}
            query1->prepare("DROP TABLE IF EXISTS `files`;");
            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}
            query1->prepare("CREATE TABLE IF NOT EXISTS `files` (" \
                            "`id` int(11) NOT NULL auto_increment," \
                            "`name` varchar(255) NOT NULL," \
                            "`size` int(11) NOT NULL," \
                            "`id_tree` int(11) NOT NULL," \
                            "`id_owner` int(11) NOT NULL," \
                            "`ctime` timestamp NOT NULL default '0000-00-00 00:00:00'," \
                            "`mtime` timestamp NOT NULL default '0000-00-00 00:00:00'," \
                            "`hash_sha1` varchar(40) NOT NULL," \
                            "PRIMARY KEY  (`id`)," \
                            "KEY `id_ower` (`id_owner`)," \
                            "KEY `id_tree` (`id_tree`)" \
                            ") ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=4 ;");
            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}
            /*
            query1->prepare("INSERT INTO `files` (`id`, `name`, `size`, `id_tree`, `id_owner`, `ctime`, `mtime`, `hash_sha1`) VALUES" \
                            "(1, 'test.txt', 0, 0, 3, '2009-06-01 07:15:40', '2009-06-01 07:15:40', '')," \
                            "(2, 'test.txt', 0, 0, 3, '2009-06-01 17:38:29', '2009-06-01 17:38:29', '')," \
                            "(3, 'test.txt', 0, 0, 3, '2009-06-01 17:39:57', '2009-06-01 17:39:57', '');");
            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}
            */
            query1->prepare("DROP TABLE IF EXISTS `settings`;");
            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}
            query1->prepare("CREATE TABLE IF NOT EXISTS `settings` (" \
                            "`user` int(11) NOT NULL," \
                            "`plugin` varchar(255) NOT NULL," \
                            "`scope` int(1) NOT NULL," \
                            "`value` blob," \
                            "KEY `user` (`user`)," \
                            "KEY `module` (`plugin`)," \
                            "KEY `scope` (`scope`)" \
                            ") ENGINE=MyISAM DEFAULT CHARSET=utf8;");
            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}
            query1->prepare("INSERT INTO `settings` (`user`, `plugin`, `scope`, `value`) VALUES" \
                            "(3, 'test', 0, 0x0000000a00000000080074006500730074)," \
                            "(4, '', 0, 0x0000000a0000000000);");
            query1->prepare("DROP TABLE IF EXISTS `tree`;");
            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}
            query1->prepare("CREATE TABLE IF NOT EXISTS `tree` (" \
                            "`id` int(11) NOT NULL auto_increment," \
                            "`typeofnode` varchar(42) NOT NULL," \
                            "`name` varchar(128) NOT NULL," \
                            "`user_ref` int(11) NOT NULL default '0'," \
                            "`id_parent` int(11) NOT NULL default '0'," \
                            "PRIMARY KEY  (`id`)" \
                            ") ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=237 ;");
            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}
            query1->prepare("INSERT INTO `tree` (`id`, `typeofnode`, `name`, `user_ref`, `id_parent`) VALUES" \
                            "(1, '', 'School', 1, 0)," \
                            "(2, '', 'Prof', 1, 1)," \
                            "(3, '', 'Promos', 1, 1)");
            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}
            query1->prepare("DROP TABLE IF EXISTS `users`;");
            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}
            query1->prepare("CREATE TABLE IF NOT EXISTS `users` (" \
                            "`id` int(11) NOT NULL auto_increment," \
                            "`enabled` tinyint(1) NOT NULL default '1'," \
                            "`login` varchar(32) NOT NULL," \
                            "`level` tinyint(1) NOT NULL," \
                            "`password` char(40) NOT NULL," \
                            "`session_key` char(64) default NULL," \
                            "`session_end` timestamp NULL default NULL," \
                            "`last_login` timestamp NULL default NULL," \
                            "`address` varchar(255) NOT NULL," \
                            "`phone` varchar(32) NOT NULL," \
                            "`country` varchar(32) NOT NULL," \
                            "`language` varchar(2) NOT NULL," \
                            "PRIMARY KEY  (`id`)," \
                            "KEY `level` (`level`)," \
                            "KEY `login` (`login`)," \
                            "KEY `enabled` (`enabled`)" \
                            ") ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=5 ;");
            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}
            query1->prepare("INSERT INTO `users` (`id`, `enabled`, `login`, `level`, `password`, `session_key`, `session_end`, `last_login`, `address`, `phone`, `country`, `language`) VALUES" \
                            "(1, 1, ?, 0, ?, NULL, '2009-06-01 17:40:22', '0000-00-00 00:00:00', '', '', '', '');");
            query1->addBindValue(ui->lineEdit_14->text());
            QVariant variantpass = QVariant(ui->lineEdit_15->text());
            query1->addBindValue(QVariant(QCryptographicHash::hash(variantpass.toByteArray(), QCryptographicHash::Sha1).toHex()).toString());
            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}
            query1->prepare("DROP TABLE IF EXISTS `user_has_group`;");
            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}
            query1->prepare("CREATE TABLE IF NOT EXISTS `user_has_group` (" \
                            "`id_user` int(11) NOT NULL," \
                            "`id_group` int(11) NOT NULL," \
                            "KEY `id_user` (`id_user`)" \
                            ") ENGINE=MyISAM DEFAULT CHARSET=utf8;");
            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}
            query1->prepare("INSERT INTO `user_has_group` (`id_user`, `id_group`) VALUES" \
                            "(1, 1);");
            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}

            QPalette Pal(ui->label_2->palette());
            if (query1->lastError().isValid() == false)
            {

                Pal.setColor(QPalette::Foreground, Qt::green);
                   ui->label_2->setPalette(Pal);
                   ui->label_2->setText("Database deployed !");

            }
            else
            {
                Pal.setColor(QPalette::Foreground, Qt::red);
                   ui->label_2->setPalette(Pal);
                   ui->label_2->setText("Error while deploying");
                    ui->label_2->setText(query1->lastError().text());
            }

            delete query1;
        }

}

void MainWindow::on_lineEdit_16_textChanged(QString )
{


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
                if (dirfils.exists())
                    {

                    dirfils.setFilter(QDir::Files| QDir::NoDotAndDotDot);
                    QFileInfoList listfils = dirfils.entryInfoList();
                    for (int j = 0; j < listfils.size(); ++j)
                        {

                        QFileInfo filefilsInfo = listfils.at(j);
                        #ifdef WIN32
                        if (("lib"+fileInfo.fileName() + ".dll") == (filefilsInfo.fileName()))
                        #else
                        if (("lib"+fileInfo.fileName() + ".so") == (filefilsInfo.fileName()))
                        #endif
                            {
                                QCheckBox * pCheckBox = new QCheckBox
                                    ((fileInfo.fileName()));

                                 ui->scrollArea->layout()->addWidget(pCheckBox);
                                 //ui->scrollAreaWidgetContents->repaint();
                             }
                        }
                    }
             }
        }
    else
    {

        Pal.setColor(QPalette::Foreground, Qt::red);
                ui->label_9->setPalette(Pal);

        QCompleter *completer = new QCompleter(this);
        completer->setCompletionMode(QCompleter::InlineCompletion);
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

    if (this->Gsettings.status() == 0)
    {
    this->Gsettings.clear();
    this->Gsettings.beginGroup("SQL");
    this->Gsettings.setValue("SQL_DRIVER", ("QMYSQL"));
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
    for (int i = 0; (i < ui->scrollArea->layout()->count()); i++)
    {

        if (((QCheckBox *)(ui->scrollArea->layout()->itemAt(i)->widget()))->isChecked())
        {

        this->Gsettings.setValue(((QCheckBox *)(ui->scrollArea->layout()->itemAt(i)->widget()))->text(),
                                (((QCheckBox *)(ui->scrollArea->layout()->itemAt(i)->widget()))->text()+"/lib"
                                 #ifdef WIN32
                                +(((QCheckBox *)(ui->scrollArea->layout()->itemAt(i)->widget()))->text()+".dll")));
                                 #else
                                +(((QCheckBox *)(ui->scrollArea->layout()->itemAt(i)->widget()))->text()+".so")));
                                #endif
        }

    }
    this->Gsettings.endGroup();
                    QPalette Pal(ui->label_6->palette());
                    Pal.setColor(QPalette::Foreground, Qt::green);
                   ui->label_6->setPalette(Pal);
                   ui->label_6->setText("Configuration saved");
    }

}

void MainWindow::on_buttonBox_clicked(QAbstractButton* button)
{

    writesettings();
}

void MainWindow::on_buttonBox_2_clicked(QAbstractButton* button)
{
    exit(0);
}
