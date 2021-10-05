#include <api.h>

json_t *load_json(const char *text) {	
	json_t			 *root;
	json_error_t 	 error;

	root = json_loads(text, 0, &error);

	if (root) {
		return root;
	} else {
		fprintf(stderr, "json error on line %d: %s\n", error.line, error.text);
		return (json_t *)0;
	}
}

void error_print(char *str){
	printf("%s\n", str);
	exit(1);
}

int main(int argc, char *argv[])
{
	char 		line		[MAX_CHARS];	

	/* 1. Connect, Request, Response	*/
	strcpy(line ,print_line(argc, argv)); //print_line : 웹서버와 연결, 요청 후 응답에서 json부분을 반환

	/* 2. Make Json File				*/
	json_t *root = load_json(line);

	/* 3. Json Parsing					*/
	if(root){
		parse_json(root);	//json parsing 후DataSet 구조체 변수에 값 대입
		json_decref(root);
	}

	printf("\n");

	return 0;
}

