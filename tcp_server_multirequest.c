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

    print("Socket created\n");


    // Generate socket address
    struct sockaddr_in server_addr;
    server_addr.sin_family      = AF_INET;
    server_addr.s, sin_port     = htons(3000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");


    // Bind socket address
    int bind_result;
    bind_result = bind(socket_desc, (struct sockaddr *) &server_addr, sizeof(server_addr));

    if (bind_result == -1)
    {
        printf("Could not bind\n");
        return EXIT_FAILURE;
    }

    print("Bind done\n");

    // Listen for incoming connections
    int listen_status;
    listen_status = listen(socket_desc, 5);

    if (listen_status == -1)
    {
        printf("Could not listen\n");
        return EXIT_FAILURE;
    }

    print("Listening...\n");
    
    // Initialize client address
    struct sockaddr_in client_addr;
    socklen_t client_socklen = sizeof(client_addr);

    int client_sock_desc;
    char client_message[1024];
    int recv_status;
    char server_message[] = "Hello from server\n";
    int send_status;

    while (1)
    {
        // Accept incoming connection
        client_sock_desc = accept(socket_desc, (struct sockaddr *) &client_addr, &client_socklen);

        if(client_sock_desc == -1)
        {
            printf("Could not accept connection\n");
        }

        print("Connection accepted\n");


        // allocate memory space for incoming message      
        memset(client_message, '\0', sizeof(client_message));
    

        // Receive message from client
        recive_status = recv(client_sock_desc, client_message, sizeof(client_message), 0);

        if(recv_status == -1)
        {
            printf("Could not receive message\n");
        }

        printf("Client message: %s\n", client_message);


        // Send message to client
        send_status = send(client_sock_desc, server_message, sizeof(server_message), 0); 

        if(send_status == -1)
        {
            printf("Could not send message\n");
        }

        printf("Message sent\n");

        // Close the sockets
        close(client_sock_desc);
    }
    
    close(socket_desc);

    return EXIT_SUCCESS;
}