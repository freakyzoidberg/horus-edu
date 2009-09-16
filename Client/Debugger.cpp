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

Debugger::~Debugger()
{
    _instance = 0;
}

Debugger* Debugger::_instance = 0;
Debugger* Debugger::instance()
{
    if ( ! _instance)
        _instance = new Debugger;
    return _instance;
}

void Debugger::reset()
{
    list.clear();
    refresh();
}

void Debugger::refresh()
{
    text.setText(list.join("\n"));
    QScrollBar* bar = text.verticalScrollBar();
    bar->setValue( bar->maximum() );
}

void Debugger::addDebugMessage(const QString msg)
{
    list.append(msg);
    refresh();
}
