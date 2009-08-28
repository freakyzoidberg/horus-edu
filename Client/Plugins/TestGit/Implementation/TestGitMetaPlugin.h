#ifndef TESTGITMETAPLUGIN_H
#define TESTGITMETAPLUGIN_H

#include "../../../Common/MetaPlugin.h"

#include "TestGit.h"

class TestGitMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline TestGitMetaPlugin() {
      Plugin* p = new TestGit;
      pluginList.append(p);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(TestGitMetaPlugin, TestGitMetaPlugin);

#endif // MAINFRAMEMETAPLUGIN_H
