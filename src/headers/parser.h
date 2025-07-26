#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include <stddef.h>

struct Json;
struct JsonArray;
struct HashMap;
struct HashMapNode;

typedef enum {
	JSON_NULL,
	JSON_OBJECT,
	JSON_STRING,
	JSON_NUMBER,
	JSON_ARRAY,
	JSON_BOOL
} JsonType;

typedef struct JsonArray {
	struct Json **elements;
	size_t count;
	size_t capacity;
} JsonArray;

typedef struct HashMapNode {
	char *key;
	struct Json *value;
	struct HashMapNode *next;
} HashMapNode;

typedef struct HashMap {
	HashMapNode **buckets;
	size_t capacity;
} HashMap;

typedef struct Json {
	JsonType type;
	union {
		bool boolean;
		double number;
		char *string;
		JsonArray *array;
		HashMap *map;
	} as;
} Json;

int parseJson(char *json);
int parseObject(char *object);
Json* JSONparse(char *json);
Json* jsonGetFromObject(const Json *json, char *key);
Json* jsonGetFromArray(const Json *json, int index);
char* jsonGetAsString(const Json *json);


struct JsonObject {
	char *data;
	struct JsonObject *prev;
	struct JsonObject *next;
};

#endif
