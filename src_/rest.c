#include <api.h>
#include <struct.h>
size_t i = 0;
DataSet dataSet;

void print_json_aux(json_t *element) {
	switch (json_typeof(element)) {
		case JSON_OBJECT:
			print_json_object(element);
			break;
		case JSON_ARRAY:
			print_json_array(element);
			break;
		case JSON_STRING:
			print_json_string(element);
			break;
		case JSON_INTEGER:
			print_json_integer(element);
			break;
		case JSON_REAL:
			print_json_real(element);
			break;
		case JSON_TRUE:
			print_json_true(element);
			break;
		case JSON_FALSE:
			print_json_false(element);
			break;
		case JSON_NULL:
			print_json_null(element);
			break;
		default:
			fprintf(stderr, "unrecognized JSON type %d\n", json_typeof(element));
	}
}
void parse_json(json_t *element){
	json_t *doc;
	const char *key;
	json_t *value;
	json_t *tmp;
	if((doc = json_object_get(element, "documents"))!= NULL){
		printf("%s\n\n", json_typeof(doc));
		if(json_typeof(doc) == JSON_ARRAY){
			json_array_foreach(doc, i, tmp){
				json_object_foreach(tmp, key, value){
					if(!strcmp(key, "address_name"))
						strcpy(dataSet.documents[i].address_name ,json_string_value(value));
					printf("value: %s\n", json_string_value(value));
					printf("documents JSON Key: \"%s\"\n", key);
				}
			}
		}
	}
	printf("doc : %s", dataSet.documents[i].address_name);


}


void print_json_object(json_t *element) {
	size_t size;
	const char *key;
	json_t *value;
	json_t *result;
	size = json_object_size(element);

	json_object_foreach(element, key, value) {
		if(!strcmp(key, "address_name"))
			strcpy(dataSet.documents[i].address_name ,json_string_value(value));
		else if(!strcmp(key, "category_group_code"))
			strcpy(dataSet.documents[i].category_group_code ,json_string_value(value));
		else if(!strcmp(key, "category_group_name"))
			strcpy(dataSet.documents[i].category_group_name ,json_string_value(value));
		else if(!strcmp(key, "cetegory_name"))
			strcpy(dataSet.documents[i].category_name ,json_string_value(value));
		else if(!strcmp(key, "distance"))
			strcpy(dataSet.documents[i].distance ,json_string_value(value));
		else if(!strcmp(key, "id"))
			strcpy(dataSet.documents[i].id, json_string_value(value));
		else if(!strcmp(key, "phone"))
			strcpy(dataSet.documents[i].phone, json_string_value(value));
		else if(!strcmp(key, "place_name"))
			strcpy(dataSet.documents[i].place_name, json_string_value(value));
		else if(!strcmp(key, "place_url"))
			strcpy(dataSet.documents[i].place_url, json_string_value(value));
		else if(!strcmp(key, "road_address_name"))
			strcpy(dataSet.documents[i].road_address_name, json_string_value(value));
		else if(!strcmp(key, "x"))
			strcpy(dataSet.documents[i].x, json_string_value(value));
		else if(!strcmp(key, "y"))
			strcpy(dataSet.documents[i].y, json_string_value(value));
		else if(!strcmp(key, "is_end"))
			dataSet.meta.is_end = json_boolean_value(value);
		else if(!strcmp(key, "pageable_count"))
			dataSet.meta.pageable_count = json_integer_value(value);
		else if(!strcmp(key, "keyword"))
			strcpy(dataSet.meta.same_name.keyword , json_string_value(value));
		else if(!strcmp(key, "region")){
			size = json_array_size(value);
			for(i = 0; i< size; i++){
				strcpy(dataSet.meta.same_name.regions[i].region, json_array_get(value, i));
			}
		}
		else if(!strcmp(key, "selected_region"))
			strcpy(dataSet.meta.same_name.selected_region , json_string_value(value));
		else if(!strcmp(key, "total_count"))
			dataSet.meta.total_count = json_integer_value(value);


		printf("documents JSON Key: \"%s\"\n", key);
		print_json_aux(value);
	}
}

void print_json_array(json_t *element) {
	size_t size = json_array_size(element);

	printf("JSON Array of %lld element:\n", (long long)size);
	for (i = 0; i < size; i++) {
		print_json_aux(json_array_get(element, i));
	}
}

void print_json_string(json_t *element) {
	printf("JSON String: \"%s\"\n", json_string_value(element));
}

json_t *load_json(const char *text) {
	json_t *root;
	json_error_t error;

	root = json_loads(text, 0, &error);

	if (root) {
		return root;
	} else {
		fprintf(stderr, "json error on line %d: %s\n", error.line, error.text);
		return (json_t *)0;
	}
}
void print_json_null(json_t *element, int indent) {
	(void)element;
	printf("JSON Null\n");
}
void print_json_integer(json_t *element) {
	printf("JSON Integer: \"%" JSON_INTEGER_FORMAT "\"\n", json_integer_value(element));
}

void print_json_real(json_t *element) {
	printf("JSON Real: %f\n", json_real_value(element));
}

void print_json_true(json_t *element) {
	(void)element;
	printf("JSON True\n");
}

void print_json_false(json_t *element) {
	(void)element;
	printf("JSON False\n");
}


int main(int argc, char *argv[])
{
	//char message_fmt[] = "GET %s HTTP/1.1\r\nHost: %s\r\nAuthorization: KakaoAK %s\r\nConnection: close\r\n\r\n"; 
//	char line[MAX_CHARS];
	char *seg;
	char message_fmt[] = "GET %s HTTP/1.0\r\nHost: %s\r\nAuthorization: KakaoAK %s\r\n\r\n";
	char str[READLEN];
	char buf[READLEN];
	char message[MSGLEN];
	int s, n, left_len, sent_len, recv_len;
	struct sockaddr_in server_addr;
	struct hostent *host;
	char line[MAX_CHARS];
	int port;
	int byte;
	int i= 0;
	char *token;
	if(argc < 4) {
		printf("usage : %s <Host> <Resource> <API_KEYS>\n", argv[0]);
		printf("ex) dapi.kakao.com /v2/local/search/keyword.json?query=<query> <API_KEYS>\n");
		return -1;
	}

	if((host=gethostbyname(argv[1]))== NULL){
		printf("gethostbyname error\n");
		exit(-1);
	}
	if((s=socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		printf("can not create socket\n");
		return -1;
	}

	sprintf(message, message_fmt,argv[2],argv[1], argv[3]);
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	memcpy(&server_addr.sin_addr.s_addr, host->h_addr, host->h_length);
	server_addr.sin_port=htons(80);

	if(connect(s, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
		printf("can not connect");
		return -1;
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

	json_t *root = load_json(line);
	if(root){
		print_json_aux(root);
		//parse_json(root);
		json_decref(root);
	}
	printf("aaaaaa%s\n", dataSet.documents[0].address_name);

	printf("\n");

	return 0;
}

