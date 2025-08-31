// This is shamelessly copied from AI. It is the only piece of AI
// code in this project because I am VERY FRUSTRATED with the 
// libsecret docs. I tried doing this the legit way for hours but the 
// entry just wouldn't show up in seahorse.
//
// I do have a simple understanding of how libsecret works with schemas and whatnot.
// This should be all I need for doing the simplest task this library is designed for.
// I am not reading the entirety of libsecret docs.
// I am not wasting any more time going around weird contraptions just to 
// do the simple act of storing a password in a keyring.
//
// Below code was written ~60% by a clanker and restructured by me to fit
// into this project.

// May the light of UNIX find you, you heathens.

#include "api/request.h"
#include "import_ui.h"
#include <glib.h>
#include <libsecret/secret.h>
#include <stdio.h>

#define SCHEMA_NAME "com.aesistril.kilmister"

// Add "instance" attribute
static const SecretSchema schema = {
    SCHEMA_NAME,
    SECRET_SCHEMA_NONE,
    {
        { NULL, 0 },
    }
};

// Callback for storing password
static void store_password_cb(GObject *source_object, GAsyncResult *res, gpointer user_data) {
    GError *error = NULL;
    if (!secret_password_store_finish(res, &error)) {
        toast_printf(toast_overlay, "Failed to store login: %s", error->message);
        g_error_free(error);
    } else {
        toast_printf(toast_overlay, "Login stored successfully");
    }
}

// Callback for retrieving password
static void get_password_cb(GObject *source_object, GAsyncResult *res, gpointer user_data) {
    GError *error = NULL;
    gchar *password = secret_password_lookup_finish(res, &error);

    if (error != NULL) {
        toast_printf(toast_overlay, "Failed to get saved login: %s", error->message);
        g_error_free(error);
        return;
    }

    if (password != NULL) {
        lemmy_jwt = password; // Do NOT call secret_password_free(password) here
        toast_printf(toast_overlay, "Password retrieved successfully");
    } else {
        toast_printf(toast_overlay, "No password found for this instance");
    }
}
// Store credentials for a specific instance
void creds_store(const char *cred) {
    secret_password_store(&schema,
                          SECRET_COLLECTION_DEFAULT,
                          "Lemmy Auth Creds",
                          cred,
                          NULL, // cancellable
                          store_password_cb,
                          NULL,
                          NULL);
}

// Retrieve credentials for a specific instance
void creds_get() {
    secret_password_lookup(&schema,
                           NULL, // cancellable
                           get_password_cb,
                           NULL,
                           NULL);
}