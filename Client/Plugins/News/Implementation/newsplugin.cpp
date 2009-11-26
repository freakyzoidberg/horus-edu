/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
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
