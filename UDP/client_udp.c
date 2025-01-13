#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_error(const char *message);
void interact_with_server(int socket, struct sockaddr_in *server_address);

int main() {
    int client_socket;
    struct sockaddr_in server_address;

    // Step 1: Create the socket
    if ((client_socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        handle_error("Socket creation failed");
    }

    // Step 2: Configure server address
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
        handle_error("Invalid address or address not supported");
    }

    printf("Ready to communicate with the server.\n");

    // Step 3: Interact with the server
    interact_with_server(client_socket, &server_address);

    // Step 4: Close the socket
    printf("Disconnecting from the server.\n");
    close(client_socket);
    return 0;
}

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

void interact_with_server(int socket, struct sockaddr_in *server_address) {
    char buffer[BUFFER_SIZE];
    char request[BUFFER_SIZE];
    socklen_t server_address_len = sizeof(*server_address);

    while (1) {
        // Get user input
        printf("Enter your request (or type 'exit' to quit): ");
        fgets(request, BUFFER_SIZE, stdin);

        // Check for exit condition
        if (strncmp(request, "exit", 4) == 0) {
            printf("Exiting client.\n");
            break;
        }

        // Send the request to the server
        if (sendto(socket, request, strlen(request), 0, (struct sockaddr *)server_address, server_address_len) < 0) {
            handle_error("Failed to send request");
        }

        // Receive the response from the server
        int bytes_received = recvfrom(socket, buffer, BUFFER_SIZE - 1, 0, (struct sockaddr *)server_address, &server_address_len);
        if (bytes_received < 0) {
            handle_error("Failed to receive response");
        }

        buffer[bytes_received] = '\0'; // Null-terminate the received string

        // Process the server response
        if (strncmp(buffer, "OK", 2) == 0) {
            printf("OK\n");
        } else if (strncmp(buffer, "KO", 2) == 0) {
            printf("KO\n");
        } else if (strncmp(buffer, "RES_SOLDE", 9) == 0) {
            printf("RES_SOLDE:\n%s\n", buffer + 10); // Skip "RES_SOLDE "
        } else if (strncmp(buffer, "RES_OPERATIONS", 14) == 0) {
            printf("RES_OPERATIONS:\n%s\n", buffer + 15); // Skip "RES_OPERATIONS "
        } else {
            printf("%s\n", buffer);
        }
    }
}