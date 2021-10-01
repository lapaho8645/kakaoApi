#include <api.h>

int sock(char *argv[]){


char *print_line(int argc, char *argv[]){
	char *seg;
	char message_fmt[] = "GET %s HTTP/1.0\r\nHost: %s\r\nAuthorization: KakaoAK %s\r\n\r\n";
	char str[READLEN];
	char buf[READLEN];
	char message[MSGLEN];
	int s, n, left_len, sent_len, recv_len;
	struct sockaddr_in server_addr;
	struct hostent *host;
	static char line[MAX_CHARS];
	int port;
	int byte;
	int i= 0;
	char *token;
	if(argc < 4) {
		printf("usage : %s <Host> <Resource> <API_KEYS>\n", argv[0]);
		error_print("ex) dapi.kakao.com /v2/local/search/keyword.json?query=<query> <API_KEYS>\n");
		
	}

	if((host=gethostbyname(argv[1]))== NULL){
		printf("gethostbyname error\n");
		exit(-1);
	}
	if((s=socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		error_print("can not create socket\n");
	}

	sprintf(message, message_fmt,argv[2],argv[1], argv[3]);
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	memcpy(&server_addr.sin_addr.s_addr, host->h_addr, host->h_length);
	server_addr.sin_port=htons(80);

	if(connect(s, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
		error_print("can not connect");
	}
	left_len = strlen(message);
	sent_len = 0;
	do{
		byte = write(s, message+sent_len, left_len - sent_len);
		if(byte < 0)
			printf("write error\n");
		if(byte == 0)
			break;
		sent_len += byte;
	}while(sent_len < left_len);

	memset(buf, 0, sizeof(buf));
	memset(str, 0, sizeof(str));
	memset(line, 0, sizeof(line));


	do{
		memset(buf, 0, sizeof(buf));
		n = read(s, buf, READLEN);
		fprintf(stdout,"%s ", buf);
		if(n < 0)
			printf("read error\n");
		if(n == 0)
			break;
		sprintf(str, "%s%s", str, buf);
	}while(1);

	seg = strstr(str, "{");
	sprintf(line, "%s", seg);
	close(s);
	return line;
}

