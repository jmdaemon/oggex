#include "extractwidget.h"
#include "oggex_gtk.h"

typedef struct {
  int thing;
} ExtractWidgetPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (ExtractWidget, extract_widget, GTK_TYPE_GRID)

static void extract_widget_class_init (ExtractWidgetClass *klass) {
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);
  gtk_widget_class_set_template_from_resource (widget_class, UI_EXTRACT_WIDGET);

  gtk_widget_class_bind_template_child(widget_class, ExtractWidget, lbl_extract);
  gtk_widget_class_bind_template_child(widget_class, ExtractWidget, lbl_embedded);
  gtk_widget_class_bind_template_child(widget_class, ExtractWidget, lbl_dest);
  gtk_widget_class_bind_template_child(widget_class, ExtractWidget, btn_extract);
}

static void extract_widget_init (ExtractWidget *self) {
  gtk_widget_init_template (GTK_WIDGET (self));
}

static void extract_callback(GtkButton* /*self */, gpointer user_data) {
  ExtractWidget* extractwidget = OGGEX_EXTRACT_WIDGET(user_data);
  SPDLOG_INFO("Reading form data");

  /* Get embedded file path */
  FileChooserButton *fcb_embedded = extractwidget->fcb_embedded;
  g_return_if_fail(OGGEX_IS_FILECHOOSER(fcb_embedded));
  GFile *file_embedded = filechooserbutton_get_file(fcb_embedded);
  const char* embedded = g_file_get_path(file_embedded);

  /* Get dest file diretory */
  FileChooserButton *fcb_dest = extractwidget->fcb_dest;
  g_return_if_fail(OGGEX_IS_FILECHOOSER(fcb_dest));
  GFile *file_dest = filechooserbutton_get_file(fcb_dest);
  const char* dest = g_file_get_path(file_dest);

  /* Construct the arguments struct */
  SPDLOG_INFO("Setting arguments");
  args.sound.image = (char*) embedded;
  args.sound.dest = (char*) dest;

  args.sound.temp = (char*) "temp.ogg";
  args.sound.log = (char*) "log.ogg";

  SPDLOG_DEBUG("args.sound.image : {}", args.sound.image);
  SPDLOG_DEBUG("args.sound.dest  : {}", args.sound.dest);

  SPDLOG_DEBUG("args.sound.temp  : {}", args.sound.temp);
  SPDLOG_DEBUG("args.sound.log   : {}", args.sound.log);

  Sound sound = args.sound;
  Settings settings = { 10, false };
  Media media = {sound, settings, args};

  /* Embed Files */
  SPDLOG_INFO("Extracting Files ...");
  extract(media);
}

ExtractWidget* extract_widget_new (void) {
  ExtractWidget* result = (ExtractWidget*) g_object_new (EXTRACT_WIDGET_TYPE_WIDGET, NULL);

  /* Add file choosers to widget */
  result->fcb_embedded = filechooserbutton_new("Open Image", "Image Files (*.png *.jpg *.bmp)", true, GTK_FILE_CHOOSER_ACTION_OPEN);
  result->fcb_dest = filechooserbutton_new("Select Folder", "Folders (*)", true, GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER);

  gtk_grid_attach(GTK_GRID(result), GTK_WIDGET(result->fcb_embedded), 1, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(result), GTK_WIDGET(result->fcb_dest), 1, 2, 1, 1);

  /* Setup callback */
  g_signal_connect(result->btn_extract, "clicked", G_CALLBACK(extract_callback), G_OBJECT(result));
  
  /* Set minimum sizes */
  gtk_widget_set_size_request(GTK_WIDGET(result->fcb_embedded), 400, 30);
  gtk_widget_set_size_request(GTK_WIDGET(result->fcb_dest), 400, 30);

  // Autocomplete fields
  Sound sound = args.sound;
  if (sound.image != nullptr) {
    GFile *file = g_file_new_for_path(sound.image);
    const char* shortpath = g_file_get_basename(file);
    gtk_button_set_label(GTK_BUTTON(result->fcb_embedded), shortpath);
  }

  if (sound.dest != nullptr) {
    GFile *file = g_file_new_for_path(sound.dest);
    const char* shortpath = g_file_get_basename(file);
    gtk_button_set_label(GTK_BUTTON(result->fcb_dest), shortpath);
  }

  return result;
}
