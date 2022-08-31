#include "filechooserbutton.h"

/* Private member variables */
typedef struct {
  const char* prompt;
  GFile *file;
  GtkFileChooserNative *fc;
  GtkFileFilter *file_filter; 
  GtkFileChooserAction action;
} FileChooserButtonPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(FileChooserButton, filechooserbutton, GTK_TYPE_BUTTON)

static void filechooserbutton_class_init (FileChooserButtonClass *klass) {
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  /* TODO: Free resource in oggex window destructor */
  const char* resource = "/io/github/com/jmdaemon/oggex/../../../resources/gtk/filechooserbutton.ui";
  gtk_widget_class_set_template_from_resource (widget_class, resource);

  /*free(resource);*/
}

static void filechooserbutton_init (FileChooserButton *self) {
  gtk_widget_init_template (GTK_WIDGET (self));

  FileChooserButtonPrivate *priv = filechooserbutton_get_instance_private(self);
}

/* Getters */
const char* filechooserbutton_get_prompt(FileChooserButton *self) {
  FileChooserButtonPrivate* priv = filechooserbutton_get_instance_private(self);
  return priv->prompt;
}

GFile* filechooserbutton_get_file(FileChooserButton *self) {
  FileChooserButtonPrivate* priv = filechooserbutton_get_instance_private(self);
  return priv->file;
}

GtkFileChooserNative* filechooserbutton_get_fcn(FileChooserButton *self) {
  FileChooserButtonPrivate* priv = filechooserbutton_get_instance_private(self);
  return priv->fc;
}

GtkFileChooserAction filechooserbutton_get_action(FileChooserButton *self) {
  FileChooserButtonPrivate* priv = filechooserbutton_get_instance_private(self);
  return priv->action;
}

/* Setters */
static void filechooserbutton_set_prompt(FileChooserButton *self, const char* prompt) {
  g_return_if_fail(OGGEX_IS_FILECHOOSER(self));
  FileChooserButtonPrivate* priv = filechooserbutton_get_instance_private(self);
  priv->prompt = prompt;
}

static void filechooserbutton_set_file(FileChooserButton *self, GFile *file) {
  FileChooserButtonPrivate* priv = filechooserbutton_get_instance_private(self);
  priv->file = file;
}

static void filechooserbutton_set_fcn(FileChooserButton *self, GtkFileChooserNative* fcn) {
  g_return_if_fail(OGGEX_IS_FILECHOOSER(self));
  FileChooserButtonPrivate* priv = filechooserbutton_get_instance_private(self);
  priv->fc = fcn;
}

static void filechooserbutton_set_action(FileChooserButton *self, GtkFileChooserAction action) {
  g_return_if_fail(OGGEX_IS_FILECHOOSER(self));
  FileChooserButtonPrivate* priv = filechooserbutton_get_instance_private(self);
  priv->action = action;
}

/* Signal Handlers */
static void filechooserbutton_browse(GtkNativeDialog *native, int response, gpointer user_data) {
  if (response == GTK_RESPONSE_ACCEPT) {
    FileChooserButton *self = OGGEX_FILECHOOSER(user_data);
    g_return_if_fail(OGGEX_IS_FILECHOOSER(self));

    GtkFileChooser *chooser = GTK_FILE_CHOOSER (native);
    GFile *file = gtk_file_chooser_get_file (chooser);

    gtk_file_chooser_set_file(chooser, file, NULL);
  }
}

static void filechooserbutton_show(GtkButton* self, gpointer user_data) {
  FileChooserButton *fcb = OGGEX_FILECHOOSER(user_data);
  g_return_if_fail(OGGEX_IS_FILECHOOSER(fcb));

  FileChooserButtonPrivate* priv = filechooserbutton_get_instance_private(fcb);
  gtk_native_dialog_show(GTK_NATIVE_DIALOG (priv->fc));
}

/* Class Constructor */
FileChooserButton* filechooserbutton_new(const char* prompt, const char* filter, GtkFileChooserAction action) {
  FileChooserButton* fcb = g_object_new (FILECHOOSER_BUTTON_TYPE_FILECHOOSER, NULL);
  puts("FileChooserButton initialized");

  FileChooserButtonPrivate *priv = filechooserbutton_get_instance_private(fcb);
  puts("FileChooserButtonPrivate initialized");

  /* Set the fields for the file chooser */
  puts("Setting FileChooserButton fields");
  priv->prompt = malloc(strlen(prompt));
  priv->prompt = prompt;
  priv->action = action;

  /* Create the file chooser native widget */
  puts("Setting file chooser");
  GtkFileChooserNative* native = gtk_file_chooser_native_new(prompt, NULL, action, "_Select", "_Cancel");
  priv->fc = native;

  /* Set the file filters for the chooser */
  puts("Setting file filter");
  GtkFileFilter *file_filter = gtk_file_filter_new();
  gtk_file_filter_add_pattern(file_filter, filter);
  priv->file_filter = file_filter;

  /* Show the GTK dialog on button click */
  puts("Setting button callback");
  g_signal_connect(GTK_BUTTON(&fcb->parent_instance), "clicked", G_CALLBACK (filechooserbutton_show), G_OBJECT(fcb));

  /* Browse for files using the dialog */
  puts("Setting dialog callback");
  g_signal_connect(GTK_WIDGET(&priv->fc), "response", G_CALLBACK (filechooserbutton_browse), G_OBJECT(fcb));
  return fcb;
}
