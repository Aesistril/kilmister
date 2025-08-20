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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>

#include "api/request.h"
#include "api/v3/lemmy_apiv3.h"

// account/auth/login 
// Log into Lemmy
// Lemmyv3Login_t.jwt is NULL if fails, booleans initialized as false
Lemmyv3Login_t lemmyv3_login(const char *username_or_email, const char *password, const char *totp_2fa_token) {
    size_t len = 69
           + strlen(totp_2fa_token)
           + strlen(password)
           + strlen(username_or_email)
           + 1;

    char *payload = malloc(len);

    snprintf(payload, len, "{\"totp_2fa_token\": \"%s\",\"password\": \"%s\",\"username_or_email\": \"%s\"}", 
        totp_2fa_token, password, username_or_email);

    char *resp = lemmy_api_call("POST", "v3/user/login", NULL, payload);
    cJSON *json = cJSON_Parse(resp);
    cJSON *json_jwt = cJSON_GetObjectItemCaseSensitive(json, "jwt");
    cJSON *json_registration_created = cJSON_GetObjectItemCaseSensitive(json, "registration_created");
    cJSON *json_verify_email_sent = cJSON_GetObjectItemCaseSensitive(json, "verify_email_sent");
    
    Lemmyv3Login_t res;
    res.jwt = NULL;
    res.registration_created = false;
    res.verify_email_sent = false;

    if(cJSON_IsString(json_jwt) && json_jwt->valuestring != NULL) {
        res.jwt = strdup(json_jwt->valuestring);
    }
    if(cJSON_IsBool(json_registration_created)) {
        res.registration_created = cJSON_IsTrue(json_registration_created);
    }
    if(cJSON_IsBool(json_verify_email_sent)) {
        res.verify_email_sent = cJSON_IsTrue(json_verify_email_sent);
    }

    free(resp);
    free(payload);
    cJSON_Delete(json);
    return res;
}