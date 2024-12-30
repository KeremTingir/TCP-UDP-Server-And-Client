#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>

int main(void)
{
    // Create TCP Socket
    int socket_desc;
    socket_desc = socket(AF_INET, SOCK_STREAM, 0); 

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

    // Connect to server
    """ connect() yapısı

        Bir soketi belirtilen adres ve port numarasına bağlar.

        Parametreler:
        1 : Soket file descriptor. ( int )
        2 : sockaddr yapısı.       ( *struct sockaddr )
        3 : sockaddr yapısının boyutu. ( socklen_t )
    """
    int connect_result;
    connect_result = connect(socket_desc, (struct sockaddr *) &server_addr, sizeof(server_addr));

    if (connect_result == -1)
    {
        printf("Could not connect\n");
        return EXIT_FAILURE;
    }

    printf("Connected\n");

    // compose the message to send
    char client_message[1024];
    printf("Enter message: ");
    fgets(client_message, sizeof(client_message), stdin);
    strtok(client_message, "\n");

    // Send message to server
    int send_status;
    send_status = send(socket_desc, client_message, strlen(client_message), 0);

    if (send_status == -1)
    {
        printf("Could not send message\n");
        return EXIT_FAILURE;
    }

    printf("Message sent\n");

    // Allocate space for messages from the server
    char server_message[1024];
    memset(server_message, '\0', sizeof(server_message));

    // Receive message from server
    int recv_status;
    recv_status = recv(socket_desc, server_message, sizeof(server_message), 0);

    if (recv_status == -1)
    {
        printf("Could not receive message\n");
        return EXIT_FAILURE;
    }

    printf("Server message: %s\n", server_message);
    




    return EXIT_FAILURE;

}