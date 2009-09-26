#ifndef COURSEMETAPLUGIN_H
#define COURSEMETAPLUGIN_H

#include "../../../../Common/MetaPlugin.h"

#include "Course.h"
#include "../../../../Common/DataImplementations/WhiteBoardData/WhiteBoardDataPlugin.h"

class CourseMetaPlugin : public MetaPlugin
{
  Q_OBJECT
  Q_INTERFACES(MetaPlugin)

public:
    inline CourseMetaPlugin() {
	  pluginList.append(new Course);
	  pluginList.append(new WhiteBoardDataPlugin);
  }
};

/* maybe put this lines in a cpp if this file is include by an other file */
// declare instance of the plugin
Q_EXPORT_PLUGIN2(CourseMetaPlugin, CourseMetaPlugin);

#endif // COURSEMETAPLUGIN_H
