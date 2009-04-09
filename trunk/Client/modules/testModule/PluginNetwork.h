#ifndef PLUGINNETWORK_H
#define PLUGINNETWORK_H

#include <QEvent>

class   PluginNetwork : IPluginNetwork
{
    public:
        PluginNetwork(QEvent *);

        bool    handler();

    private:
        QEvent  *event;
};

#endif // PLUGINNETWORK_H
