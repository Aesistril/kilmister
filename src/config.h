#ifndef KILCONFIG_H
#define KILCONFIG_H

#include <stdbool.h>

// generally heap allocated
typedef struct kilmister_config {
    const char* instance;
    bool logged_in;
} kilmister_config;

extern kilmister_config *kilconfig;

int kilconfig_checkcreate();
int kilconfig_load(kilmister_config *kilmister_cfg);
int kilconfig_save(kilmister_config *kilmister_cfg);

#endif