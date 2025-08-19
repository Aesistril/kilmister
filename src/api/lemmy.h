#ifndef LEMMY_H
#define LEMMY_H

#include <stddef.h>

char *lemmyv3_login(const char *username, const char *password, const char *totp_2fa_token);
char *lemmyv4_login(const char *username, const char *password, const char *totp_2fa_token);

// ---- Macro alias ----
#if defined(LEMMY_API_V3)
#  define lemmy_login lemmyv3_login
#elif defined(LEMMY_API_V4)
#  define lemmy_login lemmyv4_login
#else
#  error "You must define LEMMY_API_V3 or LEMMY_API_V4 before including lemmy.h"
#endif

#endif