#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#define DEFAULT_PORT 3055

typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr_storage sockaddr_storage;


void error(const char* msg);

//returns fd for socket
//domain specifies the Adress Family and type TCP or UDP
int create_socket(int domain, int type);


//binds socket to specific port
int bind_to_port(int fd, unsigned int family, unsigned short port);

//specifies the how many connection can be accepted before rejection
int start_listening(int fd, int num);

//returns new socket_d for communication
//while orginal listens to new connection
int accept_connection(int fd, sockaddr_in* client_addr);


//for client returns nothing useful
int connect_to_port(int fd, int ip_family, unsigned short port, const char* ip_addr);