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
        if (!db.open())
        {
            Pal.setColor(QPalette::Foreground, Qt::red);
                ui->label_2->setPalette(Pal);

            ui->label_2->setText("Error at DB connection");
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
            query1->prepare("CREATE TABLE IF NOT EXISTS `files` ("\
                            "`id` int(11) NOT NULL auto_increment,"\
                            "`name` varchar(255) NOT NULL,"\
                            "`mime` varchar(64) NOT NULL,"\
                            "`size` int(11) NOT NULL,"\
                            "`id_tree` int(11) NOT NULL,"\
                            "`id_owner` int(11) NOT NULL,"\
                            "`ctime` timestamp NOT NULL,"\
                            "`mtime` timestamp NOT NULL,"\
                            "`hash_sha1` varchar(40) NOT NULL,"\
                            "PRIMARY KEY  (`id`),"\
                            "KEY `id_ower` (`id_owner`),"\
                            "KEY `id_tree` (`id_tree`),"\
                            "KEY `mtime` (`mtime`)"\
                            ") ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=261 ;");
            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}

            query1->prepare("INSERT INTO `files` (`id`, `name`, `mime`, `size`, `id_tree`, `id_owner`, `ctime`, `mtime`, `hash_sha1`) VALUES"\
                    "(1, 'Histoire de la Chine', 'x-horus/x-lesson', 0, 241, 3, '2009-06-01 07:15:40', '2009-06-01 07:15:40', ''),"\
                    "(2, 'Histoire de costume', 'x-horus/x-lesson', 0, 241, 3, '2009-06-01 17:38:29', '2009-06-01 17:38:29', ''),"\
                    "(3, 'Tectonique des plaques', 'x-horus/x-lesson', 0, 243, 3, '2009-06-01 17:39:57', '2009-06-01 17:39:57', ''),"\
                    "(4, 'Reglement interieur.pdf', 'application/pdf', 0, 258, 4, '2009-06-06 11:44:20', '2009-06-06 11:44:20', ''),"\
		    "(42, 'Chine.pdf', 'application/pdf', 0, 3, 0, '0000-00-00 00:00:00', '0000-00-00 00:00:00', ''),"\
                    "(259, 'Decharge de responsabilitee.pdf', 'application/pdf', 0, 256, 0, '0000-00-00 00:00:00', '0000-00-00 00:00:00', ''),"\
                    "(260, 'Fiche descriptive.pdf', 'application/pdf', 0, 257, 0, '0000-00-00 00:00:00', '0000-00-00 00:00:00', '');");
            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}

            query1->prepare("DROP TABLE IF EXISTS `settings`;");
            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}
            query1->prepare("CREATE TABLE IF NOT EXISTS `settings` (" \
                            "`user` int(11) NOT NULL," \
                            "`plugin` varchar(255) NOT NULL," \
                            "`scope` int(1) NOT NULL," \
                            "`value` blob," \
                            "`mtime` timestamp NOT NULL,"\
                            "KEY `user` (`user`)," \
                            "KEY `module` (`plugin`)," \
                            "KEY `scope` (`scope`)," \
                            "KEY `mtime` (`mtime`)"\
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
                            "`mtime` timestamp NOT NULL,"\
                            "PRIMARY KEY  (`id`)," \
                            "KEY `mtime` (`mtime`)"\
                            ") ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=237 ;");
            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}
            query1->prepare("INSERT INTO `tree` (`id`, `typeofnode`, `name`, `user_ref`, `id_parent`) VALUES" \
                            "(1, 'CLASSES', 'Classes', 0, 0),"\
                            "(2, 'GROUP', 'Professeurs', 0, 0),"\
                            "(3, 'GRADE', '6eme', 0, 1),"\
"(237, 'GRADE', '5eme', 0, 1),"\
"(238, 'GRADE', '4eme', 0, 1),"\
"(239, 'GRADE', '3eme', 0, 1),"\
"(240, 'SUBJECT', 'Maths', 0, 3),"\
"(241, 'SUBJECT', 'Histoire', 0, 245),"\
"(242, 'SUBJECT', 'Physique', 0, 3),"\
"(243, 'SUBJECT', 'Geographie', 0, 245),"\
"(244, 'SUBJECT', 'Francais', 0, 3),"\
"(245, 'SUBJECT', 'Histoire / Geo', 0, 3),"\
"(0, 'ROOT', 'College Vauban', 0, 0),"\
"(247, 'GROUP', 'Eleves', 0, 0),"\
"(248, 'SUBJECT', 'SVT', 0, 237),"\
"(249, 'SUBJECT', 'Sport', 0, 237),"\
"(250, 'SUBJECT', 'Histoire / Geo', 0, 237),"\
"(251, 'SUBJECT', 'Francais', 0, 237),"\
"(252, 'SUBJECT', 'Histoire', 0, 250),"\
"(253, 'SUBJECT', 'Geographie', 0, 250),"\
"(254, 'GROUP', 'Administration', 0, 0),"\
"(255, 'GROUP', 'Groups', 0, 0),"\
"(256, 'GROUP', 'Sortie Pedagogiques', 0, 255),"\
"(257, 'GROUP', 'Citee de l''espace Avril 2009', 0, 256),"\
"(258, '', 'Documents generaux', 0, 0);");

            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}
            query1->prepare("DROP TABLE IF EXISTS `users`;");
            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}
            query1->prepare("CREATE TABLE IF NOT EXISTS `users` ("\
  "`id` int(11) NOT NULL auto_increment,"\
  "`enabled` tinyint(1) NOT NULL default '1',"\
  "`login` varchar(32) NOT NULL,"\
  "`level` tinyint(1) NOT NULL,"\
  "`password` char(40) NOT NULL,"\
  "`session_key` char(64) default NULL,"\
 " `session_end` timestamp NULL default NULL,"\
  "`last_login` timestamp NULL default NULL,"\
  "`surname` varchar(255) NOT NULL,"\
  "`name` varchar(255) NOT NULL,"\
  "`birth_date` timestamp NOT NULL default '0000-00-00 00:00:00',"\
  "`picture` blob NOT NULL,"\
  "`address` varchar(255) NOT NULL,"\
  "`phone` varchar(32) NOT NULL,"\
  "`country` varchar(32) NOT NULL,"\
  "`language` varchar(32) NOT NULL,"\
  "`id_tree` int(11) NOT NULL default '-1',"\
  "`mtime` timestamp NOT NULL,"\
  "PRIMARY KEY  (`id`),"\
  "KEY `level` (`level`),"\
 " KEY `login` (`login`),"\
 " KEY `enabled` (`enabled`),"\
 " KEY `mtime` (`mtime`)"\
") ENGINE=MyISAM  DEFAULT CHARSET=utf8 AUTO_INCREMENT=72 ;");



            query1->exec();
            if (query1->lastError().isValid()) {qDebug() << query1->lastError().text();}
            query1->prepare("INSERT INTO `users` (`id`, `enabled`, `login`, `level`, `password`, `session_key`, `session_end`, `last_login`, `surname`, `name`, `birth_date`, `picture`, `address`, `phone`, `country`, `language`, `id_tree`) VALUES "\
"(1, 1, ?, 0, ?, NULL, '0000-00-00 00:00:00', '0000-00-00 00:00:00', 'sdfsdfsdfsdf', 'sfdsfdsfdsfs', '2009-06-06 00:00:00', 0x76696465, 'sdfsdfsdf', 'dfsdfsdfsd', 'ssdfsdfsdfsdf', 'sd', 0),"\
"(4, 1, 'toto', 0, '0b9c2625dc21ef05f6ad4ddf47c5f203837aa32c', '8125320c6dadce4096e996fbd61df050b3ad8c54c6d8a338db26ff1dd8a1b9a2', '0000-00-00 00:00:00', '0000-00-00 00:00:00', 'sdfsdfsdfsdf', 'sfdsfdsfdsfs', '2009-06-06 00:00:00', 0x76696465, 'sdfsdfsdf', 'dfsdfsdfsd', 'ssdfsdfsdfsdf', 'sd', 0),"\
"(5, 1, 'val', 0, '39f69c278f46165447f30d10acf54277aaa3d5fc', '95a9c8d843545f2bb32939895520a71a4ef909755a759333744ace4137d3dff9', '0000-00-00 00:00:00', NULL, '', '', '0000-00-00 00:00:00', '', '90p9p09', '90p90', '90p90p', 'p0', 0),"\
"(6, 1, 'git', 0, '46f1a0bd5592a2f9244ca321b129902a06b53e03', '7afd803e5ca2ab50d427ea9964b415e27da9706fa611aed05fd8b477c2bb1e0c', '0000-00-00 00:00:00', NULL, '', '', '0000-00-00 00:00:00', '', '', '', '', '', 0),"\
"(7, 1, 'pierre', 4, 'pierre', NULL, '2009-06-05 20:36:00', NULL, '', '', '0000-00-00 00:00:00', '', '25, rue du cul', '0612542323', 'China', 'ch', 9),"\
"(32, 1, 'Valentin', 3, '39f69c278f46165447f30d10acf54277aaa3d5fc', NULL, '2009-06-06 15:23:06', NULL, 'Val', 'Entin', '2009-06-06 00:00:00', 0x76696465, '25, rue machin', '0123456789', 'Chine', 'Chongqinghua', 3),"\
"(54, 1, 'AbdEr', 3, 'c374c48b268e999230e206a5ed840004a9926148', 'd861660d2a81b6b11267b6baa2c8cb9cfce5dceeacef09b4b22d1d6160dec399', '2009-06-06 15:23:19', NULL, 'Abder', 'N', '2009-06-06 00:00:00', 0x76696465, '25, rue convention', '0142424242', 'France', 'Chinois', 3),"\
"(55, 1, 'Professeur', 2, 'e718ab41a00fe697cc1973be2104f5df4ed0b538', NULL, NULL, NULL, 'Jean', 'Luc', '2009-06-06 00:00:00', 0x76696465, '25, rue toto', '0123454565', 'France', 'Francais', 9),"\
"(64, 1, 'Mamadou', 3, 'd3febce94dd80a8620557479f409dc8a5594b510', NULL, NULL, NULL, 'Mamadou', 'Mamadou', '2009-06-06 00:00:00', 0x76696465, 'Mamadou', 'Mamadou', 'Mamadou', 'Mamadou', 0),"\
"(56, 1, 'Pierre', 2, '8ce4081e7eea6ace8332c7eb78415c57ec6ef2e3', NULL, NULL, NULL, 'Pierre', 'Pierre', '2009-06-06 00:00:00', 0x76696465, 'Pierre', 'Pierre', 'Pierre', 'Pierre', 9),"\
"(58, 1, 'Jerem', 2, '8d65594256bf4c57aa9778a78fc5b08e975f8040', NULL, NULL, NULL, 'Jerem', 'Jerem', '2009-06-06 00:00:00', 0x76696465, 'Jerem', 'Jerem', 'Jerem', 'Jerem', 9),"\
"(59, 1, 'Roumain', 2, 'e29a872af4795a630b7a7621ca4d99fcfb1151e7', NULL, NULL, NULL, 'Roumain', 'Roumain', '2009-06-06 00:00:00', 0x76696465, 'Roumain', 'Roumain', 'Roumain', 'Roumain', 9),"\
"(60, 1, 'adrien', 2, '4d10829f147c13c63c4579f5297a87efba1143a3', NULL, NULL, NULL, 'adrien', 'adrien', '2009-06-06 00:00:00', 0x76696465, 'adrien', 'adrien', 'adrien', 'adrien', 9),"\
"(61, 1, 'gildas', 2, '368a5a5d095c9a1a6aef9c51517545cc126e6142', NULL, NULL, NULL, 'gildas', 'gildas', '2009-06-06 00:00:00', 0x76696465, 'gildas', 'gildas', 'gildas', 'gildas', 9),"\
"(62, 1, 'Jean', 2, 'f7ed376ba27377ae2680fafe1a67037df80b7e36', NULL, NULL, NULL, 'Jean', 'Jean', '2009-06-06 00:00:00', 0x76696465, 'Jean', 'Jean', 'Jean', 'Jean', 9),"\
"(63, 1, 'lacave', 2, '2d015eca25fd336891782abaf1f41ed563d68732', NULL, NULL, NULL, 'lacave', 'lacave', '2009-06-06 00:00:00', 0x76696465, 'lacave', 'lacave', 'lacave', 'lacave', 9),"\
"(65, 1, 'Mouloud', 2, '079649a62b156d1619e03fa518867684a5119991', NULL, NULL, NULL, 'Mouloud', 'Mouloud', '2009-06-06 00:00:00', 0x76696465, 'Mouloud', 'Mouloud', 'Mouloud', 'Mouloud', 9),"\
"(67, 1, 'nanouc_a', 2, 'fe3e2ee496e39e843ae8180479432c240c88190e', NULL, NULL, NULL, 'nanouc_a', 'nanouc_a', '2009-06-06 00:00:00', 0x76696465, 'nanouc_a', 'nanouc_a', 'nanouc_a', 'nanouc_a', 9),"\
"(68, 1, 'vidal', 2, '5431a5ce02fa3c14c98aa025fc8454045c65b65d', NULL, NULL, NULL, 'vidal', 'vidal', '2009-06-06 00:00:00', 0x76696465, 'vidal', 'vidal', 'vidal', 'vidal', 9),"\
"(69, 1, 'etud6', 3, '2c404ec3d3eb2a922a8e301a1f237ad1e7f7eb58', NULL, '2009-06-06 15:23:28', NULL, 'Etudiant', '6eme', '0000-00-00 00:00:00', '', '', '', '', '', 237),"\
"(70, 1, 'etud5', 3, '99bf77682cc85d95068b537948e43eff99d7b6f3', NULL, '2009-06-06 14:47:47', NULL, 'Etudiant', '5eme', '0000-00-00 00:00:00', '', '', '', '', '', 237),"\
"(71, 1, 'TEST', 3, '984816fd329622876e14907634264e6f332e9fb3', NULL, NULL, NULL, 'TEST', 'TEST', '2009-06-06 00:00:00', 0x76696465, 'TEST', 'TEST', 'TEST', 'TEST', 0);");

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
                            "(3, 6);");
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
    qDebug() << "dir exist";
            dir.setFilter(QDir::Dirs| QDir::NoDotAndDotDot);
            QFileInfoList list = dir.entryInfoList();
            for (int i = 0; i < list.size(); ++i)
             {
               QFileInfo fileInfo = list.at(i);

                QDir dirfils(fileInfo.absoluteFilePath());
                found = 0;
                if (dirfils.exists())
                    {
qDebug() << "dirfils exist";
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

        this->Gsettings.setValue(((QCheckBox *)(ui->scrollArea->layout()->itemAt(i)->widget()))->text().split("/").first(),

                                 #ifdef WIN32
                                (((QCheckBox *)(ui->scrollArea->layout()->itemAt(i)->widget()))->text()));
                                 #else
                                (((QCheckBox *)(ui->scrollArea->layout()->itemAt(i)->widget()))->text()));
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
