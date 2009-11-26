/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/********************************************************************************
** Form generated from reading ui file 'mailbox.ui'
**
** Created: Mon 31. Aug 21:09:33 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAILBOX_H
#define UI_MAILBOX_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mailboxClass
{
public:
    QWidget *centralWidget;
    QPushButton *new_message;
    QPushButton *mailbox;
    QWidget *widget_mailbox;
    QLabel *label;
    QLabel *label_2;
    QWidget *widget_send_message;
    QLabel *label_from;
    QLineEdit *lineEdit_from;
    QLineEdit *lineEdit_to;
    QLabel *label_to;
    QLabel *label_subject;
    QLineEdit *lineEdit_subject;
    QPushButton *pushButton_send;
    QPlainTextEdit *content_message;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *mailboxClass)
    {
        if (mailboxClass->objectName().isEmpty())
            mailboxClass->setObjectName(QString::fromUtf8("mailboxClass"));
        mailboxClass->resize(731, 519);
        centralWidget = new QWidget(mailboxClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        new_message = new QPushButton(centralWidget);
        new_message->setObjectName(QString::fromUtf8("new_message"));
        new_message->setGeometry(QRect(30, 40, 101, 21));
        mailbox = new QPushButton(centralWidget);
        mailbox->setObjectName(QString::fromUtf8("mailbox"));
        mailbox->setGeometry(QRect(30, 70, 101, 21));
        widget_mailbox = new QWidget(centralWidget);
        widget_mailbox->setObjectName(QString::fromUtf8("widget_mailbox"));
        widget_mailbox->setGeometry(QRect(160, 20, 531, 361));
        label = new QLabel(widget_mailbox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(170, 10, 171, 31));
        label_2 = new QLabel(widget_mailbox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(210, 190, 46, 14));
        widget_send_message = new QWidget(centralWidget);
        widget_send_message->setObjectName(QString::fromUtf8("widget_send_message"));
        widget_send_message->setEnabled(true);
        widget_send_message->setGeometry(QRect(10, 100, 441, 353));
        label_from = new QLabel(widget_send_message);
        label_from->setObjectName(QString::fromUtf8("label_from"));
        label_from->setGeometry(QRect(40, 10, 41, 21));
        lineEdit_from = new QLineEdit(widget_send_message);
        lineEdit_from->setObjectName(QString::fromUtf8("lineEdit_from"));
        lineEdit_from->setGeometry(QRect(90, 10, 311, 20));
        lineEdit_to = new QLineEdit(widget_send_message);
        lineEdit_to->setObjectName(QString::fromUtf8("lineEdit_to"));
        lineEdit_to->setGeometry(QRect(90, 50, 311, 20));
        label_to = new QLabel(widget_send_message);
        label_to->setObjectName(QString::fromUtf8("label_to"));
        label_to->setGeometry(QRect(40, 50, 46, 14));
        label_subject = new QLabel(widget_send_message);
        label_subject->setObjectName(QString::fromUtf8("label_subject"));
        label_subject->setGeometry(QRect(40, 80, 46, 14));
        lineEdit_subject = new QLineEdit(widget_send_message);
        lineEdit_subject->setObjectName(QString::fromUtf8("lineEdit_subject"));
        lineEdit_subject->setGeometry(QRect(90, 80, 311, 20));
        pushButton_send = new QPushButton(widget_send_message);
        pushButton_send->setObjectName(QString::fromUtf8("pushButton_send"));
        pushButton_send->setGeometry(QRect(120, 320, 75, 23));
        content_message = new QPlainTextEdit(widget_send_message);
        content_message->setObjectName(QString::fromUtf8("content_message"));
        content_message->setGeometry(QRect(90, 120, 311, 171));
        mailboxClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(mailboxClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 731, 21));
        mailboxClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(mailboxClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mailboxClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(mailboxClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        mailboxClass->setStatusBar(statusBar);

        retranslateUi(mailboxClass);

        QMetaObject::connectSlotsByName(mailboxClass);
    } // setupUi

    void retranslateUi(QMainWindow *mailboxClass)
    {
        mailboxClass->setWindowTitle(QApplication::translate("mailboxClass", "mailbox", 0, QApplication::UnicodeUTF8));
        new_message->setText(QApplication::translate("mailboxClass", "Nouveau message", 0, QApplication::UnicodeUTF8));
        mailbox->setText(QApplication::translate("mailboxClass", "Boite de reception", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("mailboxClass", "boite de reception", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("mailboxClass", "EN DEV", 0, QApplication::UnicodeUTF8));
        label_from->setText(QApplication::translate("mailboxClass", "FROM :", 0, QApplication::UnicodeUTF8));
        label_to->setText(QApplication::translate("mailboxClass", "TO :", 0, QApplication::UnicodeUTF8));
        label_subject->setText(QApplication::translate("mailboxClass", "Subject :", 0, QApplication::UnicodeUTF8));
        pushButton_send->setText(QApplication::translate("mailboxClass", "Envoyer", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(mailboxClass);
    } // retranslateUi

};

namespace Ui {
    class mailboxClass: public Ui_mailboxClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAILBOX_H
