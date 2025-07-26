#include "headers/places.h"
#include "headers/file.h"
#include "headers/helpers.h"
#include <curl/curl.h>
#include <curl/easy.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int basePlaces(char *key, char *query) {
	CURL *curl = curl_easy_init();
	if (!curl) {
		printf("curl_easy_init failed\n");
		return 1;
	}
	struct MemoryStruct chunk;
	chunk.memory = malloc(1);
	// freed near the end of this function
	chunk.size = 0;

	char post_data[1024];
	snprintf(post_data, sizeof(post_data), "{\"textQuery\": \"%s\"}\n", query);

	struct curl_slist *headers = NULL;
	headers = curl_slist_append(headers, "Content-Type: application/json");
	headers = curl_slist_append(headers, "X-Goog-FieldMask: places.displayName,places.name,places.id,places.types,places.nationalPhoneNumber,places.internationalPhoneNumber,places.formattedAddress,places.location,places.viewport,places.googleMapsUri,places.websiteUri");
	char api_header[1024];
	snprintf(api_header, sizeof(api_header), "X-Goog-Api-Key: %s", key);
	headers = curl_slist_append(headers, api_header);

	CURLcode res;
	curl_easy_setopt(curl, CURLOPT_URL, "https://places.googleapis.com/v1/places:searchText");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_data);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

	res = curl_easy_perform(curl);

	if (res != CURLE_OK) {
		printf("curl_easy_perform failed: %s\n", curl_easy_strerror(res));
	} else {
		writeJson(chunk.memory);
		free(chunk.memory);
	}

	curl_easy_cleanup(curl);
	curl_slist_free_all(headers);

	return 0;
}
