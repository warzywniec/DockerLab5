#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#ifndef VERSION
#define VERSION "DEV"
#endif

const char* get_ip() {
    static char ip[INET_ADDRSTRLEN];
    struct sockaddr_in sa;
    struct hostent *he;

    char hostname[1024];
    gethostname(hostname, sizeof(hostname));

    he = gethostbyname(hostname);
    if (he == NULL) {
        return "unknown";
    }

    inet_ntop(AF_INET, he->h_addr_list[0], ip, sizeof(ip));
    return ip;
}

void serve_forever() {
    int server_fd, client_fd;
    struct sockaddr_in server, client;
    socklen_t client_len = sizeof(client);
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket");
        exit(1);
    }

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    if (bind(server_fd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        perror("bind");
        exit(1);
    }

    listen(server_fd, 5);

    printf("Listening on port 8080...\n");

    while (1) {
        client_fd = accept(server_fd, (struct sockaddr*)&client, &client_len);
        if (client_fd < 0) {
            perror("accept");
            continue;
        }

        read(client_fd, buffer, sizeof(buffer)); 

        char hostname[1024];
        gethostname(hostname, sizeof(hostname));
        const char* ip = get_ip();

        char response[1024];
        snprintf(response, sizeof(response),
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain\r\n\r\n"
            "Adres IP: %s\nNazwa hosta: %s\nWersja aplikacji: %s\n",
            ip, hostname, VERSION);

        write(client_fd, response, strlen(response));
        close(client_fd);
    }
}

int main() {
    serve_forever();
    return 0;
}
