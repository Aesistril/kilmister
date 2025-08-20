// Kilmister Client -- A lemmy client for GTK desktops and mobile devices
// Copyright (C) 2025-2026

// This file is part of Kilmister Client.
// Kilmister Client is free software: you can redistribute it and/or modify it under the terms of 
// the GNU General Public License as published by the Free Software Foundation, either version 
// 3 of the License, or (at your option) any later version.
// Kilmister Client is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
// See the GNU General Public License for more details.
// You should have received a copy of the GNU General Public License along with Kilmister Client. 
// If not, see <https://www.gnu.org/licenses/>. 

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <curl/curl.h>
#include "request.h"

const char* lemmy_instance_domain = NULL;
const char* lemmy_jwt = NULL;

static size_t write_callback(void *data, size_t size, size_t nmemb, void *userp) {
    size_t realsize = size * nmemb;
    struct memory *mem = (struct memory *)userp;

    char *ptr = realloc(mem->response, mem->size + realsize + 1);
    if (ptr == NULL) {
        fprintf(stderr, "Out of memory!\n");
        return 0;
    }

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = '\0';

    return realsize;
}

char* http_request(const char *url, const char *method, const char *json_payload) {
    CURL *curl;
    CURLcode res;
    struct memory chunk = {0};
    struct curl_slist *headers = NULL;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl)
        return NULL;

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "kilmister-client/1.0");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

    // If POST with payload
    if (method && strcasecmp(method, "POST") == 0 && json_payload) {
        headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload);
    } else if (method && strcasecmp(method, "GET") != 0) {
        // Other HTTP methods
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, method);
    }

    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        free(chunk.response);
        chunk.response = NULL;
    }

    if (headers) curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
    curl_global_cleanup();
    return chunk.response;
}

// char *lemmy_instance_domain should be defined before using this function
// This is basically a shorthand for putting the instance name in the URL.
// All the options are just added to the final url back to back with no modifications.
char* lemmy_api_call(const char *method, const char *call, const char *url_params, const char *json_payload) {
    if (!method || !call) return NULL;

    size_t len = strlen("https://") + strlen(lemmy_instance_domain) +
                 strlen("/api/v4/") + strlen(call) +
                 (url_params ? strlen(url_params) : 0) + 1;

    char *url = malloc(len);
    if (!url) return NULL;

    if (url_params)
        snprintf(url, len, "https://%s/api/%s%s", lemmy_instance_domain, call, url_params);
    else
        snprintf(url, len, "https://%s/api/%s", lemmy_instance_domain, call);

    char *data = http_request(url, method, json_payload);

    free(url);
    return data;
}
