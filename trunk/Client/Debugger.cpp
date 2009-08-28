#include "Debugger.h"

#include <QLabel>
#include <QVariant>

Debugger::Debugger()
{
    setWindowFlags(Qt::Dialog);

    setLayout(&layout);
    setWindowTitle(tr("Horus debugger"));

    layout.addWidget(new QLabel("Celui qui se sent d'ameliorer ca, mais je pouvais plus supporter les 500 mesages pour en voire un a la fin."));

    show();
}

Debugger* Debugger::instance()
{
    static Debugger debugger;
    return &debugger;
}

void Debugger::addDebugMessage(const QString msg)
{
    static int line = 0;

//    instance()->setGeometry(QRect(0,0,500,250));

//    instance()->setRowStretch(4, 0);
//        layout.addWidget(tv, 4, 0);

    instance()->layout.addWidget(new QLabel(QVariant(line).toString() + " : " + msg));
    line++;
}
