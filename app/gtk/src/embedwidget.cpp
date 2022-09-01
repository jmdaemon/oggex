#include "embedwidget.h"
#include "oggex_gtk.h"

typedef struct {
  int thing;
} EmbedWidgetPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (EmbedWidget, embed_widget, GTK_TYPE_GRID)

static void embed_widget_class_init (EmbedWidgetClass *klass) {
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);
  gtk_widget_class_set_template_from_resource(widget_class, UI_EMBED_WIDGET);

  gtk_widget_class_bind_template_child(widget_class, EmbedWidget, lbl_dest);
  gtk_widget_class_bind_template_child(widget_class, EmbedWidget, lbl_tag);
  gtk_widget_class_bind_template_child(widget_class, EmbedWidget, lbl_image);
  gtk_widget_class_bind_template_child(widget_class, EmbedWidget, lbl_audio);
  gtk_widget_class_bind_template_child(widget_class, EmbedWidget, lbl_embed);
  gtk_widget_class_bind_template_child(widget_class, EmbedWidget, e_tag);
  gtk_widget_class_bind_template_child(widget_class, EmbedWidget, e_dest);
  gtk_widget_class_bind_template_child(widget_class, EmbedWidget, btn_embed);
}

static void embed_widget_init (EmbedWidget *self) {
  gtk_widget_init_template (GTK_WIDGET (self));
}

static void embed_callback(GtkButton* /* self */, gpointer user_data) {
  EmbedWidget* embedwidget = OGGEX_EMBED_WIDGET(user_data);

  SPDLOG_INFO("Reading embed form data");
  
  FileChooserButton *fcb_image = embedwidget->fcb_image;
  g_return_if_fail(OGGEX_IS_FILECHOOSER(fcb_image));

  GFile *file_image = filechooserbutton_get_file(fcb_image);
  const char* image = g_file_get_path(file_image);

  /* Get audio file name */
  FileChooserButton *fcb_audio = embedwidget->fcb_audio;
  g_return_if_fail(OGGEX_IS_FILECHOOSER(fcb_audio));

  GFile *file_audio = filechooserbutton_get_file(fcb_audio);
  const char* audio = g_file_get_path(file_audio);

  /* Get sound tag */
  GtkEntry* e_tag = embedwidget->e_tag;
  GtkEntryBuffer* e_tag_buffer = gtk_entry_get_buffer(e_tag);
  const char* tag = gtk_entry_buffer_get_text(e_tag_buffer);

  /* Get dest output file name */
  GtkEntry* e_dest = embedwidget->e_dest;
  GtkEntryBuffer* e_dest_buffer = gtk_entry_get_buffer(e_dest);
  const char* dest = gtk_entry_buffer_get_text(e_dest_buffer);

  /* Construct the arguments struct */
  SPDLOG_INFO("Setting arguments");
  args.sound.src = (char*) audio;
  args.sound.image = (char*) image;
  args.sound.tag = (char*) tag;
  args.sound.dest = (char*) dest;

  args.sound.temp = (char*) "temp.ogg";
  args.sound.log = (char*) "log.ogg";

  SPDLOG_DEBUG("args.sound.src   : {}", args.sound.src);
  SPDLOG_DEBUG("args.sound.image : {}", args.sound.image);
  SPDLOG_DEBUG("args.sound.tag   : {}", args.sound.tag);
  SPDLOG_DEBUG("args.sound.dest  : {}", args.sound.dest);

  SPDLOG_DEBUG("args.sound.temp  : {}", args.sound.temp);
  SPDLOG_DEBUG("args.sound.log   : {}", args.sound.log);

  Sound sound = args.sound;
  Settings settings = { 10, false };
  Media media = {sound, settings, args};

  /* Embed Files */
  SPDLOG_INFO("Embedding Files ...");
  embed(media);
}

EmbedWidget* embed_widget_new (void) {
  EmbedWidget* result = (EmbedWidget*) g_object_new (EMBED_WIDGET_TYPE_WIDGET, NULL);

  /* Add file choosers to embed_widget */
  result->fcb_image = filechooserbutton_new("Open Image", "Image Files (*.png *.jpg *.bmp)", true, GTK_FILE_CHOOSER_ACTION_OPEN);
  result->fcb_audio = filechooserbutton_new("Open Audio", "Audio Files (*.ogg)", true, GTK_FILE_CHOOSER_ACTION_OPEN);
  gtk_grid_attach(GTK_GRID(result), GTK_WIDGET(result->fcb_image), 1, 1, 1, 1);
  gtk_grid_attach(GTK_GRID(result), GTK_WIDGET(result->fcb_audio), 1, 2, 1, 1);

  /* Setup embed callback */
  g_signal_connect(result->btn_embed, "clicked", G_CALLBACK(embed_callback), G_OBJECT(result));
  return result;
}
