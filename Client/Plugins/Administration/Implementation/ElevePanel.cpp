#include "ElevePanel.h"

ElevePanel::ElevePanel(QHash<int, QString> eleves)
{
    setupUi();
    fillStudents(eleves);
    mainLayout->addLayout(bottomLayout);
    connect(okButton, SIGNAL(clicked()), this, SLOT(validateClicked()));
}

void        ElevePanel::setupUi()
{
    mainLayout = new QVBoxLayout(this);
//    scrollArea = new QScrollArea;
//    scrollArea->setBackgroundRole(QPalette::Dark);
//    scrollArea->setLayout(mainLayout);
//
    mainLayout->setAlignment(this, Qt::AlignTop);
    bottomLayout = new QHBoxLayout();
    date = new QDateEdit(QDate::currentDate());
    date->setMaximumWidth(120);
    bottomLayout->addWidget(date);
    coefLabel = new QLabel(tr("Coef"));
    bottomLayout->addWidget(coefLabel);
    coef = new QLineEdit();
    coef->setMaximumWidth(40);
    okButton = new QPushButton(tr("Valider"));
    bottomLayout->addWidget(coef);
    bottomLayout->addWidget(okButton);
}

void        ElevePanel::fillStudents(QHash<int, QString> students)
{
    QHBoxLayout *tmp = new QHBoxLayout();
    QLabel *stuL = new QLabel(tr("Eleves"));
    stuL->setMaximumWidth(120);
    stuL->setMinimumWidth(70);
    tmp->addWidget(stuL);
    QLabel *markL = new QLabel(tr("Notes"));
    tmp->addWidget(markL);
    QLabel *comL = new QLabel(tr("Commentaire"));
    tmp->addWidget(comL);
    mainLayout->addLayout(tmp);
    mainLayout->setAlignment(tmp, Qt::AlignTop);
    QHash<int, QString>::const_iterator it = students.constBegin();
    QList<QWidget*> wdgts;
    QLineEdit *tmpNote;
    QLineEdit *tmpCom;
    while(it != students.constEnd())
    {
        tmp = new QHBoxLayout();
        QLabel *userName = new QLabel(it.value());
        userName->setMaximumWidth(180);
        userName->setMinimumWidth(120);
        tmp->addWidget(userName);
        tmpNote = new QLineEdit();
        tmpNote->setMaximumWidth(30);
        tmp->addWidget(tmpNote);
        tmpCom = new QLineEdit();
        tmp->addWidget(tmpCom);
        wdgts.append(tmpNote);
        wdgts.append(tmpCom);
        hNotes[it.key()] = wdgts;
        mainLayout->addLayout(tmp);
        mainLayout->setAlignment(tmp, Qt::AlignTop);
        wdgts.clear();
        ++it;
    }
    mainLayout->setSpacing(4);
    mainLayout->setMargin(0);
}

void    ElevePanel::validateClicked()
{
    QHash<int, QList<QWidget* > >::const_iterator it = hNotes.constBegin();
    while(it != hNotes.constEnd())
    {
        if (((QLineEdit*)it.value()[0])->text() == "" || ((QLineEdit*)it.value()[1])->text() == "")
        {
            QMessageBox msgBox;
            msgBox.setText(tr(""));
            msgBox.setInformativeText(tr("Veuillez remplir tous les champs."));
            msgBox.setStandardButtons(QMessageBox::Yes);
            msgBox.exec();
            break;
        }
        ++it;
    }
}
