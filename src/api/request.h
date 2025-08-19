#ifndef REQUEST_H
#define REQUEST_H

#include <stddef.h>

extern char* lemmy_instance_domain;

struct memory {
    char *response;
    size_t size;
};

char* lemmy_api_call(const char *method, const char *call, const char *url_params, const char *json_payload);

#endif