#include "glib.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <libconfig.h>
#include <unistd.h>
#include <config.h>

kilmister_config *kilconfig = NULL;

char* kilconfig_getpath() {
    const gchar *user_confdir = g_get_user_config_dir();
    size_t len = strlen(user_confdir) + strlen("/kilmisterclient.conf") + 1;
    char *configpath = malloc(len);
    snprintf(configpath, len, "%s/kilmisterclient.conf", user_confdir); 

    return configpath;
}

// Create a default config file if it doesn't exist. 
int kilconfig_checkcreate() {
    struct stat configstat;
    char *configpath = kilconfig_getpath();

    // config does not exist.
    if(stat(configpath, &configstat)) {
        fprintf(stderr, "~/.config/kilmisterclient.cfg does not exist. Creating it.\n");

        kilmister_config default_config; 
        default_config.instance = "null";
        default_config.logged_in = false;

        kilconfig_save(&default_config);
        return 0;
    }
    
    // config exists
    free(configpath);
    return 0;
}

int kilconfig_load(kilmister_config *kilmister_cfg) {
    char *configpath = kilconfig_getpath();
    
    config_t cfg;

    config_init(&cfg);

    /* Read the file. If there is an error, report it and exit. */
    if(! config_read_file(&cfg, configpath))
    {
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                config_error_line(&cfg), config_error_text(&cfg));
        config_destroy(&cfg);
        return 1;
    }

    if(config_lookup_string(&cfg, "instance", &(kilmister_cfg->instance)));
    else {
        fprintf(stderr, "No 'instance' setting in ~/.config/kilmisterclient.cfg\n");
        return 1;
    }

    if(config_lookup_bool(&cfg, "logged_in", (int*) &(kilmister_cfg->logged_in)));
    else {
        fprintf(stderr, "No 'logged_in' setting in ~/.config/kilmisterclient.cfg\n");
        return 1;
    }

    free(configpath);
    return 0;
}


int kilconfig_save(kilmister_config *kilmister_cfg) {
    char *configpath = kilconfig_getpath();
    
    config_t cfg;
    config_setting_t *setting, *root;

    config_init(&cfg);
    root = config_root_setting(&cfg);
    
    setting = config_setting_add(root, "instance", CONFIG_TYPE_STRING);
    config_setting_set_string(setting, kilmister_cfg->instance);

    setting = config_setting_add(root, "logged_in", CONFIG_TYPE_BOOL);
    config_setting_set_bool(setting, kilmister_cfg->logged_in);

    if(!config_write_file(&cfg, configpath)) {
        fprintf(stderr, "Failed to save config file ~/.config/kilmisterclient.cfg");
        fprintf(stderr, "%s:%d - %s\n", config_error_file(&cfg),
                config_error_line(&cfg), config_error_text(&cfg));
        return 1;
    }

    fprintf(stderr, "Saved config file ~/.config/kilmisterclient.cfg");
    
    free(configpath);
    return 0;
}