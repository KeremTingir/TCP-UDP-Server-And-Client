#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>


int main(void)
{
    // Create UDP Socket
    int socket_desc;
    socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); 

    if (socket_desc == -1)
    {
        printf("Could not create socket\n");
        return EXIT_FAILURE;
    }

    printf("Socket created\n");

    // Generate socket address
    struct sockaddr_in server_addr;
    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(3000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");


    int bind_result;
    bind_result = bind(socket_desc, (struct sockaddr *) &server_addr, sizeof(server_addr));

    if (bind_result == -1)
    {
        printf("Could not bind\n");
        return EXIT_FAILURE;
    }

    printf("Port: %d\n", ntohs(server_addr.sin_port));
    printf("Bind done\n");
    
    // Initialize client address
    struct sockaddr_in client_addr;
    socklen_t client_addr_size = sizeof(client_addr);

    //allocate memory for client address
    char client_message[1024];
    memset(client_message, '\0', sizeof(client_message));

    // Receive message from client
    int recv_status;
    recv_status = recvfrom(socket_desc, client_message, sizeof(client_message), 0, (struct sockaddr *) &client_addr, &client_addr_size);

    if (recv_status == -1)
    {
        printf("Could not receive message\n");
        return EXIT_FAILURE;
    }

    printf("Client message: %s\n", client_message);

    // Send message to client
    char server_message[1024] = "Hello from server";

    int send_status;
    send_status = sendto(socket_desc, server_message, sizeof(server_message), 0, (struct sockaddr *) &client_addr, client_addr_size);
    
    if (send_status == -1)
    {
        printf("Could not send message\n");
        return EXIT_FAILURE;
    }

    printf("Message sent\n");

    

    return EXIT_SUCCESS;
}