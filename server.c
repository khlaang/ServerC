// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 3000
int main(int argc, char const *argv[])
{
    int socket_descriptor, new_socket, read_value;
    struct sockaddr_in address;
    int option = 1;
    int size_address = sizeof(address);
    char buffer[1024] = {0};
    char *message = "The LRC congratulates you";
       
    // Création du socket (domain, type, protocol | SOCKSTREAM = TCP )
    if ((socket_descriptor = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
       
    // On rattache le socket au port 8080
    if (setsockopt(socket_descriptor, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&option, sizeof(option)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
       
    // On rattache le socket au port 8080
    if (bind(socket_descriptor, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(socket_descriptor, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(socket_descriptor, (struct sockaddr *)&address, 
                       (socklen_t*)&size_address))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    read_value = read( new_socket , buffer, 1024);
    printf("%s\n",buffer );
    send(new_socket , message , strlen(message) , 0 );
    printf("The LRC congratulates you\n");
    return 0;
}