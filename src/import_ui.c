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

#include "import_ui.h"
#include "adwaita.h"
#include <stdarg.h>
#include <stdarg.h>
#include <stdio.h>

GtkWindow*  mainwin;
GtkButton* login_button;
AdwEntryRow* login_instance_field;
AdwEntryRow* login_user_field;
AdwEntryRow* login_pass_field;
AdwEntryRow* login_totp_field;
GtkCheckButton* login_remembercheck;
AdwToastOverlay* toast_overlay;
AdwViewStackPage* spinnerpage;
AdwViewStackPage* loginpage;
AdwViewStackPage* mainpage;
AdwViewStack* topstack;


void import_ui_def(GtkBuilder *builder){
    mainwin = GTK_WINDOW(gtk_builder_get_object(builder, "mainwin"));
    login_button = GTK_BUTTON(gtk_builder_get_object(builder, "login_button"));
    login_instance_field = ADW_ENTRY_ROW(gtk_builder_get_object(builder, "login_instance_field"));
    login_user_field = ADW_ENTRY_ROW(gtk_builder_get_object(builder, "login_user_field"));
    login_pass_field = ADW_ENTRY_ROW(gtk_builder_get_object(builder, "login_pass_field"));
    login_totp_field = ADW_ENTRY_ROW(gtk_builder_get_object(builder, "login_totp_field"));
    login_remembercheck = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "login_remembercheck"));
    toast_overlay = ADW_TOAST_OVERLAY(gtk_builder_get_object(builder, "toast_overlay"));
    spinnerpage = ADW_VIEW_STACK_PAGE(gtk_builder_get_object(builder, "spinnerpage"));
    loginpage = ADW_VIEW_STACK_PAGE(gtk_builder_get_object(builder, "loginpage"));
    mainpage = ADW_VIEW_STACK_PAGE(gtk_builder_get_object(builder, "mainpage"));
    topstack = ADW_VIEW_STACK(gtk_builder_get_object(builder, "topstack"));
}

void toast_printf(AdwToastOverlay* overlay, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    int len = vsnprintf(NULL, 0, fmt, args) + 1;
    va_end(args);

    va_start(args, fmt);
    char *message = malloc(len);
    vsnprintf(message, len, fmt, args);
    va_end(args);

    AdwToast *toast = adw_toast_new(message);
    adw_toast_overlay_add_toast(overlay, toast);
}