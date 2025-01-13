#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h> 

#define PORT 8080
#define BUFFER_SIZE 1024
#define MAX_ACCOUNTS 100
#define MAX_OPERATIONS 10

typedef struct {
    char id_client[50];
    char id_compte[50];
    char password[50];
    double balance;
    char operations[MAX_OPERATIONS][BUFFER_SIZE];
    char operation_dates[MAX_OPERATIONS][50];
    int operation_count;
    char last_operation_date[50];
} Account;

Account accounts[MAX_ACCOUNTS];
int account_count = 0;

void handle_client(int client_socket);
void handle_error(const char *message);
void add_account(const char *id_client, const char *id_compte, const char *password, double initial_balance);
Account* find_account(const char *id_client, const char *id_compte, const char *password);
void add_operation(Account *account, const char *operation);
int handle_ajout(const char *id_client, const char *id_compte, const char *password, double somme);
int handle_retrait(const char *id_client, const char *id_compte, const char *password, double somme);
void handle_solde(int client_socket, const char *id_client, const char *id_compte, const char *password);
void handle_operations(int client_socket, const char *id_client, const char *id_compte, const char *password);

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_address, client_address;
    socklen_t client_address_len = sizeof(client_address);

    // Initialize some accounts (assuming account creation is already done)
    add_account("Inessa", "123", "pass1", 0.0);
    add_account("Philip", "456", "pass2", 520.0);
    add_account("Marie", "789", "pass3", 2200.0);

    // 1. creer le socket : AF_INET: IPv4, SOCK_STREAM: TCP, 0: IP
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        handle_error("Socket creation failed");
    }

    //2. server address proporties : sin_family: Address family (IPv4), sin_addr: IP address, sin_port: Port number
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);


    // 3. bind the socket to the server address
    if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        handle_error("Bind failed");
    }

    // 4. listen for connections
    if (listen(server_socket, 5) < 0) {
        handle_error("Listen failed");
    }

    printf("Server is listening on port %d...\n", PORT);

    // 5. Accepter une connexion client
    while (1) {
        client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_len);
        if (client_socket < 0) {
            perror("Failed to accept client connection");
            continue;
        }
        printf("Client connected: %s:%d\n",
               inet_ntoa(client_address.sin_addr),
               ntohs(client_address.sin_port));

        handle_client(client_socket);

        printf("Client disconnected: %s:%d\n",
               inet_ntoa(client_address.sin_addr),
               ntohs(client_address.sin_port));
    }

    // 6. Close the server socket
    close(server_socket);
    return 0;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    int bytes_received;

    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_received] = '\0'; // Null-terminate the received string
        printf("Received from client: %s\n", buffer);

        // Parse the command
        char command[BUFFER_SIZE];
        char id_client[50], id_compte[50], password[50];
        double somme = 0.0;
        int parsed_args = sscanf(buffer, "%s %s %s %s %lf", command, id_client, id_compte, password, &somme);

        if (strcmp(command, "AJOUT") == 0) {
            if (parsed_args == 5 && somme != 0) {
                if (handle_ajout(id_client, id_compte, password, somme)) {
                    const char *response = "OK\n";
                    send(client_socket, response, strlen(response), 0);
                } else {
                    const char *response = "KO\n";
                    send(client_socket, response, strlen(response), 0);
                }
            } else {
                const char *response = "KO\n";
                send(client_socket, response, strlen(response), 0);
            }
        } else if (strcmp(command, "RETRAIT") == 0) {
            if (parsed_args == 5) {
                if (handle_retrait(id_client, id_compte, password, somme)) {
                    const char *response = "OK\n";
                    send(client_socket, response, strlen(response), 0);
                } else {
                    const char *response = "KO\n";
                    send(client_socket, response, strlen(response), 0);
                }
            } else {
                const char *response = "KO\n";
                send(client_socket, response, strlen(response), 0);
            }
        } else if (strcmp(command, "SOLDE") == 0) {
            if (parsed_args == 4) {
                handle_solde(client_socket, id_client, id_compte, password);
            } else {
                const char *response = "Invalid command: missing arguments for SOLDE\n";
                send(client_socket, response, strlen(response), 0);
            }
        } else if (strcmp(command, "OPERATIONS") == 0) {
            if (parsed_args == 4) {
                handle_operations(client_socket, id_client, id_compte, password);
            } else {
                const char *response = "Invalid command: missing arguments for OPERATIONS\n";
                send(client_socket, response, strlen(response), 0);
            }
        } else {
            const char *response = "KO\n";
            send(client_socket, response, strlen(response), 0);
        }
    }

    if (bytes_received < 0) {
        perror("Failed to read from client");
    }

    close(client_socket);
}



