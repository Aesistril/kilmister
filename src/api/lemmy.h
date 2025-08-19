#ifndef LEMMY_H
#define LEMMY_H

#include <stddef.h>

// ---- Macro alias ----
#if defined(LEMMY_API_V3)
#  include "api/v3/lemmy_apiv3.h"
#  define lemmy_login lemmyv3_login
#  define LemmyLogin_t Lemmyv3Login_t
#elif defined(LEMMY_API_V4)
#  include "api/v4/lemmy_apiv4.h"
#  define lemmy_login lemmyv4_login
#else
#  error "You must define LEMMY_API_V3 or LEMMY_API_V4 before including lemmy.h"
#endif

#endif