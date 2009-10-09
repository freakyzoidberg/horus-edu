#ifndef DEBUGGER_H
#define DEBUGGER_H

#include <QWidget>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>

class Debugger : public QWidget
{
  Q_OBJECT

public:
    static Debugger* instance();
    void addDebugMessage(const QString msg);
    ~Debugger();

private:
    Debugger();
    QVBoxLayout layout;
    QTextEdit   text;
    QPushButton resetButton;
    static Debugger* _instance;
};

#endif // DEBUGGER_H
