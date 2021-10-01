#include <api.h>

void parse_json(json_t *element){
	json_t *doc;
	json_t *meTa;
	const char *key;
	const char *key2;
	json_t *value;
	json_t *tmp;
	size_t i = 0;
	if((doc = json_object_get(element, "documents"))!= NULL){
		if(json_typeof(doc) == JSON_ARRAY){
			json_array_foreach(doc, i, tmp){
				if(json_typeof(tmp) == JSON_OBJECT){
					json_object_foreach(tmp, key, value){
						if(!strcmp(key, "address_name"))
							strcpy(dataSet.documents[i].address_name, json_string_value(value));
						else if(!strcmp(key, "category_group_code"))
							strcpy(dataSet.documents[i].category_group_code ,json_string_value(value));
						else if(!strcmp(key, "category_group_name"))
							strcpy(dataSet.documents[i].category_group_name ,json_string_value(value));
						else if(!strcmp(key, "category_name"))
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
						else{
							error_print("key is invalid");
						}
					}
				}
				else{
					error_print("array value is not object");
				}
			}
		}
		else{
			error_print("documents value is not array");
		}

	}
	else{
		error_print("documents is not found");
	}
	if((meTa = json_object_get(element, "meta"))!=NULL){
		if(json_typeof(meTa) == JSON_OBJECT){
			json_object_foreach(meTa, key, tmp){
				if(!strcmp(key, "is_end"))
					dataSet.meta.is_end = json_boolean_value(value);
				else if(!strcmp(key, "pageable_count"))
					dataSet.meta.pageable_count = json_integer_value(value);
				else if(!strcmp(key, "same_name")){
					json_object_foreach(tmp, key2, value){
						if(!strcmp(key2, "keyword"))
							strcpy(dataSet.meta.same_name.keyword , json_string_value(value));
						else if(!strcmp(key2, "region")){
							json_array_foreach(value, i, tmp){
							strcpy(dataSet.meta.same_name.regions[i].region, json_string_value(tmp));
							}
						}
						else if(!strcmp(key2, "selected_region"))
							strcpy(dataSet.meta.same_name.selected_region, json_string_value(value));
					}
				}
				else if(!strcmp(key, "total_count"))
					dataSet.meta.total_count = json_integer_value(value);
				else{
					error_print("key is invalid");
				}
			}

		}
		else{
			error_print("meta value is not object");
		}
	}
	else{
		error_print("meta is not found");
	}

}

