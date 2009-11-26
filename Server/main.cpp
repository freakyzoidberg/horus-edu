/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Horus is free software: you can redistribute it and/or modify               *
 * it under the terms of the GNU General Public License as published by        *
 * the Free Software Foundation, either version 3 of the License, or           *
 * (at your option) any later version.                                         *
 *                                                                             *
 * Horus is distributed in the hope that it will be useful,                    *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                *
 * GNU General Public License for more details.                                *
 *                                                                             *
 * You should have received a copy of the GNU General Public License           *
 * along with Horus. If not, see <http://www.gnu.org/licenses/>.               *
 *                                                                             *
 * The orginal content of this material was realized as part of                *
 * 'Epitech Innovative Project' www.epitech.eu                                 *
 *                                                                             *
 * You are required to preserve the names of the original authors              *
 * of this content in every copy of this material                              *
 *                                                                             *
 * Authors :                                                                   *
 * - BERTHOLON Romain                                                          *
 * - GRANDEMANGE Adrien                                                        *
 * - LACAVE Pierre                                                             *
 * - LEON-BONNET Valentin                                                      *
 * - NANOUCHE Abderrahmane                                                     *
 * - THORAVAL Gildas                                                           *
 * - VIDAL Jeremy                                                              *
 *                                                                             *
 * You are also invited but not required to send a mail to the original        *
 * authors of this content in case of modification of this material            *
 *                                                                             *
 * Contact: contact@horus-edu.net                                              *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
#include				<QCoreApplication>
#ifdef					Q_OS_WIN
# include				<Windows.h>
# include				<Strsafe.h>
#endif
#include				<QtNetwork>
#include				<QThreadPool>
#include				<QString>

#include				"../Common/Defines.h"
#include				"../Common/Logs.h"
#include				"Server.h"
#include				"PluginManagerServer.h"
#include				"Settings.h"

#ifdef					Q_OS_WIN
SERVICE_STATUS			gSvcStatus;
SERVICE_STATUS_HANDLE	gSvcStatusHandle;
bool					console;

void					ReportSvcStatus(DWORD dwCurrentState, DWORD dwWin32ExitCode, DWORD dwWaitHint)
{
	static DWORD		dwCheckPoint = 1;

	gSvcStatus.dwCurrentState = dwCurrentState;
	gSvcStatus.dwWin32ExitCode = dwWin32ExitCode;
	gSvcStatus.dwWaitHint = dwWaitHint;
	if (dwCurrentState == SERVICE_START_PENDING)
		gSvcStatus.dwControlsAccepted = 0;
	else
		gSvcStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
	if ((dwCurrentState == SERVICE_RUNNING) || (dwCurrentState == SERVICE_STOPPED))
		gSvcStatus.dwCheckPoint = 0;
	else
		gSvcStatus.dwCheckPoint = dwCheckPoint++;
	SetServiceStatus(gSvcStatusHandle, &gSvcStatus);
}

void WINAPI				controlHandler(DWORD control)
{
	switch(control)
	{
	case SERVICE_CONTROL_STOP :
		ReportSvcStatus(SERVICE_STOP_PENDING, NO_ERROR, 0);
		ReportSvcStatus(gSvcStatus.dwCurrentState, NO_ERROR, 0);
		ReportSvcStatus( SERVICE_STOPPED, NO_ERROR, 0 );
		exit(0);
		break ;
	case SERVICE_CONTROL_INTERROGATE :
		break;
	default :
		break;
   }
}

int						serviceMain(int argc, char **argv)
#else
int						main(int argc, char *argv[])
#endif
{
	int					i;
    QCoreApplication	a(argc, argv);
	Settings			*tmpSetting;

#ifdef					Q_OS_WIN
	if (!console)
	{
		gSvcStatusHandle = RegisterServiceCtrlHandler(TEXT(SERVER_NAME), controlHandler);
		if (!gSvcStatusHandle)
			logs::addlog(LOGERROR,"RegisterServiceCtrlHandler failed");
		gSvcStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
		gSvcStatus.dwServiceSpecificExitCode = 0;
		ReportSvcStatus(SERVICE_START_PENDING, NO_ERROR, 3000);
	}
#endif	
	QCoreApplication::setOrganizationName(ORGANIZATION_NAME);
    QCoreApplication::setOrganizationDomain(ORGANIZATION_DOMAIN);
    QCoreApplication::setApplicationName(SERVER_NAME);
    for (i = 0; i < QCoreApplication::arguments().count(); i++)
        if (QCoreApplication::arguments().at(i) == "--gen-config")
            {
                tmpSetting = new Settings();
                tmpSetting->FirstSetSettings();
                delete tmpSetting;
                return (0);
           }
    Server theserver(&a);
    PluginManagerServer::instance()->load();
    logs::addlog(LOGINFO,"Server fully Loaded");
    QThreadPool::globalInstance()->setMaxThreadCount(MAX_POOL_THREADS);
#ifdef					Q_OS_WIN
	if (!console)
		ReportSvcStatus(SERVICE_RUNNING, NO_ERROR, 0);
#endif
    return (a.exec());
}

#ifdef					Q_OS_WIN

int						installService()
{
	SC_HANDLE			manager;
	SC_HANDLE			service;
	TCHAR				path[4096];

	if (!GetModuleFileName(NULL, path, 4096))
		return (-1);
	manager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (!manager) 
		return (-1);
	service = CreateService(manager, TEXT(SERVER_NAME), QCoreApplication::tr(SERVER_NAME).toStdWString().c_str(), SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS, SERVICE_AUTO_START, SERVICE_ERROR_NORMAL, path, NULL, NULL, NULL, NULL, NULL);
	if (!service) 
	{
		CloseServiceHandle(manager);
		return (-1);
	}
	CloseServiceHandle(service); 
	CloseServiceHandle(manager);
	return (0);
}

void					reportEvent(LPTSTR szFunction) 
{ 
	HANDLE				hEventSource;
	LPCTSTR				lpszStrings[2];
	TCHAR				Buffer[80];

	hEventSource = RegisterEventSource(NULL, TEXT(SERVER_NAME));
	if (hEventSource)
	{
		StringCchPrintf(Buffer, 80, TEXT("%s failed with %d"), szFunction, GetLastError());
		lpszStrings[0] = TEXT(SERVER_NAME);
		lpszStrings[1] = Buffer;
		ReportEvent(hEventSource, EVENTLOG_ERROR_TYPE, 0, (DWORD) 0xC0020001L, NULL, 2, 0, lpszStrings, NULL);
		DeregisterEventSource(hEventSource);
	}
}
#include <QFile>

int						main(int argc, char *argv[])
{
	console = false;
	SERVICE_TABLE_ENTRY	DispatchTable[] = {{TEXT("Horus Server"), (LPSERVICE_MAIN_FUNCTION) serviceMain}, {NULL, NULL}}; 
	if (argc > 1 && _strcmpi(argv[1], "install") == 0)
		return (installService());
    if (!StartServiceCtrlDispatcher(DispatchTable)) 
	{
		if (GetLastError() == ERROR_FAILED_SERVICE_CONTROLLER_CONNECT)
		{
			console = true;
			serviceMain(argc, argv);
		}
	    logs::addlog(LOGERROR,"StartServiceCtrlDispatcher failed");
	}
	return (-42);
}

#endif
