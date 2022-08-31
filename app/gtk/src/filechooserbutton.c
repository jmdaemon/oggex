#include "filechooserbutton.h"

/* Private member variables */
typedef struct {
  const char* prompt;
  /*const char* filter; */
  /*const char* path;*/

  /*GFile *file;*/

  GtkFileChooserNative *fc;

  GtkFileFilter *file_filter; 

  /*GtkFileChooser *chooser;*/
  /*GtkFileChooserNative *native;*/

  GtkFileChooserAction action;
} FileChooserButtonPrivate;

/*G_DEFINE_TYPE_WITH_PRIVATE (FileChooserButton, embed_widget, GTK_TYPE_GRID)*/
/*G_DEFINE_TYPE_WITH_PRIVATE(FileChooserButton, embed_widget, GTK_TYPE_BUTTON)*/
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

/*
FileChooserButton* embed_widget_new (void) {
  return g_object_new (FILECHOOSER_BUTTON_TYPE_WIDGET, NULL);
}
*/

/* Getters */

/* Access the private member variables of the file chooser button */

/*FileChooserButtonPrivate* filechooserbutton_get_private(FileChooserButton *self) {*/
  /*FileChooserButtonPrivate* priv = G_TYPE_CLASS_GET_PRIVATE(self, FILECHOOSER_BUTTON_TYPE_WIDGET, FileChooserButtonPrivate);*/
  /*return priv;*/
/*}*/

const char* filechooserbutton_get_prompt(FileChooserButton *self) {
  FileChooserButtonPrivate* priv = filechooserbutton_get_instance_private(self);
  return priv->prompt;
}

/*GFile* filechooserbutton_get_file(FileChooserButton *self) {*/
  /*FileChooserButtonPrivate* priv = filechooserbutton_get_instance_private(self);*/
  /*return priv->file;*/
/*}*/

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

/*static void filechooserbutton_set_file(FileChooserButton *self, GFile *file) {*/
  /*FileChooserButtonPrivate* priv = filechooserbutton_get_instance_private(self);*/
  /*priv->file = file;*/
/*}*/

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

/*static void filechooserbutton_browse(FileChooserButton *self, int response) {*/
/*static void filechooserbutton_browse(FileChooserButton *self, GtkNativeDialog *native, int response) {*/

static void filechooserbutton_browse(GtkNativeDialog *native, int response, gpointer user_data) {
/*static void filechooserbutton_browse(GtkNativeDialog *native, int response) {*/
  if (response == GTK_RESPONSE_ACCEPT) {
    /*FileChooserButton *self = (native);*/
    /*GtkFileChooser *chooser = GTK_FILE_CHOOSER(filechooserbutton_get_fcn(self));*/
    /*FileChooserButton *self = (FileChooserButton*) user_data;*/
    /*FileChooserButton *self = OGGEX_FILECHOOSER(user_data);*/
    FileChooserButton *self = OGGEX_FILECHOOSER(user_data);
    g_return_if_fail(OGGEX_IS_FILECHOOSER(self));

    GtkFileChooser *chooser = GTK_FILE_CHOOSER (native);
    GFile *file = gtk_file_chooser_get_file (chooser);

    /*filechooserbutton_set_file(self, file);*/
    gtk_file_chooser_set_file(chooser, file, NULL);

    /*save_to_file (file);*/

    /*g_object_unref (file);*/
  }

  /*g_object_unref (native);*/

  /*gtk_file_chooser_get_file()*/
}

/*static void filechooserbutton_show(FileChooserButton *self) {*/
/*static void filechooserbutton_show(gpointer user_data) {*/
static void filechooserbutton_show(GtkButton* self, gpointer user_data) {

  /*filechooserbutton_browse()*/
  /*FileChooserButton *self = (FileChooserButton*) user_data;*/
  /*FileChooserButtonPrivate* priv = filechooserbutton_get_instance_private(self);*/

  /*FileChooserButton *fcb = (FileChooserButton*) user_data;*/
  FileChooserButton *fcb = OGGEX_FILECHOOSER(user_data);
  g_return_if_fail(OGGEX_IS_FILECHOOSER(fcb));

  FileChooserButtonPrivate* priv = filechooserbutton_get_instance_private(fcb);
  gtk_native_dialog_show(GTK_NATIVE_DIALOG (priv->fc));
}

/* Class Constructor */

