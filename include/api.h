#include <stdio.h>
#include <sys/types.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <jansson.h>

#include <struct.h>

#define MSGLEN 1024
#define READLEN 4096
#define MAX_CHARS (1024 * 8)

DataSet dataSet;
extern char *print_line(int , char*[]);
extern void parse_json(json_t *);
extern void error_print(char *);

