#include "Debugger.h"

#include <QLabel>
#include <QVariant>
#include <QScrollBar>


Debugger::Debugger()
{
    text.setReadOnly(true);
    resetButton.setText("Reset");
    QObject::connect(&resetButton, SIGNAL(clicked()), this, SLOT(reset()));

    setWindowFlags(Qt::Dialog);
    setLayout(&layout);
    setWindowTitle(tr("Horus debugger"));

    layout.addWidget(&text);
    layout.addWidget(&resetButton);

    reset();
    show();
}

Debugger* Debugger::instance()
{
    static Debugger debugger;
    return &debugger;
}

void Debugger::reset()
{
    list.clear();
    refresh();
//    layout.addWidget(new QLabel("Celui qui se sent d'ameliorer ca, mais je pouvais plus supporter les 500 mesages pour en voire un a la fin."));
}

void Debugger::refresh()
{
    text.setText(list.join("\n"));
    QScrollBar* bar = text.verticalScrollBar();
    bar->setValue(bar->maximum());
}

void Debugger::addDebugMessage(const QString msg)
{
    list.append(msg);
    refresh();
}
