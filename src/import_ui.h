#ifndef IMPORTUI_H
#define IMPORTUI_H

#include <gtk/gtk.h>
#include <adwaita.h>

// Widgets are global because passing variables to g_signal_connect is
// unnecessarily complex for the purposes of this project
extern GtkWindow*  mainwin;
extern GtkButton* login_button;
extern AdwEntryRow* login_instance_field;
extern AdwEntryRow* login_user_field;
extern AdwEntryRow* login_pass_field;
extern AdwEntryRow* login_totp_field;
extern GtkCheckButton* login_remembercheck;
extern AdwToastOverlay* toast_overlay;
extern AdwViewStackPage* spinnerpage;
extern AdwViewStackPage* loginpage;
extern AdwViewStackPage* mainpage;
extern AdwViewStack* topstack;

void import_ui_def(GtkBuilder *builder);
void toast_printf(AdwToastOverlay* overlay, const char *fmt, ...);

#endif