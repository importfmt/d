#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int get_status(int r, const char* status_info);
int create_socket();
struct sockaddr_in create_protocol_cluster();
void bind_socket(int socket, struct sockaddr_in addr);
void create_listener(int socket);
void handle_request(int socket);

int main(void)
{
	int server_socket = create_socket();
	struct sockaddr_in addr = create_protocol_cluster();
	bind_socket(server_socket, addr);
	create_listener(server_socket);
	struct sockaddr_in cAddr;
	int cAddr_len = sizeof(cAddr);
	while(1)
	{
		int client_socket = accept(server_socket, (struct sockaddr*)&cAddr, (socklen_t*)&cAddr_len);
		if(get_status(client_socket, "Connection") == -1) return;
		handle_request(client_socket);
	}
	close(server_socket);

	return 0;
}

int get_status(int r, const char* status_info)
{
	if( r == -1)
	{
		printf("ERROR:%s failed.\n", status_info);
		return -1;
	}
	printf("INFO:%s successful.\n", status_info);
	return 0;
}

int create_socket()
{
	int server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(get_status(server_socket, "Create socket") == -1) return;
	return server_socket;
}

struct sockaddr_in create_protocol_cluster()
{
	struct sockaddr_in addr;
	bzero(&addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(80);
	addr.sin_addr.s_addr = inet_addr("0.0.0.0");
	return addr;
}

void bind_socket(int socket,struct sockaddr_in addr)
{
	int r = bind(socket, (struct sockaddr*)&addr, sizeof(addr));
	if(get_status(r, "Bind") == -1) return;
}

void create_listener(int socket)
{
	int r = listen(socket, 10);
	if(get_status(r, "Listen") == -1) return;
}

void handle_request(int socket)
{
	char buff[1024*1024] = {0};
	int nread = read(socket,buff, sizeof(buff));
	printf("%s", buff);

	char filename[10] = {0};
	sscanf(buff, "GET /%s", filename);
	printf("INFO: Request file is %s\n", filename);

	char *mime = NULL;
	if(strstr(filename, ".html"))   mime = "text/html";
	else if(strstr(filename, "image/png")) mime = "image/png";
	else if(strstr(filename, "image/jpeg")) mime = "image/jpeg";
	else if(strstr(filename, ".css")) mime = "text/css";

	char response[1024*1024] = {0};
	sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\n\r\n", mime);
	int head_len = strlen(response);


	int file = open(filename, O_RDONLY);
	int file_len = read(file, response + head_len, sizeof(response) - head_len);

	write(socket, response, head_len + file_len);
	close(socket);
}


