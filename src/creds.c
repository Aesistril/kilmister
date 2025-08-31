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

#include "api/request.h"
#include "import_ui.h"
#include <glib.h>
#include <libsecret/secret.h>
#include <stdio.h>

#define SCHEMA_NAME "com.aesistril.kilmister"

// Secret schema with "instance" attribute
static const SecretSchema schema = {
    SCHEMA_NAME,
    SECRET_SCHEMA_NONE,
    {
        { "instance", SECRET_SCHEMA_ATTRIBUTE_STRING },
        { NULL, 0 }
    }
};

// Store credentials for a specific Lemmy instance synchronously
void creds_store(const char *cred) {
    if (!lemmy_instance_domain || !cred) {
        toast_printf(toast_overlay, "Invalid instance or credential");
        return;
    }

    GError *error = NULL;

    if (!secret_password_store_sync(&schema,
                                   SECRET_COLLECTION_DEFAULT,
                                   "Lemmy Auth Creds",
                                   cred,
                                   NULL, // cancellable
                                   &error,
                                   "instance", lemmy_instance_domain,
                                   NULL)) {
        toast_printf(toast_overlay, "Failed to store login: %s", error ? error->message : "Unknown error");
        if (error) g_error_free(error);
    } else {
        toast_printf(toast_overlay, "Login stored successfully");
    }
}

// Retrieve credentials for a specific Lemmy instance synchronously
void creds_get() {
    if (!lemmy_instance_domain) {
        lemmy_jwt = NULL;
        toast_printf(toast_overlay, "No instance selected");
        return;
    }

    GError *error = NULL;
    gchar *password = secret_password_lookup_sync(&schema,
                                                  NULL, // cancellable
                                                  &error,
                                                  "instance", lemmy_instance_domain,
                                                  NULL);

    if (error != NULL) {
        toast_printf(toast_overlay, "Failed to get saved login: %s", error->message);
        g_error_free(error);
        lemmy_jwt = NULL;
        return;
    }

    if (password != NULL) {
        lemmy_jwt = password; // keep ownership, do NOT free
        toast_printf(toast_overlay, "Password retrieved successfully");
    } else {
        lemmy_jwt = NULL;
        toast_printf(toast_overlay, "No password found for this instance");
    }
}