void add_account(const char *id_client, const char *id_compte, const char *password, double initial_balance) {
    if (account_count < MAX_ACCOUNTS) {
        strcpy(accounts[account_count].id_client, id_client);
        strcpy(accounts[account_count].id_compte, id_compte);
        strcpy(accounts[account_count].password, password);
        accounts[account_count].balance = initial_balance;
        accounts[account_count].operation_count = 0;
        account_count++;
    }
}

Account* find_account(const char *id_client, const char *id_compte, const char *password) {
    for (int i = 0; i < account_count; i++) {
        if (strcmp(accounts[i].id_client, id_client) == 0 &&
            strcmp(accounts[i].id_compte, id_compte) == 0 &&
            strcmp(accounts[i].password, password) == 0) {
            return &accounts[i];
        }
    }
    return NULL;
}

void add_operation(Account *account, const char *operation) {
    if (account->operation_count < MAX_OPERATIONS) {
        strcpy(account->operations[account->operation_count], operation);
    } else {
        for (int i = 1; i < MAX_OPERATIONS; i++) {
            strcpy(account->operations[i - 1], account->operations[i]);
            strcpy(account->operation_dates[i - 1], account->operation_dates[i]);
        }
        strcpy(account->operations[MAX_OPERATIONS - 1], operation);
    }

    // Update the date of the operation
    time_t now = time(NULL);
    strftime(account->operation_dates[account->operation_count], sizeof(account->operation_dates[account->operation_count]), "%Y-%m-%d %H:%M:%S", localtime(&now));
    account->operation_count++;
    if (account->operation_count > MAX_OPERATIONS) {
        account->operation_count = MAX_OPERATIONS;
    }

    // Update the date of the last operation
    strcpy(account->last_operation_date, account->operation_dates[account->operation_count - 1]);
}

int handle_ajout(const char *id_client, const char *id_compte, const char *password, double somme) {
    Account *account = find_account(id_client, id_compte, password);
    if (account && somme > 0) {
        account->balance += somme;
        char operation[BUFFER_SIZE];
        snprintf(operation, BUFFER_SIZE, "AJOUT %.2f€", somme);
        add_operation(account, operation);
        return 1; // Success
    } else {
        return 0; // Failure
    }
}

int handle_retrait(const char *id_client, const char *id_compte, const char *password, double somme) {
    Account *account = find_account(id_client, id_compte, password);
    if (account && somme > 0) {
        if (account->balance >= somme) {
            account->balance -= somme;
            char operation[BUFFER_SIZE];
            snprintf(operation, BUFFER_SIZE, "RETRAIT %.2f€", somme);
            add_operation(account, operation);
            return 1; // Success
        } else {
            return 0; // Failure
        }
    } else {
        return 0; // Failure
    }
}

void handle_solde(int client_socket, const char *id_client, const char *id_compte, const char *password) {
    Account *account = find_account(id_client, id_compte, password);
    if (account) {
        char response[BUFFER_SIZE];
        snprintf(response, BUFFER_SIZE, "RES_SOLDE %.2f€ %s\n", account->balance, account->last_operation_date);
        send(client_socket, response, strlen(response), 0);
    } else {
        const char *response = "Invalid command\n";
        send(client_socket, response, strlen(response), 0);
    }
}

void handle_operations(int client_socket, const char *id_client, const char *id_compte, const char *password) {
    Account *account = find_account(id_client, id_compte, password);
    if (account) {
        char response[BUFFER_SIZE] = "RES_OPERATIONS\n";
        for (int i = 0; i < account->operation_count; i++) {
            char operation[BUFFER_SIZE];
            snprintf(operation, BUFFER_SIZE, "%s %s", account->operations[i], account->operation_dates[i]);
            strcat(response, operation);
            strcat(response, "\n");
        }
        send(client_socket, response, strlen(response), 0);
    } else {
        const char *response = "KO\n";
        send(client_socket, response, strlen(response), 0);
    }
}

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}