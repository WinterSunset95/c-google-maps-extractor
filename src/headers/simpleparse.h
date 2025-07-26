#ifndef SIMPLEPARSE_H
#define SIMPLEPARSE_H
// This is a simplified parser for the JSON recieved from the Places API
// For this parser, we assume that the JSON will be always of the same format

#include <stddef.h>

typedef struct SpObject {
	char *value;
	size_t size;
} SpObject;

typedef struct CsvLine {
	char *id;
	char *formattedAddress;
	char *latitude;
	char *longitude;
	char *googleMapsUri;
	char *displayName;
} CsvLine;

typedef struct SpArray {
	SpObject **objects;
	size_t count;
	size_t capacity;
} SpArray;

// Get an array of character arrays from the base JSON string
SpArray getArrayFromJson(char *json);
char *populateCsv(SpObject *object, CsvLine *csvLine);

#endif
