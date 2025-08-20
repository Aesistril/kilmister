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

#include <glib.h>
#include <gtk/gtk.h>
#include <adwaita.h>
#include <curl/curl.h>
#include "api/request.h"
#include "gtk/gtkshortcut.h"
#include <stdio.h>
#include "signals_gui.h"
#include "import_ui.h"

#define LEMMY_API_V3
#include "api/lemmy.h"


gpointer login_button_worker(gpointer data) {
    WorkerData *wdata = data;

    lemmy_instance_domain = gtk_editable_get_text(GTK_EDITABLE(login_instance_field));

    // heap allocated pointer to LemmyLogin_t
    wdata->res = lemmy_login(gtk_editable_get_text(GTK_EDITABLE(login_user_field)),
                            gtk_editable_get_text(GTK_EDITABLE(login_pass_field)),
                            gtk_editable_get_text(GTK_EDITABLE(login_totp_field))).jwt;

    if(gtk_check_button_get_active(login_remembercheck)) {
        // libsecret save
    }

    // Quit nested loop once done
    g_main_loop_quit(wdata->loop);
    return NULL;
}

void launch_nonblocking(GtkWidget *widget, gpointer function) {
    WorkerData data = {0};
    data.loop = g_main_loop_new(NULL, FALSE);

    // Start thread
    g_thread_new("worker", function, &data);

    // Block here, but UI still processes events
    g_main_loop_run(data.loop);

    // Worker done
    g_print("Worker result: %s\n", data.res);
    g_free(data.res);
    g_main_loop_unref(data.loop);
    
}