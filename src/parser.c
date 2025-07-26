#include "headers/parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Json* JSONparse(char *json) {
	Json *value;
	value = (Json*)malloc(sizeof(Json));
	value->type = JSON_NULL;

	char token;

	char *placeholder = json;

	parseObject(json);

	while (*placeholder != '\0') {
		// To determine whether data is an array or an object
		if (*placeholder == '[' || *placeholder == '{' || *placeholder == '\"') {
			if (*placeholder == '[') {
				value->type = JSON_ARRAY;
				printf("%c: array\n", *placeholder);
			} else if (*placeholder == '{') {
				value->type = JSON_OBJECT;
				printf("%c: object\n", *placeholder);
			} else if (*placeholder == '\"') {
				value->type = JSON_STRING;
				printf("%c: string\n", *placeholder);
			} else {
				value->type = JSON_NULL;
			}
			break;
		}
		// if it ever reaches here, the data is invalid
		placeholder++;
		value->type = JSON_NULL;
	}

	return value;
}

int parseJson(char *json) {
	int objectCount = 0;
	int objectStartTokenCount = 0;
	int objectEndTokenCount = 0;
	int arrayStartTokenCount = 0;
	int arrayEndTokenCount = 0;
	int keyStartTokenCount = 0;
	int keyEndTokenCount = 0;
	int valueStartTokenCount = 0;
	int valueEndTokenCount = 0;

	struct JsonObject *head = (struct JsonObject*)malloc(sizeof(struct JsonObject));

	int currObjectSize = 16;
	char *currentObject = (char*)malloc(currObjectSize);
	int currObjectIndex = 0;
	while (*json != '\0') {
		// Only start counting when we are in an array
		if (*json == '[') {
			arrayStartTokenCount++;
		} else if (*json == ']') {
			arrayEndTokenCount++;
		}
		if (arrayStartTokenCount == 0 || arrayStartTokenCount == arrayEndTokenCount) {
			json++;
			continue;
		}

		// When objectStartTokenCount and objectEndTokenCount are greater than 0
		// and equal, that means one object is done
		if (*json == '{') {
			objectStartTokenCount++;
		} else if (*json == '}') {
			objectEndTokenCount++;
		}
		if (objectStartTokenCount > 0 && objectStartTokenCount == objectEndTokenCount) {
			objectStartTokenCount = 0;
			objectEndTokenCount = 0;
			currentObject[currObjectIndex] = *json;
			currentObject[currObjectIndex+1] = '\0';
			head = (struct JsonObject*)malloc(sizeof(struct JsonObject));
			head->data = currentObject;
			head->prev = NULL;
			parseObject(currentObject);
			// Reset the currentObject
			currObjectIndex = 0;
			currentObject = NULL;
			currentObject = (char*)malloc(currObjectSize);
			objectCount++;
		} else {
			// Append the current character to the current object
			currentObject[currObjectIndex] = *json;
			currObjectIndex++;

			// If the current object is full, double its size
			if (currObjectIndex == currObjectSize) {
				currObjectSize *= 2;
				char *temp = (char*)realloc(currentObject, currObjectSize);
				if (temp != NULL) {
					currentObject = temp;
				} else {
					free(currentObject);
					currentObject = NULL;
					printf("Out of memory\n");
				}
			}
		}
		json++;
	}

	printf("Objects: %d\n", objectCount);

	return 0;
}

// This function will flatten the object
// Get all the direct keys
int parseObject(char *object) {
	while (*object != '\0') {
		printf("%c", *object);
		object++;
	}

	return 0;
}
