#ifndef __LOCALSETTINGS_H__
# define __LOCALSETTINGS_H__

# include	<QSettings>

//! Class managing the local settings of the client
/*!
 *  Make configuration file if it don't exists.
 */
class LocalSettings : public QSettings
{
public:
	LocalSettings();

	void checkConfig();
};

#endif // __LOCALSETTINGS_H__
