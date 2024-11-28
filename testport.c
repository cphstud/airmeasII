#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
	int PORT;
	PORT = atoi(argv[1]);
	int server_fd, new_socket;
	struct sockaddr_in address;
	int addrlen = sizeof(address);

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
		perror("Socket failed");
		exit(EXIT_FAILURE);
	}

	// Set up the address structure
	address.sin_family = AF_INET; // IPv4
	address.sin_addr.s_addr = INADDR_ANY; // Bind to any available address
	address.sin_port = htons(PORT); // Convert port to network byte order

	// Bind the socket to the specified port
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
		perror("Bind failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	printf("Listening on port %d...\n", PORT);

	// Start listening for incoming connections
	if (listen(server_fd, 3) < 0) {
		perror("Listen failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	// Accept a connection (this blocks until a client connects)
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen)) < 0) {
		perror("Accept failed");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	printf("Connection established with client!\n");

	// Cleanup
	close(new_socket);
	close(server_fd);
	return 0;
}

