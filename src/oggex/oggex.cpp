//#include "Dashboard.h"

//#include <gtkmm.h>
#include <gtk/gtk.h>
#include <glib/gstdio.h>

#include <fmt/core.h>
#include <fmt/printf.h> 

using namespace std;

static void print_hello (GtkWidget *widget, gpointer data) {
  g_print ("Hello World\n");
}

static void quit_cb (GtkWindow *window) {
  gtk_window_close (window);
}

static void activate (GtkApplication *app, gpointer user_data) {
  GtkBuilder *builder = gtk_builder_new();
  gtk_builder_add_from_file (builder, "dashboard.ui", NULL);

  GObject *window = gtk_builder_get_object (builder, "oggex");
  gtk_window_set_application (GTK_WINDOW (window), app);

  GObject *button = gtk_builder_get_object (builder, "button1");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

  button = gtk_builder_get_object (builder, "button2");
  g_signal_connect (button, "clicked", G_CALLBACK (print_hello), NULL);

  button = gtk_builder_get_object (builder, "quit");
  g_signal_connect_swapped (button, "clicked", G_CALLBACK (quit_cb), window);

  gtk_widget_show (GTK_WIDGET (window));

  g_object_unref (builder);
}


int main(int argc, char *argv[]) {
  //auto application = DashboardController::create();
  //return application->run(argc, argv);
#ifdef GTK_SRCDIR
  g_chdir (GTK_SRCDIR);
#endif

  GtkApplication *app;
  int status;

  app = gtk_application_new ("com.github.jmd.oggex", G_APPLICATION_FLAGS_NONE);
  g_signal_connect (app, "activate", G_CALLBACK (activate), NULL);
  status = g_application_run (G_APPLICATION (app), argc, argv);
  g_object_unref (app);

  return status;
}
