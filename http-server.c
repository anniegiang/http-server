#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>

#include <fcntl.h> // for open
#include <unistd.h> // for close 

#include <netinet/in.h>
#include <arpa/inet.h>

// Implementation of a HTTP server 
int main() {
	// the file that the client will request and the server will serve
	FILE *html_data;
	// opens a file called index.html and returns an object
	html_data = fopen("index.html", "r");
	
	// stores the html object into a string
	char response_data[1024];
	// read the file
	fgets(response_data, 1024, html_data);

	// tell client the status_code from request
	char http_header[2048] = "HTTP/1.1 200 OK\r\n\n";

	// add the status code into index.html
	strcat(http_header, response_data);

	// create a socket for the server
	int server_socket;

	// AF_INET = internet domain, SOCK_STREAM = TCP, 
	server_socket = socket(AF_INET, SOCK_STREAM, 0);

	// define sock address = where the server will serve data
	struct sockaddr_in server_address;	
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(8001);
	server_address.sin_addr.s_addr = INADDR_ANY;
	
	// bind socket to a port
	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	// listen to connections from the socket
	listen(server_socket, 5);

	// create a socket for the client
	int client_socket;

	// create an infinite loop so that the server can listen to requets
	while(1) {
		// accept the client's request
		client_socket = accept(server_socket, NULL, NULL); 
		// send data back to the client
		send(client_socket, http_header, sizeof(http_header), 0);
		// close the client socket
		// close(client_socket);
	}

	return 0;
}