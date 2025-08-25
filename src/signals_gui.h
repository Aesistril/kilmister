#ifndef SIGNALS_H
#define SIGNALS_H

#include <glib.h>
#include <gtk/gtk.h>

typedef struct {
    GMainLoop *loop;
    GThreadFunc worker;
    void *res;
} WorkerData;

void login_button_worker(gpointer data);
void launch_nonblocking(GtkWidget *widget, gpointer function);
void creds_try_login(gpointer data);

#endif