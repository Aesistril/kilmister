#include <glib.h>
#include <gtk/gtk.h>
#include <adwaita.h>
#include <curl/curl.h>
#include "api/request.h"
#include "glib-object.h"
#include "gtk/gtkshortcut.h"
#include <stdio.h>

#define LEMMY_API_V3
#include "api/lemmy.h"

GtkWindow* mainwin;
GtkButton* print_button;

static void on_button_clicked(GtkWidget *header_bar, gpointer data) {
    g_print(" clicked\n");
}

static void activate(AdwApplication *app, gpointer user_data) {
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "/home/ae/Projects/C/kilmister/src/ui/main.ui", NULL);

    // import some objects from ui definition
    mainwin = GTK_WINDOW(gtk_builder_get_object(builder, "mainwin"));
    AdwHeaderBar* header_bar = ADW_HEADER_BAR(gtk_builder_get_object(builder, "header_bar"));
    print_button = GTK_BUTTON(gtk_builder_get_object(builder, "print_button"));
    g_object_unref(builder);

    g_signal_connect(print_button, "clicked", G_CALLBACK(on_button_clicked), NULL);


    lemmy_instance_domain = "lemmy.world";
    
    // char twofa[7];
    // printf("2fa token: ");
    // fgets(twofa, 7, stdin);
    

    // if(resp) {
    //     printf("%s\n", resp);
    // }

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