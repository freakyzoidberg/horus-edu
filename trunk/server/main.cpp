#include <QtCore/QCoreApplication>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setApplicationName("test");
    write(0, "coucou", 6);

    return a.exec();
}
