#include	"newsplugin.h"

#include	<QWebView>
#include	<QLabel>
#include	<QNetworkProxy>

#include	"displayer.h"

NewsPlugin::NewsPlugin() :QWidget()
{
    QNetworkProxy proxy;

	proxy.setType(QNetworkProxy::HttpProxy);
    proxy.setHostName("10.42.42.62");
    proxy.setPort(3128);
    proxy.setUser("bertho_r");
    proxy.setPassword("pDewqw3(");
    QNetworkProxy::setApplicationProxy(proxy);
    QWebView  *web = new QWebView();
    web->setUrl(QUrl("https://www.horus-edu.net/"));
    web->setWindowTitle("News gogole");
    //web->show();
    QVBoxLayout *content = new QVBoxLayout();
    //QLabel toto("toto");
    //toto.setLayout(content);
    //content->addWidget(web.window());
    content->addWidget(web);
    //content->addWidget(toto.layout()->widget());
    setLayout(content->layout());

}
