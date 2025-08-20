#ifndef SIGNALS_H
#define SIGNALS_H

#include <glib.h>
#include <gtk/gtk.h>

typedef struct {
    GMainLoop *loop;
    GThreadFunc worker;
    void *res;
} WorkerData;

gpointer login_button_worker(gpointer data);
void launch_nonblocking(GtkWidget *widget, gpointer function);

#endif