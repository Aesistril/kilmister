// creds.c
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
