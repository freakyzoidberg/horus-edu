#ifndef			__MAINFRAMEMETAPLUGIN_H__
# define		__MAINFRAMEMETAPLUGIN_H__

# include		"../../../Common/MetaPlugin.h"

# include		"MainFrame.h"
# include		"ExampleSmallDisplayable.h"

class			MainFrameMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline		MainFrameMetaPlugin()
	{
      Plugin*	p = new MainFrame();
      pluginList.append(p);
	  p = new ExampleSmallDisplayable();
	  pluginList.append(p);
      //PluginManager().addPlugin(p);
	}
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(MainFrameMetaPlugin, MainFrameMetaPlugin);

#endif //		MAINFRAMEMETAPLUGIN_H