/*FileChooserButton* filechooserbutton_new(const char* prompt, const char* lbl_accept, const char* lbl_cancel, GtkFileChooserAction action) {*/
/*FileChooserButton* filechooserbutton_new(const char* prompt, GtkFileChooserAction action) {*/
FileChooserButton* filechooserbutton_new(const char* prompt, const char* filter, GtkFileChooserAction action) {
  /*FileChooserButtonPrivate priv = G_TYPE_INSTANCE_GET_PRIVATE(fcb, FILECHOOSER_BUTTON_TYPE_WIDGET, FileChooserButtonPrivate);*/
  /*FileChooserButton* fcb = g_object_new (FILECHOOSER_BUTTON_TYPE_WIDGET, NULL);*/
  /*FileChooserButton* fcb = g_object_new (FILECHOOSER_BUTTON_TYPE_BUTTON, NULL);*/
  FileChooserButton* fcb = g_object_new (FILECHOOSER_BUTTON_TYPE_FILECHOOSER, NULL);
  puts("FileChooserButton initialized");
  puts("Getting private fields");
  FileChooserButtonPrivate *priv = filechooserbutton_get_instance_private(fcb);
  /*FileChooserButtonPrivate* priv = filechooserbutton_get_private(fcb);*/
  /*FileChooserButtonPrivate* priv = G_TYPE_CLASS_GET_PRIVATE(fcb, FILECHOOSER_BUTTON_TYPE_WIDGET, FileChooserButtonPrivate);*/
  /*FileChooserButtonPrivate* priv = g_type_instance_get_private(fcb, FILECHOOSER_BUTTON_TYPE_WIDGET);*/
  puts("FileChooserButtonPrivate initialized");
  /*priv->prompt = prompt;*/
  /*priv->action = action;*/

  /* Set the fields for the file chooser */
  puts("Setting FileChooserButton fields");
  priv->prompt = malloc(strlen(prompt));
  priv->prompt = prompt;
  /*priv->file = NULL;*/
  /*priv->file = GFile;*/
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
  /*g_object_set_data();*/

  /*GtkFileFilter();*/
  /*gtk_file_chooser_add_filter();*/



  puts("Setting callbacks");
  /* Show the GTK dialog on button click */
  /*g_signal_connect(&fcb->parent_instance, "clicked", G_CALLBACK (filechooserbutton_show), &fcb);*/
  puts("Setting button callback");
  /*g_signal_connect(&fcb->parent_instance, "clicked", G_CALLBACK (filechooserbutton_show), &fcb);*/

  /*g_signal_connect(&fcb->parent_instance, "clicked", G_CALLBACK (filechooserbutton_show), fcb);*/
  /*g_signal_connect(&fcb->parent_instance, "click", G_CALLBACK (filechooserbutton_show), &fcb);*/

  /* Browse for files using the dialog */
  puts("Setting dialog callback");
  /*g_signal_connect(&priv->fc, "response", G_CALLBACK (filechooserbutton_browse), &fcb);*/
  /*g_signal_connect(priv->fc, "response", G_CALLBACK (filechooserbutton_browse), fcb);*/

  /*g_signal_connect(native, "response", G_CALLBACK (filechooserbutton_browse), fcb);*/

  /*g_signal_connect(native, "response", G_CALLBACK (filechooserbutton_browse), NULL);*/

  /*g_signal_connect (native, "response", G_CALLBACK (on_response), NULL);*/



  /*GtkFileChooserNative* native = gtk_file_chooser_native_new(prompt, NULL, action, lbl_accept, lbl_cancel);*/
  /*priv->chooser = GTK_FILE_CHOOSER(native);*/
  /*priv->native = native;*/
  /*priv->fc = native;*/
  return fcb;
}


/*static void on_response (GtkNativeDialog *native, int response) {*/
  /*if (response == GTK_RESPONSE_ACCEPT) {*/
      /*GtkFileChooser *chooser = GTK_FILE_CHOOSER (native);*/
      /*GFile *file = gtk_file_chooser_get_file (chooser);*/

      /*[>save_to_file (file);<]*/

      /*g_object_unref (file);*/
    /*}*/

  /*g_object_unref (native);*/
/*}*/
/*GTK_TYPE_FILE_CHOOSER_ACTION_SAVE_FILE*/
/*GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER;*/

  /*GtkFileChooserNative *native;*/
  /*GtkFileChooser *chooser;*/
  /*GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;*/

  /*native = gtk_file_chooser_native_new ("Save File",*/
                                        /*parent_window,*/
                                        /*action,*/
                                        /*"_Save",*/
                                        /*"_Cancel");*/
  /*chooser = GTK_FILE_CHOOSER (native);*/

  /*if (user_edited_a_new_document)*/
    /*gtk_file_chooser_set_current_name (chooser, _("Untitled document"));*/
  /*else*/
    /*gtk_file_chooser_set_file (chooser, existing_file, NULL);*/

  /*g_signal_connect (native, "response", G_CALLBACK (on_response), NULL);*/
  /*gtk_native_dialog_show (GTK_NATIVE_DIALOG (native));*/
