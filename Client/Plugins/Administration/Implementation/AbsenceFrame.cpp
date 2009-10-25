#include "AbsenceFrame.h"

AbsenceFrame::AbsenceFrame()
{
    setupUi();
}

void    AbsenceFrame::setupUi()
{
    absLayout = new QHBoxLayout(this);
    rightSide = new QGridLayout();
    leftSide = new QVBoxLayout();
    userName = new QLineEdit();
    leftSide->addWidget(userName);
    classList = new QComboBox();
    leftSide->addWidget(classList);
    userList = new QListView();
    leftSide->addWidget(userList);
    absLayout->addLayout(leftSide);
    //dateAbsence;
    //allCourse;
    //okButton;

}
