#include "src/CAMERA.hpp"
#include <unistd.h>

int main()
{
    int fd = create_socket(AF_INET, SOCK_DGRAM);
    bind_to_port(fd, AF_INET, DEFAULT_PORT);
    sockaddr_in clientData;
    socklen_t clientDataSize = sizeof(clientData);
    char confirm;
     int c = recvfrom(fd, &confirm, sizeof(char), 0, (sockaddr*)&clientData, &clientDataSize);
    if(confirm != 'Y')
    {
        error("Comformation error!");
    }
    fprintf(stdout, "[INFO-SERVER]Comfarmation is recieved!\n");
    enable_camera(fd, &clientData, &clientDataSize);  
    return 0;    
}