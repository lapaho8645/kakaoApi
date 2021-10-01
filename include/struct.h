#define DEFAULT_SIZE 512
#define COMM_MAX 5
typedef struct Document_t {
	char        id                  [DEFAULT_SIZE]  ;
	char        place_name          [DEFAULT_SIZE]  ;
	char        category_group_code [DEFAULT_SIZE]  ;
	char        category_group_name [DEFAULT_SIZE]  ;
	char        category_name       [DEFAULT_SIZE]  ;
	char        phone               [DEFAULT_SIZE]  ;
	char        address_name        [DEFAULT_SIZE]  ;
	char        road_address_name   [DEFAULT_SIZE]  ;
	char        x                   [DEFAULT_SIZE]  ;
	char        y                   [DEFAULT_SIZE]  ;
	char        place_url           [DEFAULT_SIZE]  ;
	char        distance            [DEFAULT_SIZE]  ;
} Document ;

typedef struct Region_t {
	char        region              [DEFAULT_SIZE]  ;
} Region ;

typedef struct SameName_t {
	Region      regions             [COMM_MAX]      ;
	char        keyword             [DEFAULT_SIZE]  ;
	char        selected_region     [DEFAULT_SIZE]  ;
} SameName ;

typedef struct Meta_t {
	int         total_count                         ;
	int         pageable_count                      ;
	short       is_end                              ;
	SameName    same_name                           ;
} Meta ;

typedef struct DataSet_t {
	Document    documents           [COMM_MAX]      ;
	Meta        meta                                ;
} DataSet ;

