#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>


int main(int argc, char *argv[])
{
   // Create a UDP socket
    int socket_desc;
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }

    printf("Socket created\n");

    // Generate the server address
    struct sockaddr_in server_addr;
    socklen_t server_addr_size = sizeof(server_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    //  Create a message
    char client_message[1024];
    printf("Enter message: ");
    fgets(client_message, 1024, stdin);
    strtok(client_message, "\n");

    // Send the message to the server
    int send_result;
    send_result = sendto(socket_desc, client_message, strlen(client_message), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));

    if send_result == -1)
    {
        printf("Could not send message");
        return EXıT_FAILURE;
    }

    printf("Message sent\n");

    // Allocate memory for the server response
    char server_message[1024];
    memset(server_message, '\0', sizeof(server_message));

    // Receive the server's response
    int receive_result;
    receive_result = recvfrom(socket_desc, server_message, sizeof(server_message), 0, (struct sockaddr *)&server_addr, &server_addr_size);

    if receive_result == -1)
    {
        printf("Could not receive message");
        return EXIT_FAILURE;
    }

    printf("Server response: %s\n", server_message);

    return EXIT_SUCCESS;
}