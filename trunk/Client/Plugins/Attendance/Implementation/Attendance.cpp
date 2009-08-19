#include		"Attendance.h"

const QString	Attendance::pluginName() const
{
	return ("Attendance");
}

const QString	Attendance::pluginVersion() const
{
	return ("0.1");
}

QWidget			*Attendance::getWidget()
{
	return (0);
}
