#include "LessonTabTeacher.h"

#include	<Phonon/VideoPlayer>

LessonTabTeacher::LessonTabTeacher(PluginManager *pluginManager) : _pluginManager(pluginManager)
{
	Phonon::VideoPlayer	*player;

	player = new Phonon::VideoPlayer(this);
	player->load(Phonon::MediaSource("C:\\Users\\Public\\Videos\\Sample Videos\\Wildlife.wmv"));
	player->play();
}
