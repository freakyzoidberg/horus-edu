#include "Debugger.h"

#include <QLabel>
#include <QVariant>
#include <QScrollBar>

Debugger::Debugger()
{
    text.setReadOnly(true);
    resetButton.setText(tr("Reset"));
	QObject::connect(&resetButton, SIGNAL(clicked()), &text, SLOT(clear()));

    setWindowFlags(Qt::Dialog);
    setLayout(&layout);
    setWindowTitle(tr("Horus debugger"));

    layout.addWidget(&text);
    layout.addWidget(&resetButton);

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

void Debugger::addDebugMessage(const QString msg)
{
	text.append(msg);
}
