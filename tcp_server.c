#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>

int main(void)
{
    // Create TCP Socket
    """ socket() yapısı

        Bağlantı için gerekli endpointi oluşturur.
        Başarılı olması durumunda bir soket tanımlayıcısı döndürür.
        Başarısız olması durumunda -1 döndürür ve errno değişkenine hata kodunu atar.

        Parametreler:
        1 : Domain
        2 : Type
        3 : Protocol

        AF_INET : IPv4 Protokolü.
        AF_INET6 : IPv6 Protokolü.

        SOCK_STREAM : TCP protokolü.
        SOCK_DGRAM : UDP protokolü.
    """

    int socket_desc;
    socket_desc = socket(AF_INET, SOCK_STREAM, 0); 

    if (socket_desc == -1)
    {
        printf("Could not create socket\n");
        return EXIT_FAILURE;
    }

    print("Socket created\n");


    // Generate socket address
    """ sockaddr_in yapısı

        sin_family : Adres ailesi. AF_INET veya AF_INET6 olabilir.

        sin_port : Port numarası.
            htons() fonksiyonu ile port numarası network byte order'a çevirilir.

        sin_addr : IP host adresi.
            s_addr : Host adresi.
    """

    struct sockaddr_in server_addr;
    server_addr.sin_family      = AF_INET;
    server_addr.s, sin_port     = htons(3000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");


    // Bind socket address
    """ bind() yapısı

        Bir soketin adresini belirler.
        Bir soketin adresi, bir adres ailesi, bir IP adresi ve bir port numarasıdır.

        Parametreler:
        1 : Soket file descriptor. ( int )
        2 : socket adresi.         ( *sockaddr )   
        3 : soceker length.        ( socklen_t )
    """

    int bind_result;
    bind_result = bind(socket_desc, (struct sockaddr *) &server_addr, sizeof(server_addr));

    if (bind_result == -1)
    {
        printf("Could not bind\n");
        return EXIT_FAILURE;
    }

    print("Bind done\n");

    // Listen for incoming connections
    """ listen() yapısı

        Bir soketin bağlantıları dinlemesini sağlar.
        Bağlantılar, accept() fonksiyonu ile kabul edilir.

        Parametreler:
        1 : Soket file descriptor. ( int )
        2 : Bağlantı sırası.       ( int )
    """

    int listen_status;
    listen_status = listen(socket_desc, 1);

    if (listen_status == -1)
    {
        printf("Could not listen\n");
        return EXIT_FAILURE;
    }

    print("Listening...\n");
    
    // Initialize client address
    struct sockaddr_in client_addr;
    socklen_t client_socklen = sizeof(client_addr);


    // Accept incoming connection
    """ accept() yapısı

        Bağlantıyı kabul eder.
        Yeni bir soket oluşturur ve bağlantıyı kabul eder.
        Yeni soket, bağlantı için kullanılır.

        Parametreler:
        1 : Soket file descriptor. ( int )
        2 : Client adresi.         ( *sockaddr )   
        3 : Client adres uzunluğu. ( *socklen_t )
    """

    int client_sock_desc;
    client_sock_desc = accept(socket_desc, (struct sockaddr *) &client_addr, &client_socklen);

    if(client_sock_desc == -1)
    {
        printf("Could not accept connection\n");
        return EXIT_FAILURE;
    }

    print("Connection accepted\n");


    // allocate memory space for incoming message
    """ memset() yapısı

        Bir bellek bloğunu belirli bir değerle doldurur.

        Parametreler:
        1 : Destination ( *char )
        2 : Değer.        ( char )
        3 : Boyut.        ( int )
    """

    char client_message[1024];
    memset(client_message, '\0', sizeof(client_message));
  

    // Receive message from client
    """ recv() yapısı

        Bir soketten veri alır.

        Parametreler:
        1 : Soket file descriptor. ( int )
        2 : Buffer.                ( *void )
        3 : Buffer length.         ( size_t )
        4 : Flags.                 ( int )
    """

    int recv_status;
    recive_status = recv(client_sock_desc, client_message, sizeof(client_message), 0);

    if(recv_status == -1)
    {
        printf("Could not receive message\n");
        return EXIT_FAILURE;
    }
    
    printf("Client message: %s\n", client_message);


    // prepare the answer
    char server_message[] = "Hello from server\n";

    // Send message to client
    """ send() yapısı

        Bir sokete veri gönderir.

        Parametreler:
        1 : Soket file descriptor. ( int )
        2 : Buffer.                ( *void )
        3 : Buffer length.         ( size_t )
        4 : Flags.                 ( int )
    """

    int send_status;
    send_status = send(client_sock_desc, server_message, sizeof(server_message), 0); 

    if(send_status == -1)
    {
        printf("Could not send message\n");
        return EXIT_FAILURE;
    }

    printf("Message sent\n");

    // Close the sockets
    close(client_sock_desc);
    close(socket_desc);

    return EXIT_SUCCESS;
}