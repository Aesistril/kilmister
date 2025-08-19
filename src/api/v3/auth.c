#include "api/request.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// account/auth/login 
// Log into Lemmy
char* lemmyv3_login(char *username_or_email, char *password,  char *totp_2fa_token) {
    size_t len = 69
           + strlen(totp_2fa_token)
           + strlen(password)
           + strlen(username_or_email)
           + 1;

    char *payload = malloc(len);

    snprintf(payload, len, "{\"totp_2fa_token\": \"%s\",\"password\": \"%s\",\"username_or_email\": \"%s\"}", 
        totp_2fa_token, password, username_or_email);

    return lemmy_api_call("POST", "v3/user/login", NULL, payload);
}