#include "headers/simpleparse.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SpArray getArrayFromJson(char *json) {
	SpArray array;
	array.objects = malloc(32 * sizeof(SpObject));
	// freed in main.c, for-loop
	array.count = 0;
	array.capacity = 32;

	char *placeholder = json;
	// Go to the nearest [
	while (*placeholder != '[') {
		if (*placeholder == '\0') {
			return array;
			break;
		}
		placeholder++;
	}

	int openCount = 0;
	int closeCount = 0;

	int charCount = 0;
	int currObjSize = 32;
	char *currentObject = (char*)malloc(currObjSize);
	// Freed at the end of this function

	while (*placeholder != '\0') {
		if (*placeholder == '{') openCount++;
		if (*placeholder == '}') closeCount++;
		placeholder++;
		if (openCount == closeCount && openCount != 0) {
			SpObject *newObject = malloc(sizeof(SpObject));
			// Freed in main.c, for-loop
			newObject->value = (char*)malloc(currObjSize);
			// Freed in main.c, for-loop
			currentObject[charCount] = '\0';
			strcpy(newObject->value, currentObject);
			newObject->size = charCount;
			array.objects[array.count] = newObject;
			array.count++;
			charCount = 0;
			currObjSize = 32;
			free(currentObject);
			currentObject = (char*)malloc(currObjSize);
			// Freed in the next loop
			openCount = 0;
			closeCount = 0;
		}
		if (openCount == closeCount && openCount == 0) continue;
		// if it reaches this area, that means we are in an object
		// copy the current character into the object value
		currentObject[charCount] = *placeholder;
		charCount++;
		if (charCount >= currObjSize) {
			currObjSize *= 2;
			currentObject = (char*)realloc(currentObject, currObjSize);
		}
	}

	free(currentObject);

	return array;
}

char *parseLine(char *mainLine, int lineNo, char *line, size_t size) {
	char *toAppend = (char*)malloc(size);
	// freed in main.c, the second for-loop

	char *placeholder = line;
	int started = 0;
	int count = 0;
	while (*placeholder != '\0') {
		if (*placeholder == ':' && *(placeholder+1) == ' ') {
			started = 1;
			placeholder+=2;
			continue;
		}

		if (*placeholder == ',' && *(placeholder+1) == '\0') {
			placeholder++;
			continue;
		}

		if (started == 0) {
			placeholder++;
			continue;
		}

		toAppend[count] = *placeholder;
		count++;
		toAppend[count] = '\0';
		placeholder++;
	}

	strcat(mainLine, toAppend);
	strcat(mainLine, ",");
	return toAppend;
}

char *populateCsv(SpObject *object, CsvLine *csvLine) {
	char *token = (char*)malloc(object->size);
	// freed at the end of this function
	int count = 0;
	token = strtok(object->value, "\n");

	char *toReturn = (char*)malloc(object->size);
	// freed in main.c, for loop
	strcpy(toReturn, "");

	int locationStart = 0;
	int displayNameStart = 0;
	while (token != NULL) {
		//// id, formattedAddress, location.latitude, location.longitude, googleMapsUri, displayName.text
		if (strstr(token, "\"location\"")) {
			locationStart = 1;
		}
		if (strstr(token, "\"displayName\"")) {
			displayNameStart = 1;
		}

		if (strstr(token, "\"id\"")) {
			char *line = parseLine(toReturn, count, token, strlen(token));
			csvLine->id = line;
		} else if (strstr(token, "\"formattedAddress\"")) {
			char *line = parseLine(toReturn, count, token, strlen(token));
			csvLine->formattedAddress = line;
		} else if (strstr(token, "\"latitude\"") && locationStart == 1) {
			char *line = parseLine(toReturn, count, token, strlen(token));
			csvLine->latitude = line;
		} else if (strstr(token, "\"longitude\"") && locationStart == 1) {
			char *line = parseLine(toReturn, count, token, strlen(token));
			csvLine->longitude = line;
			locationStart = 0;
		} else if (strstr(token, "\"googleMapsUri\"")) {
			char *line = parseLine(toReturn, count, token, strlen(token));
			csvLine->googleMapsUri = line;
		} else if (strstr(token, "\"text\"") && displayNameStart == 1) {
			char *line = parseLine(toReturn, count, token, strlen(token));
			csvLine->displayName = line;
			displayNameStart = 0;
		}

		token = strtok(NULL, "\n");
		count++;
	}

	free(token);
	return toReturn;
}
