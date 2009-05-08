#ifndef CLIENTAPPLICATION_H
#define CLIENTAPPLICATION_H

#include    <QtGui/QApplication>

class ClientApplication : public QApplication
{
public:
    ClientApplication(int argc, char *argv[]);
    ~ClientApplication();
    bool    event(QEvent *event);

    void    reloadPlugins();
    void    restartNetwork();

    QWidget *loader;
};


#endif // CLIENTAPPLICATION_H
