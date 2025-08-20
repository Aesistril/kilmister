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

#include "libsecret/secret.h"

#define KILMISTER_SCHEMA kilmister_get_schema ()

const SecretSchema *kilmister_get_schema (void) {
    static const SecretSchema schema = {
        "com.aesistril.kilmister", SECRET_SCHEMA_NONE,
        {
            {"jwt", SECRET_SCHEMA_ATTRIBUTE_STRING},
        }
    };

    return &schema;
}

static void on_password_stored (GObject *source, GAsyncResult *result, gpointer unused) {
    GError *error = NULL;

    secret_password_store_finish (result, &error);
    if (error != NULL) {
        /* ... handle the failure here */
        g_error_free (error);
    } else {
        /* ... do something now that the password has been stored */
    }
}

