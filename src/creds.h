#ifndef CREDS_H
#define CREDS_H

#include "libsecret/secret.h"

const SecretSchema * kilmister_get_schema (void) G_GNUC_CONST;

#define KILMISTER_SCHEMA  kilmister_get_schema ()

void creds_store(const char *cred);
void creds_get();


#endif