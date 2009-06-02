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
# define FILE_TRANSFERT_WAIT_TIME 2 // 2s for test. after:// 300 // 5min
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

//! enumerate the differents Level of users
enum UserLevel { LEVEL_ROOT, LEVEL_ADMINISTRATOR, LEVEL_TEACHER, LEVEL_STUDENT, LEVEL_FAMILY, LEVEL_GUEST, __LAST_LEVEL__ };

#endif // DEFINES_H
