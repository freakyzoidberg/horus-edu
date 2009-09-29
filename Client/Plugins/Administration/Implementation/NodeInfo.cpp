#include "NodeInfo.h"
#include "../../../../Common/UserData.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QBuffer>
#include <QMenu>
#include <qvariant.h>
#include "UserModel.h"

NodeInfo::NodeInfo(TreeData& _node, int type, UserDataPlugin &_users) : users(_users), node(_node)
{
    setupUi();
    connect(buttonBox, SIGNAL(clicked(QAbstractButton *)), this, SLOT(buttonClicked(QAbstractButton *)));
    if (type == 1)
    {
        buttonBox->addButton(new QPushButton(tr("Save")), QDialogButtonBox::ActionRole);
        buttonBox->addButton(new QPushButton(tr("Cancel")), QDialogButtonBox::ActionRole);
        fillFields();
    }
    else
    {
        buttonBox->addButton(new QPushButton(tr("Add")), QDialogButtonBox::ActionRole);
        buttonBox->addButton(new QPushButton(tr("Cancel")), QDialogButtonBox::ActionRole);
    }
    completer = new QCompleter(new UserModel(users.getAllUser(), this), this);
    completer->setCompletionMode(QCompleter::PopupCompletion);
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    userTxt->setCompleter(completer);
}

void    NodeInfo::setupUi()
{
    this->setMinimumWidth(300);
    mainLayout = new QVBoxLayout(this);
    infos = new QGroupBox(this);
    nodeLayout = new QFormLayout();
    nodeLayout->setHorizontalSpacing(4);
    nodeLayout->setVerticalSpacing(10);
    label = new QLabel(tr("Id"));
    nodeLayout->setWidget(1, QFormLayout::LabelRole, label);
    idTxt = new QLineEdit();
    idTxt->setReadOnly(true);
    nodeLayout->setWidget(1, QFormLayout::FieldRole, idTxt);
    label_1 = new QLabel(tr("Name"));
    nodeLayout->setWidget(2, QFormLayout::LabelRole, label_1);
    nameTxt = new QLineEdit(this);
    nodeLayout->setWidget(2, QFormLayout::FieldRole, nameTxt);
    label_2 = new QLabel(tr("Type"));
    nodeLayout->setWidget(3, QFormLayout::LabelRole, label_2);
    typeTxt = new QLineEdit(this);
    nodeLayout->setWidget(3, QFormLayout::FieldRole, typeTxt);
    label_3 = new QLabel(tr("User referent"));
    nodeLayout->setWidget(4, QFormLayout::LabelRole, label_3);
    userTxt = new QLineEdit(this);

    nodeLayout->setWidget(4, QFormLayout::FieldRole, userTxt);
    mainLayout->addLayout(nodeLayout);
    buttonBox = new QDialogButtonBox(Qt::Horizontal, this);
    mainLayout->addWidget(buttonBox);
    infos->setWindowTitle(tr("Edit Node"));
    infos->setLayout(mainLayout);
}

void NodeInfo::fillFields()
{
    idTxt->setText(QVariant(node.id()).toString());
    nameTxt->setText(node.name());
    typeTxt->setText(node.type());
    //userTxt->setText(((UserData*)node.user())->login());
}

void    NodeInfo::buttonClicked(QAbstractButton * button)
{
   if (button->text() == tr("Add"))
   {
        QMessageBox msgBox;
        msgBox.setText(tr("Confirme modification"));
        msgBox.setInformativeText(tr("Do you want to confirme the modification"));
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Yes);
        int ret = msgBox.exec();
        if (ret == QMessageBox::Yes)
        {
            node.setName(nameTxt->text());
            node.setType(typeTxt->text());
            node.setUser(users.getUser(completer->currentIndex().data(Qt::UserRole).toInt()));
            node.save();
        }
   }
   else if (button->text() == tr("Save"))
   {
        QMessageBox msgBox;
        QString      Error = "";
        if(this->nameTxt->text() == "")
            Error.append(tr("Name |"));
        if(this->typeTxt->text() == "")
            Error.append(tr("Type |"));
        if(this->userTxt->text() == "")
            Error.append(tr("User |"));
        if (Error != "")
        {
            QString msg;
            msg.append(tr("les champs suivant doivent etre remplis: \n"));
            msg.append(Error);

            msgBox.setText(msg);
            msgBox.exec();
            return;
        }
            node.setName(nameTxt->text());
            node.setType(typeTxt->text());
            node.setUser(users.getUser(completer->currentIndex().data(Qt::UserRole).toInt()));
            node.save();
   }
   else if (button->text() == tr("Cancel"))
   {

   }
}
