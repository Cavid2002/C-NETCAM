#include "src/CAMERA.hpp"
#include <unistd.h>
 
int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        error("invalid number of arguments");
    }
    int client_fd = create_socket(AF_INET, SOCK_DGRAM);
    
    sockaddr_in client;
    client.sin_addr.s_addr = inet_addr(argv[1]);
    client.sin_family = AF_INET;
    client.sin_port = htons(DEFAULT_PORT);
    socklen_t clientSize = sizeof(client);


    char confirm = 'Y';
    sendto(client_fd, &confirm, sizeof(char), 0, (sockaddr*)&client, clientSize);
    fprintf(stdout, "[INFO-CLIENT]Comfarmation is sent\n");
    recive_frame(client_fd, &client, &clientSize);
    
    close(client_fd);
    return 0;
}