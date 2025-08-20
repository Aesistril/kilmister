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
#include "glib-object.h"
#include "gtk/gtkshortcut.h"
#include <stdio.h>
#include "import_ui.h"
#include "signals_gui.h"


static void activate(AdwApplication *app, gpointer user_data) {
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "/home/ae/Projects/C/kilmister/src/ui/main.ui", NULL);

    // import some objects from ui definition
    import_ui_def(builder);
    g_object_unref(builder);

    g_signal_connect(login_button, "clicked", G_CALLBACK(launch_nonblocking), login_button_worker);
    
    // set and summon the main window
    gtk_window_set_application(GTK_WINDOW(mainwin), GTK_APPLICATION(app));
    gtk_window_present(GTK_WINDOW(mainwin));
}

int main(int argc, char *argv[]) {
    AdwApplication *app = adw_application_new("com.aesistril.kilmister", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    curl_global_cleanup();
    return status;
}