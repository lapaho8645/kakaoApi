#include <stdio.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <jansson.h>

#define MSGLEN 1024
#define READLEN 4096
#define DEFAULT_SIZE 512
#define COMM_MAX     5
#define MAX_CHARS (1024 * 8)

