#include <stddef.h>
#include <stdio.h>
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include "headers/file.h"
#include "headers/parser.h"
#include "headers/places.h"
#include "headers/simpleparse.h"

// AIzaSyCbjPXU1C7Rr8WblgqDQcXSclq3VaH3g3k

int main() {
	FILE *csv = fopen("./latest-results.csv", "w");
	fclose(csv);
	csv = fopen("./latest-results.csv", "a");
	fprintf(csv, "ID,Formatted Address,Latitude,Longitude,Google Maps URI,Display Name\n");
	// closed at the bottom of this function
	char *key = initFile();
	if (key == 0) {
		return 1;
	}

	char query[1024];
	// Uncomment later
	///////////////////////////////////////
	printf("Enter your query: ");
	scanf("%[^\n]s", query);
	basePlaces(key, query);
	///////////////////////////////////////
	char *filename = (char*)malloc(strlen(query) + 5);
	strcpy(filename, "./");
	strcat(filename, query);
	strcat(filename, ".csv");
	FILE *newCsv = fopen(filename, "w");
	fprintf(newCsv, "ID,Formatted Address,Latitude,Longitude,Google Maps URI,Display Name\n");

	char *testJson = readJson();

	SpArray array = getArrayFromJson(testJson);
	CsvLine csvLineArray[array.count];

	printf("|-----------------|----------------------|-----------------|-----------------|-----------------|-----------------|\n");
	printf("| %15.15s | %20.20s | %15.15s | %15.15s | %15.15s | %15.15s |\n", "ID", "Formatted Address", "Latitude", "Longitude", "Google Maps URI", "Display Name");

	for (int i = 0; i < array.count; i++) {
		char *value = array.objects[i]->value;
		char *csvLine = populateCsv(array.objects[i], &csvLineArray[i]);
		fprintf(csv, "%s\n", csvLine);
		fprintf(newCsv, "%s\n", csvLine);
		free(array.objects[i]->value);
		free(array.objects[i]);
		free(csvLine);
	}

	for (int i = 0; i < array.count; i++) {
		printf("|-----------------|----------------------|-----------------|-----------------|-----------------|-----------------|\n");
		printf("| %-15.15s | %-20.20s | %-15.15s | %-15.15s | %-15.15s | %-15.15s |\n", csvLineArray[i].id, csvLineArray[i].formattedAddress, csvLineArray[i].latitude, csvLineArray[i].longitude, csvLineArray[i].googleMapsUri, csvLineArray[i].displayName);
		free(csvLineArray[i].id);
		free(csvLineArray[i].formattedAddress);
		free(csvLineArray[i].latitude);
		free(csvLineArray[i].longitude);
		free(csvLineArray[i].googleMapsUri);
		free(csvLineArray[i].displayName);
	}
	printf("|-----------------|----------------------|-----------------|-----------------|-----------------|-----------------|\n");
	printf("CSV file saved to %s\n", filename);

	free(filename);
	free(key);
	free(testJson);
	free(array.objects);
	fclose(csv);
	fclose(newCsv);

	return 0;
}
