#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <QWidget>
#include <QVBoxLayout>

class Debugger : public QWidget
{
public:
    static void addDebugMessage(const QString msg);
    static Debugger* instance();;

private:
    Debugger();
    QVBoxLayout layout;
};

#endif // DEBUGGER_H
