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

GtkWindow*  mainwin;
GtkButton* login_button;
AdwEntryRow* login_instance_field;
AdwEntryRow* login_user_field;
AdwEntryRow* login_pass_field;
AdwEntryRow* login_totp_field;
GtkCheckButton* login_remembercheck;

void import_ui_def(GtkBuilder *builder){
    mainwin = GTK_WINDOW(gtk_builder_get_object(builder, "mainwin"));
    login_button = GTK_BUTTON(gtk_builder_get_object(builder, "login_button"));
    login_instance_field = ADW_ENTRY_ROW(gtk_builder_get_object(builder, "login_instance_field"));
    login_user_field = ADW_ENTRY_ROW(gtk_builder_get_object(builder, "login_user_field"));
    login_pass_field = ADW_ENTRY_ROW(gtk_builder_get_object(builder, "login_pass_field"));
    login_totp_field = ADW_ENTRY_ROW(gtk_builder_get_object(builder, "login_totp_field"));
    login_remembercheck = GTK_CHECK_BUTTON(gtk_builder_get_object(builder, "login_remembercheck"));
}