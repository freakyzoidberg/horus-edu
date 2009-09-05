#ifndef TESTGIT_H
#define TESTGIT_H

#include <QtPlugin>
#include <QHash>

#include "../../../DisplayablePlugin.h"

#include "TestGitWidget.h"

class TestGit : public DisplayablePlugin
{
    Q_OBJECT
    Q_INTERFACES(DisplayablePlugin)

public:
    inline TestGit(TestNetworkPlugin* _testNetworkPlugin) { widget = 0; testNetworkPlugin = _testNetworkPlugin; }

    // INTERFACE Plugin
    inline const QString    pluginName() const    { return "Test Git"; }
    inline const QString    pluginVersion() const { return "0.42"; }

    // INTERFACE DisplayablePlugin
    inline const QString    getDisplayableName() { return "Test a GiT"; }
    inline QWidget*         getWidget() { if (widget == 0) widget = new TestGitWidget(this, testNetworkPlugin); return widget; }

    TestGitWidget*          widget;
    TestNetworkPlugin* testNetworkPlugin;
};

#endif // TESTGIT_H
