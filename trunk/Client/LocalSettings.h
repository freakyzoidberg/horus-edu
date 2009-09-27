#ifndef __LOCALSETTINGS_H__
# define __LOCALSETTINGS_H__

# include	<QObject>

//! Class managing the local settings of the client
/*!
 *  Make configuration file if it don't exists.
 */
class LocalSettings : public QObject
{
public:
	static void createConfig();
};

#endif // __LOCALSETTINGS_H__
