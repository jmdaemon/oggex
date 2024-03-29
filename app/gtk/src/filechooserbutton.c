#include "filechooserbutton.h"
#include "oggex-config.h"

/* Private member variables */
typedef struct {
  const char* prompt;
  bool shortpaths;
  GFile *file;
  GtkFileChooserNative *fc;
  GtkFileFilter *file_filter; 
  GtkFileChooserAction action;
} FileChooserButtonPrivate;

G_DEFINE_TYPE_WITH_PRIVATE(FileChooserButton, filechooserbutton, GTK_TYPE_BUTTON)

static void filechooserbutton_class_init (FileChooserButtonClass *klass) {
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);
  gtk_widget_class_set_template_from_resource (widget_class, UI_FILE_CHOOSER_BUTTON);
}

static void filechooserbutton_init (FileChooserButton *self) {
  gtk_widget_init_template (GTK_WIDGET (self));
}

/* Getters */
const char* filechooserbutton_get_prompt(FileChooserButton *self) {
  FileChooserButtonPrivate* priv = filechooserbutton_get_instance_private(self);
  return priv->prompt;
}

bool filechooserbutton_get_shortpaths(FileChooserButton *self) {
  FileChooserButtonPrivate* priv = filechooserbutton_get_instance_private(self);
  return priv->shortpaths;
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

static void filechooserbutton_set_shortpaths(FileChooserButton *self, bool shortpaths) {
  g_return_if_fail(OGGEX_IS_FILECHOOSER(self));
  FileChooserButtonPrivate* priv = filechooserbutton_get_instance_private(self);
  priv->shortpaths = shortpaths;
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
  puts("Browsing Files");
  if (response == GTK_RESPONSE_ACCEPT) {

    FileChooserButton *self = OGGEX_FILECHOOSER(user_data);
    g_return_if_fail(OGGEX_IS_FILECHOOSER(self));

    GtkFileChooser *chooser = GTK_FILE_CHOOSER (native);
    g_return_if_fail(GTK_IS_FILE_CHOOSER(chooser));

    GFile *file = gtk_file_chooser_get_file (chooser);

    if (file != NULL) {
      const char* path = g_file_get_path(file);
      printf("Selected: %s\n", path);

      filechooserbutton_set_file(self, file);
      gtk_file_chooser_set_file(chooser, file, NULL);

      const char* shortpath = g_file_get_basename(file);

      FileChooserButton* btn = self;
      gtk_button_set_label(GTK_BUTTON(btn), shortpath);
    }
  }
}

static void filechooserbutton_show(GtkButton* self, gpointer user_data) {
  FileChooserButton *fcb = OGGEX_FILECHOOSER(user_data);
  g_return_if_fail(OGGEX_IS_FILECHOOSER(fcb));

  FileChooserButtonPrivate* priv = filechooserbutton_get_instance_private(fcb);
  gtk_native_dialog_show(GTK_NATIVE_DIALOG (priv->fc));
}

/* Class Constructor */
FileChooserButton* filechooserbutton_new(const char* prompt, const char* filter, bool shortpaths, GtkFileChooserAction action) {
  FileChooserButton* fcb = g_object_new (FILECHOOSER_BUTTON_TYPE_FILECHOOSER, NULL);
  puts("FileChooserButton initialized");

  FileChooserButtonPrivate *priv = filechooserbutton_get_instance_private(fcb);
  puts("FileChooserButtonPrivate initialized");

  /* Set the fields for the file chooser */
  puts("Setting FileChooserButton fields");
  /*priv->prompt = malloc(strlen(prompt) + 1);*/
  priv->prompt = prompt;
  priv->shortpaths = true;
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

  /* Browse for files using the dialog */
  puts("Setting dialog callback");
  g_signal_connect(priv->fc, "response", G_CALLBACK (filechooserbutton_browse), G_OBJECT(fcb));

  /* Show the GTK dialog on button click */
  puts("Setting button callback");
  g_signal_connect(&fcb->parent_instance, "clicked", G_CALLBACK (filechooserbutton_show), G_OBJECT(fcb));
  return fcb;
}
