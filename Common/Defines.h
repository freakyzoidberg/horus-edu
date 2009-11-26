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
#ifndef DEFINES_H
# define DEFINES_H

# ifndef PREFIX
#  if defined(Q_OS_WIN)
#   define PREFIX  "${Program Files}" // un truc dans ce genre la
#  elif defined(Q_OS_MAC)
#   define PREFIX  "/MAC_FOLDER" // un truc pas dans ce genre la
#  else
#   define PREFIX  "/opt/"
#  endif
# endif

#ifndef ORGANIZATION_NAME
# define ORGANIZATION_NAME "Horus"
#endif
#ifndef ORGANIZATION_DOMAIN
# define ORGANIZATION_DOMAIN "horus-edu.net"
#endif

#ifndef SERVER_NAME
# define SERVER_NAME "Horus Server"
#endif
#ifndef SERVER_VERSION
# define SERVER_VERSION "0.1"
#endif

#ifndef CLIENT_NAME
# define CLIENT_NAME "Horus Client"
#endif
#ifndef CLIENT_VERSION
# define CLIENT_VERSION "0.1"
#endif

#ifndef CURRENT_PROTO_VERSION
# define CURRENT_PROTO_VERSION 0
#endif

#ifndef DEFAULT_SESSION_LIFETIME
//! duration of the session
# define DEFAULT_SESSION_LIFETIME 720 // minutes    12h*60m     0 mean infinite      max is 65536 -> 45.5days
#endif

#ifndef SESSION_WORD_SIZE
//! size of the session key
# define SESSION_WORD_SIZE 32 // bytes -> 64char hexa
#endif

#ifndef FILE_TRANSFERT_KEY_SIZE
//! size of the file transfert authorisation key
# define FILE_TRANSFERT_KEY_SIZE 32 // bytes -> 64char hexa
#endif
#ifndef FILE_TRANSFERT_WAIT_TIME
//! duration of the authorization key stay available if not used (in second)
# define FILE_TRANSFERT_WAIT_TIME 300 // 2s for test. after:// 300 // 5min
#endif

#define SHA1_WORD_SIZE 20 //bytes -> 40char hexa

#ifndef MAX_POOL_THREADS
# define MAX_POOL_THREADS 500 //a big number for tests
#endif
#ifndef MAX_USER_THREADS
# define MAX_USER_THREADS 50 //idem
#endif

#ifndef SQLCONNECTIONCOUNT
//! Total of concurent SQL connections
# define SQLCONNECTIONCOUNT 5
#endif

#ifndef LOGERROR
//! Total of concurent SQL connections
# define LOGERROR 1
#endif

#ifndef LOGWARNING
//! Total of concurent SQL connections
# define LOGWARNING 2
#endif

#ifndef LOGINFO
//! Total of concurent SQL connections
# define LOGINFO 3
#endif

#ifndef LOGDEBUG
//! Total of concurent SQL connections
# define LOGDEBUG 4
#endif

#ifdef HORUS_SERVER
#else
#ifdef HORUS_CLIENT
#else
  #error "You must define HORUS_CLIENT or HORUS_SERVER in your .pro file (DEFINES += HORUS_...)."
#endif
#endif

#endif // DEFINES_H
