#include "newsplugin.h"
#include "displayer.h"
#include <QWebView>
#include <QLabel>
NewsPlugin::NewsPlugin() :QWidget()
{

    QWebView  *web = new QWebView();
    web->setUrl(QUrl("http://news.google.com"));
    web->setWindowTitle("News gogole");
    //web->show();

    //Displayer disp;
    //disp.activateOn(&web);


    QVBoxLayout *content = new QVBoxLayout();
    //QLabel toto("toto");
    //toto.setLayout(content);
    //content->addWidget(web.window());
    content->addLayout(web->layout());
    //content->addWidget(toto.layout()->widget());
    setLayout(content->layout());

}
