#include "MailPanel.h"
#include <QPushButton>
MailPanel::MailPanel(): QWidget()
{
    QPushButton *writemail = new QPushButton(tr("Write Mail"));
    layout.addWidget(writemail);
    setLayout(layout);
}

MailPanel::~MailPanel()
{
}
