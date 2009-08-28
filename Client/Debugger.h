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

private:
    Debugger();
    QVBoxLayout layout;
    QTextEdit   text;
    QPushButton resetButton;
    QStringList list;

private slots:
    void reset();
    void refresh();
};

#endif // DEBUGGER_H
