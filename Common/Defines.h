#ifndef DEFINES_H
# define DEFINES_H

# ifndef PREFIX
#  if defined(Q_OS_WIN)
#   define PREFIX  "${Program Files}" // un truc dans ce genre la
#  elif defined(Q_OS_MAC)
#   define PREFIX  "/MAC_FOLDER_SHIT" // un truc dans ce genre la
#  else
#   define PREFIX  "/usr/local/"
#  endif
# endif

#ifndef ORGANIZATION_NAME
#define ORGANIZATION_NAME "Horus"
#endif
#ifndef ORGANIZATION_DOMAIN
#define ORGANIZATION_DOMAIN "4--2.net"
#endif

#ifndef SERVER_NAME
#define SERVER_NAME "Horus Server"
#endif
#ifndef SERVER_VERSION
#define SERVER_VERSION "0.1"
#endif

#ifndef CLIENT_NAME
#define CLIENT_NAME "Horus Client"
#endif
#ifndef CLIENT_VERSION
#define CLIENT_VERSION "0.1"
#endif

#ifndef CURRENT_PROTO_VERSION
#define CURRENT_PROTO_VERSION 0
#endif

//duration of the session
#ifndef DEFAULT_SESSION_LIFETIME
#define DEFAULT_SESSION_LIFETIME 720 // minutes    12h*60m     0 mean infinite      max is 65536 -> 45.5days
#endif
// size of the session key
#ifndef SESSION_WORD_SIZE
#define SESSION_WORD_SIZE 32 // bytes -> 64char hexa
#endif

#ifndef FILE_KEY_SIZE
#define FILE_KEY_SIZE 32 // bytes -> 64char hexa
#endif

// cannot be redefined, size of sha1 hash
#define SHA1_WORD_SIZE 20 //bytes -> 40char hexa

#ifndef MAX_POOL_THREADS
#define MAX_POOL_THREADS 500 //a big number for tests
#endif
#ifndef MAX_USER_THREADS
#define MAX_USER_THREADS 50 //idem
#endif

#ifndef STARTEVENTTYPE
#define STARTEVENTTYPE          1000
#endif
#ifndef STOPEVENTTYPE
#define STOPEVENTTYPE           1001
#endif
#ifndef LOADPLUGINEVENTTYPE
#define LOADPLUGINEVENTTYPE     1002
#endif
#ifndef UNLOADPLUGINEVENTTYPE
#define UNLOADPLUGINEVENTTYPE   1003
#endif
#ifndef NETWORKRECEIVEEVENTTYPE
#define NETWORKRECEIVEEVENTTYPE 1004
#endif

#ifndef SQLCONNECTIONCOUNT
//! Total of concurent SQL connections
#define SQLCONNECTIONCOUNT 5
#endif

#endif // DEFINES_H
