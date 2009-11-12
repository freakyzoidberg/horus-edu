#ifndef TEXTBROWSER_H
#define TEXTBROWSER_H

#include <QTextBrowser>
#include <QtGui>
 #include <QMessageBox>
class TextBrowser : public QTextBrowser
{
    Q_OBJECT
public:
    TextBrowser();


    void setSource ( const QString & name );
};

#endif // TEXTBROWSER_H
