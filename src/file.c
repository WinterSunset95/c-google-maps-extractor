#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/file.h"

char* initFile() {
	FILE *fp;
	char *key;
	long fileSize = 512;

	// Open or create file
	fp = fopen("./.env", "r");
	if (fp == NULL) {
		printf("File does not exist\n");
		printf("Creating file\n");
		fp = fopen("./.env", "w");
		if (fp == NULL) {
			printf("Failed to create and open file\n");
			return 0;
		}
	}

	// Check if file is empty or not
	int c = fgetc(fp);
	if (c == EOF) {
		// File is empty, get the API key from the user
		printf("A Places API key is required to use this program\nGo to https://cloud.google.com/maps-platform/ to get one\n");
		printf("Enter your API key: ");
		fgets(key, fileSize, stdin);
		printf("API key: %s\n", key);
		fprintf(fp, "%s", key);
		key[strcspn(key, "\n")] = 0;
		fclose(fp);
		return 0;
	}
	// If it reaches here, the file exists and is not empty.
	// In which case we will get the filesize
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	rewind(fp);
	key = (char *)malloc(fileSize + 1);
	// freed at the end of main.c

	// Get the API key from the file
	size_t bytes_read = fread(key, 1, fileSize, fp);
	if (bytes_read != fileSize) {
		printf("Failed to read file\n");
		return 0;
	}
	key[fileSize] = '\0';
	key[strcspn(key, "\n")] = 0;
	fclose(fp);
	return key;
}

int writeJson(char *json) {
	FILE *fp;
	fp = fopen("./result.json", "w");
	if (fp == NULL) {
		printf("Failed to open file\n");
		return 1;
	}
	fprintf(fp, "%s", json);
	fclose(fp);
	return 0;
}

char* readJson() {
	char *json;
	FILE *fp;
	fp = fopen("./result.json", "r");
	if (fp == NULL) {
		printf("Failed to open file\n");
		return 0;
	}
	long fileSize = 0;
	fseek(fp, 0, SEEK_END);
	fileSize = ftell(fp);
	rewind(fp);
	json = (char *)malloc(fileSize + 1);
	// freed at the end of main.c
	size_t bytes_read = fread(json, 1, fileSize, fp);
	if (bytes_read != fileSize) {
		printf("Failed to read file\n");
		return 0;
	}
	json[fileSize] = '\0';

	fclose(fp);
	return json;
}
