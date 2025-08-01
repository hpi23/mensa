#include "sprache/crates/hpi-transpiler-c/libSAP/dynstring/dynstring.h"
#include "sprache/crates/hpi-transpiler-c/libSAP/libList.h"
#include "sprache/crates/hpi-transpiler-c/libSAP/list/list.h"
#include "sprache/crates/hpi-transpiler-c/output.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void send_raw_response(int client_fd, const char *data, size_t length) {
  char header[BUFFER_SIZE];
  snprintf(header, sizeof(header),
           "HTTP/1.1 200 OK\r\n"
           "Content-Type: application/octet-stream\r\n"
           "Content-Length: %zu\r\n"
           "Connection: close\r\n\r\n",
           length);

  // Send HTTP header
  write(client_fd, header, strlen(header));

  // Send raw payload (can include null bytes or shell escapes)
  write(client_fd, data, length);
}

int main(int argc, char **argv) {
  int server_fd, client_fd;
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  char buffer[BUFFER_SIZE] = {0};

  // HPI setup.
  type_descriptor_setup();
  __hpi_internal_init_libSAP(argc, argv, true, true);
  global_variable_setup();
  bewerbung();
  einschreibung(__hpi_internal_generate_matrikelnummer());

  // Create socket (IPv4, TCP)
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // Bind socket to IP/Port
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY; // Any IP
  address.sin_port = htons(PORT);

  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // Listen for connections
  if (listen(server_fd, 3) < 0) {
    perror("listen failed");
    exit(EXIT_FAILURE);
  }

  printf("Server listening on port %d...\n", PORT);

  while (1) {
    // Accept incoming connection
    if ((client_fd = accept(server_fd, (struct sockaddr *)&address,
                            (socklen_t *)&addrlen)) < 0) {
      perror("accept failed");
      exit(EXIT_FAILURE);
    }

    // Read client request
    read(client_fd, buffer, BUFFER_SIZE);
    printf("Request:\n%s\n", buffer);

    DynString *prog_name = dynstring_from("SERVER");
    DynString *location = dynstring_from("hpi");

    ListNode *args = list_new();
    __hpi_internal_list_push(args, &prog_name);
    __hpi_internal_list_push(args, &location);

    DynString *program_output = Haupt1(args);
    char *res = dynstring_as_cstr(program_output);
    send_raw_response(client_fd, res, strlen(res) - 1);
    free(res);
    dynstring_free(program_output);
    list_free(args);
    dynstring_free(location);
    dynstring_free(prog_name);

    close(client_fd); // Close client socket
  }

  return 0;
}
