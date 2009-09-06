#include "TeacherPage.h"

TeacherPage::TeacherPage()
{
    setupUi();
}

void    TeacherPage::setupUi()
{
    teaLayout = new QHBoxLayout(this);
    teacherTree = new QTreeView();
    menuLayout = new QVBoxLayout();
    menuLayout->setAlignment(Qt::AlignHCenter);
    formLayout = new QHBoxLayout();
    leftLayout = new QFormLayout();
    leftLayout->setHorizontalSpacing(4);
    leftLayout->setVerticalSpacing(10);
    label = new QLabel("Login");
    leftLayout->setWidget(1, QFormLayout::LabelRole, label);
    loginTxt = new QLineEdit();
    leftLayout->setWidget(1, QFormLayout::FieldRole, loginTxt);
    label_12 = new QLabel("Password");
    leftLayout->setWidget(2, QFormLayout::LabelRole, label_12);
    passTxt = new QLineEdit(this);
    leftLayout->setWidget(2, QFormLayout::FieldRole, passTxt);
    date = new QCalendarWidget();
    leftLayout->setWidget(3, QFormLayout::FieldRole, date);
    label_2 = new QLabel("Nom");
    leftLayout->setWidget(4, QFormLayout::LabelRole, label_2);
    nomTxt = new QLineEdit(this);
    leftLayout->setWidget(4, QFormLayout::FieldRole, nomTxt);
    label_3 = new QLabel("Prenom");
    leftLayout->setWidget(5, QFormLayout::LabelRole, label_3);
    prenomTxt = new QLineEdit(this);
    leftLayout->setWidget(5, QFormLayout::FieldRole, prenomTxt);
    label_4 = new QLabel("Telephone");
    leftLayout->setWidget(6, QFormLayout::LabelRole, label_4);
    phoneTxt = new QLineEdit(this);
    leftLayout->setWidget(6, QFormLayout::FieldRole, phoneTxt);
    label_6 = new QLabel("Telephone 2");
    leftLayout->setWidget(7, QFormLayout::LabelRole, label_6);
    phonebisTxt = new QLineEdit(this);
    leftLayout->setWidget(7, QFormLayout::FieldRole, phonebisTxt);
    label_7 = new QLabel("Addresse");
    leftLayout->setWidget(8, QFormLayout::LabelRole, label_7);
    addrTxt = new QLineEdit(this);
    leftLayout->setWidget(8, QFormLayout::FieldRole, addrTxt);
    label_10 = new QLabel("Code");
    leftLayout->setWidget(9, QFormLayout::LabelRole, label_10);
    codeTxt = new QLineEdit(this);
    leftLayout->setWidget(9, QFormLayout::FieldRole, codeTxt);
    label_9 = new QLabel("Ville");
    leftLayout->setWidget(10, QFormLayout::LabelRole, label_9);
    villeTxt = new QLineEdit(this);
    leftLayout->setWidget(10, QFormLayout::FieldRole, villeTxt);
    label_8 = new QLabel("Pays");
    leftLayout->setWidget(11, QFormLayout::LabelRole, label_8);
    paysTxt = new QLineEdit(this);
    leftLayout->setWidget(11, QFormLayout::FieldRole, paysTxt);
    label_11 = new QLabel("Language");
    leftLayout->setWidget(12, QFormLayout::LabelRole, label_11);
    languageTxt = new QLineEdit(this);
    languageTxt->setObjectName(QString::fromUtf8("languageTxt"));
    leftLayout->setWidget(12, QFormLayout::FieldRole, languageTxt);
    activeBox = new QCheckBox("Active");
    activeBox->setObjectName(QString::fromUtf8("activeBox"));
    leftLayout->setWidget(0, QFormLayout::FieldRole, activeBox);
    formLayout->addLayout(leftLayout);
    rightLayout = new QFormLayout();
    rightLayout->setFieldGrowthPolicy(QFormLayout::ExpandingFieldsGrow);
    rightLayout->setHorizontalSpacing(3);
    rightLayout->setVerticalSpacing(10);
    graphicsView = new QGraphicsView(this);
    rightLayout->setWidget(2, QFormLayout::FieldRole, graphicsView);
    classTxt = new QLineEdit(this);
    classTxt->setObjectName(QString::fromUtf8("classTxt"));
    rightLayout->setWidget(0, QFormLayout::FieldRole, classTxt);
    label_5 = new QLabel("Classe");
    label_5->setObjectName(QString::fromUtf8("label_5"));
    rightLayout->setWidget(0, QFormLayout::LabelRole, label_5);
    lineEdit_7 = new QLineEdit(this);
    lineEdit_7->setObjectName(QString::fromUtf8("lineEdit_7"));
    rightLayout->setWidget(3, QFormLayout::FieldRole, lineEdit_7);
    formLayout->addLayout(rightLayout);
    menuLayout->addLayout(formLayout);
    buttonBox = new QDialogButtonBox(Qt::Horizontal, this);

    buttonBox->addButton(new QPushButton("Add"), QDialogButtonBox::ActionRole);
    buttonBox->addButton(new QPushButton("Save"), QDialogButtonBox::ActionRole);
    buttonBox->addButton(new QPushButton("Cancel"), QDialogButtonBox::ActionRole);
    buttonBox->addButton(new QPushButton("Delete"), QDialogButtonBox::ActionRole);
    menuLayout->addWidget(buttonBox);
    teaLayout->addWidget(teacherTree);
    teaLayout->addLayout(menuLayout);
    this->teaLayout->setStretch(0, 1);
    this->teaLayout->setStretch(1, 3);
}
