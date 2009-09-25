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
    inline TestGit(TestNetworkPlugin* _testNetworkPlugin) { testNetworkPlugin = _testNetworkPlugin; }

    // INTERFACE Plugin
    inline const QString    pluginName() const    { return "Test Git"; }
    inline const QString    pluginVersion() const { return "0.42"; }

    // INTERFACE DisplayablePlugin
	inline const QString    getDisplayableName() const { return "Test a GiT"; }
    inline QWidget*         getWidget() { return new TestGitWidget(this, testNetworkPlugin); }

    TestNetworkPlugin*      testNetworkPlugin;
};

#endif // TESTGIT_H
