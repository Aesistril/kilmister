#ifndef LEMMY_APIV3_H
#define LEMMY_APIV3_H

#include <stdbool.h>

typedef struct Lemmyv3Login_t {
    char *jwt;
    bool registration_created;
    bool verify_email_sent;
} Lemmyv3Login_t;

Lemmyv3Login_t lemmyv3_login(const char *username_or_email, const char *password, const char *totp_2fa_token);

#endif