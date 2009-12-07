@echo off
cd Plugins
set BUILDCONFIG=debug
copy FileBaseClient\%BUILDCONFIG%\FileBaseClientMetaPlugin.dll .\FileBaseClientMetaPlugin.dll
copy TreeBaseClient\%BUILDCONFIG%\TreeBaseClientMetaPlugin.dll .\TreeBaseClientMetaPlugin.dll
copy UserBaseClient\%BUILDCONFIG%\UserBaseClientMetaPlugin.dll .\UserBaseClientMetaPlugin.dll
copy EventBaseClient\%BUILDCONFIG%\EventBaseClientMetaPlugin.dll .\EventBaseClientMetaPlugin.dll
copy Administration\%BUILDCONFIG%\Administration.dll .\Administration.dll
copy Administrationv2\%BUILDCONFIG%\Administrationv2.dll .\Administrationv2.dll
copy Attendance\%BUILDCONFIG%\Attendance.dll .\Attendance.dll
copy Course\%BUILDCONFIG%\Course.dll .\Course.dll
copy Calendar\%BUILDCONFIG%\Calendar.dll .\Calendar.dll
copy Editor\%BUILDCONFIG%\Editor.dll .\Editor.dll
copy LessonManager\%BUILDCONFIG%\LessonManager.dll .\LessonManager.dll
copy Mail\%BUILDCONFIG%\Mail.dll .\Mail.dll
copy MainFrame\%BUILDCONFIG%\MainFrame.dll .\MainFrame.dll
copy Marks\%BUILDCONFIG%\Marks.dll .\Marks.dll
copy PdfController\%BUILDCONFIG%\PdfController.dll .\PdfController.dll
copy PdfDisplayer\%BUILDCONFIG%\PdfDisplayer.dll .\PdfDisplayer.dll
copy PdfEditor\%BUILDCONFIG%\PdfEditor.dll .\PdfEditor.dll
copy SettingsBaseClient\%BUILDCONFIG%\SettingsBaseClientMetaPlugin.dll .\SettingsBaseClientMetaPlugin.dll
copy TextController\%BUILDCONFIG%\TextController.dll .\TextController.dll
copy ImageController\%BUILDCONFIG%\ImageController.dll .\ImageController.dll
copy ScheduleBaseClient\%BUILDCONFIG%\ScheduleBaseClientMetaPlugin.dll .\ScheduleBaseClientMetaPlugin.dll
copy TimeTable\%BUILDCONFIG%\TimeTable.dll .\TimeTable.dll
cd ..
