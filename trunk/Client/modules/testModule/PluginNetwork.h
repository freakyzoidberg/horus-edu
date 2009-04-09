#ifndef PLUGINNETWORK_H
#define PLUGINNETWORK_H

#include <QEvent>

class   PluginNetwork : public IPluginNetwork
{
    public:
        PluginNetwork(QEvent *);

        bool    handler();

    private:
        QEvent  *event;
};

#endif // PLUGINNETWORK_H
