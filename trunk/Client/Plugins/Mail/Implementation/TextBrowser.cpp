#include "TextBrowser.h"

TextBrowser::TextBrowser()
{
}


void TextBrowser::setSource ( const QString & name )
{
    QMessageBox::information(NULL, "here", QString("devrait ouvrir un browser sur le systeme avec ")+name);
}
