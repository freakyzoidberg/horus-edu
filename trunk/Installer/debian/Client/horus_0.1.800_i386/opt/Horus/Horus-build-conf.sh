#!/bin/bash
#
#      	     Horus Team
#	contact@horus-edu.net
#

CONF="[General]\nVersion=0.1\nLessonsDirectoryPath=~/.Horus/Lessons\n\n[Plugins]\nUserDirectoryPath=/home/zoidberg/.Horus/Plugins\nLoad=libCourse.so, libPdfController.so, libTextController.so, libLessonManager.so, libdispPDF.so, libTreeManagement.so\n\n[Network]\nServer=localhost\nPort=42000\nPortTransfert=42042\n"

if  [ -d ~/.Horus/Plugins ]
then
echo -e $CONF > ~/.Horus/Horus\ Client.conf
else
mkdir -p ~/.Horus/Plugins
mkdir -p ~/.Horus/Lessons
echo -e $CONF > ~/.Horus/Horus\ Client.conf
fi

