#include "embedwidget.h"

#include "cli.h"
#include "oggex_gtk.h"

typedef struct {
  const char* path; /* TODO: Replace with Media media struct */
} EmbedWidgetPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (EmbedWidget, embed_widget, GTK_TYPE_GRID)

static void embed_widget_class_init (EmbedWidgetClass *klass) {
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  /* TODO: Free resource in oggex window destructor */
  const char* resource = "/io/github/com/jmdaemon/oggex/../../../resources/gtk/embedwidget.ui";
  gtk_widget_class_set_template_from_resource (widget_class, resource);

  gtk_widget_class_bind_template_child(widget_class, EmbedWidgetClass, lbl_dest);
  gtk_widget_class_bind_template_child(widget_class, EmbedWidgetClass, lbl_tag);
  gtk_widget_class_bind_template_child(widget_class, EmbedWidgetClass, lbl_image);
  gtk_widget_class_bind_template_child(widget_class, EmbedWidgetClass, lbl_audio);
  gtk_widget_class_bind_template_child(widget_class, EmbedWidgetClass, lbl_embed);
  gtk_widget_class_bind_template_child(widget_class, EmbedWidgetClass, e_tag);
  gtk_widget_class_bind_template_child(widget_class, EmbedWidgetClass, e_dest);
  gtk_widget_class_bind_template_child(widget_class, EmbedWidgetClass, btn_embed);
  /*free(resource);*/
}

static void embed_widget_init (EmbedWidget *self) {
  gtk_widget_init_template (GTK_WIDGET (self));
}

void embed_callback(GtkButton* self, gpointer user_data) {
  EmbedWidget* embedwidget = OGGEX_EMBED_WIDGET(user_data);
  EmbedWidgetClass* widget_class = OGGEX_EMBED_WIDGET_GET_CLASS(embedwidget);

  //SPDLOG_INFO("Reading embed form data");
  puts("Reading embed form data");

  /* Get image file name */
  FileChooserButton *fcb_image = widget_class->fcb_image;
  g_return_if_fail(OGGEX_IS_FILECHOOSER(fcb_image));

  GFile *file_image = filechooserbutton_get_file(fcb_image);
  const char* image = g_file_get_path(file_image);

  /* Get audio file name */
  FileChooserButton *fcb_audio = widget_class->fcb_audio;
  g_return_if_fail(OGGEX_IS_FILECHOOSER(fcb_audio));

  GFile *file_audio = filechooserbutton_get_file(fcb_audio);
  const char* audio = g_file_get_path(file_audio);

  /* Get sound tag */
  GtkEntry* e_tag = widget_class->e_tag;
  GtkEntryBuffer* e_tag_buffer = gtk_entry_get_buffer(e_tag);
  const char* tag = gtk_entry_buffer_get_text(e_tag_buffer);

  /* Get dest output file name */
  GtkEntry* e_dest = widget_class->e_dest;
  GtkEntryBuffer* e_dest_buffer = gtk_entry_get_buffer(e_dest);
  const char* dest = gtk_entry_buffer_get_text(e_dest_buffer);

  /* Construct the arguments struct */

  //SPDLOG_DEBUG("image : {}", image);
  //SPDLOG_DEBUG("audio : {}", audio);
  //SPDLOG_DEBUG("tag   : {}", tag);
  //SPDLOG_DEBUG("dest  : {}", dest);

  printf("image : %s\n", image);
  printf("audio : %s\n", audio);
  printf("tag   : %s\n", tag);
  printf("dest  : %s\n", dest);

  //struct arguments args = set_default_args();
  //SPDLOG_INFO("Setting arguments");
  puts("Setting arguments");
  args.sound.image = (char*) image;
  args.sound.src = (char*) audio;
  args.sound.tag = (char*) tag;
  args.sound.dest = (char*) dest;

  Settings settings = { 10, false };
  Media media = {args.sound, settings, args};
  /*Media media = {sound, settings, args};*/

  /* Call embed */
  //SPDLOG_INFO("Embedding Files ...");
  puts("Embedding Files ...");
  embed(media);
  //args.verbose = 1;
  //setup_logging(args);
  //embed(media);

  /*FileChooserButton *fcb = OGGEX_FILECHOOSER(user_data);*/
  /*g_return_if_fail(OGGEX_IS_FILECHOOSER(fcb));*/

  /*GFile *file = filechooserbutton_get_file(fcb);*/
  /*const char* path = g_file_get_path(file);*/

  /*FileChooserButtonPrivate* priv = filechooserbutton_get_instance_private(fcb);*/

}

EmbedWidget* embed_widget_new (void) {
  //EmbedWidget* result = g_object_new (EMBED_WIDGET_TYPE_WIDGET, NULL);
  EmbedWidget* result = (EmbedWidget*) g_object_new (EMBED_WIDGET_TYPE_WIDGET, NULL);
  EmbedWidgetClass* widget_class = OGGEX_EMBED_WIDGET_GET_CLASS(result);
  
  if (!widget_class) {
    fprintf(stderr, "Embed Widget class is null. Exiting...");
    exit(1);
  }

  puts("Initializing fcb_image");
  widget_class->fcb_image = filechooserbutton_new("Open Image", "Image Files (*.png *.jpg *.bmp)", true, GTK_FILE_CHOOSER_ACTION_OPEN);
  //printf("fcb_image %p\n", widget_class->fcb_image);
  printf("fcb_image %p\n", (void*) widget_class->fcb_image);

  puts("Initializing fcb_audio");
  widget_class->fcb_audio = filechooserbutton_new("Open Audio", "Audio Files (*.ogg)", true, GTK_FILE_CHOOSER_ACTION_OPEN);
  //printf("fcb_audio %p\n", widget_class->fcb_audio);
  printf("fcb_audio %p\n", (void*) (void*) (void*) (void*) (void*) (void*) (void*) (void*) (void*) widget_class->fcb_audio);

  puts("Adding fcb_image to Grid");

  /*EmbedWidget* grid = &result->parent_instance;*/
  EmbedWidget* grid = result;
  if (!grid) {
    fprintf(stderr, "embed_grid is null. Exiting...");
    exit(2);
  }
  //printf("grid %p\n", grid);
  printf("grid %p\n", (void*) grid);

  FileChooserButton* image = widget_class->fcb_image;
  if (!image) {
    fprintf(stderr, "image widget is null. Exiting...");
    exit(4);
  }
  //printf("image %p\n", image);
  printf("image %p\n", (void*) image);

  FileChooserButton* audio = widget_class->fcb_audio;
  if (!audio) {
    fprintf(stderr, "audio widget is null. Exiting...");
    exit(4);
  }
  //printf("audio %p\n", audio);
  printf("audio %p\n", (void*) audio);

  puts("Adding fcb_image to Grid");
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(image), 1, 1, 1, 1);

  puts("Adding fcb_audio to Grid");
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(audio), 1, 2, 1, 1);

  //GtkButton btn = GtkButton();
  //GtkButton btn = gtk_button_new();
  //widget_class->btn_embed = &btn;
  widget_class->btn_embed = (GtkButton*) gtk_button_new();
  GtkButton* btn_embed = widget_class->btn_embed;
  if (!btn_embed) {
    fprintf(stderr, "btn_embed widget is null. Exiting...");
    exit(5);
  }
  
  // Hook the button up to embed
  puts("Setting btn_embed callback");
  g_signal_connect(widget_class->btn_embed, "clicked", G_CALLBACK (embed_callback), G_OBJECT(result));
  //g_signal_connect(&btn, "clicked", G_CALLBACK (embed_callback), G_OBJECT(result));
  //g_signal_connect(GTK_BUTTON(&btn_embed), "clicked", G_CALLBACK (embed_callback), G_OBJECT(result));
  //g_signal_connect(GTK_BUTTON(btn_embed), "clicked", G_CALLBACK (embed_callback), G_OBJECT(result));
  //g_signal_connect(btn_embed, "clicked", G_CALLBACK (embed_callback), G_OBJECT(result));
  //g_signal_connect(widget_class->btn_embed, "clicked", G_CALLBACK (embed_callback), G_OBJECT(result));
  //g_signal_connect(GTK_BUTTON(&widget_class->btn_embed), "clicked", G_CALLBACK (embed_callback), G_OBJECT(result));
  //g_signal_connect(&widget_class->btn_embed, "clicked", G_CALLBACK (embed_callback), G_OBJECT(result));
  //g_signal_connect(widget_class->btn_embed, "clicked", G_CALLBACK (embed_callback), G_OBJECT(result));
  //g_signal_connect(GTK_BUTTON(&widget_class->btn_embed), "clicked", G_CALLBACK (embed_callback), G_OBJECT(result));
  //g_signal_connect(GTK_BUTTON(widget_class->btn_embed), "clicked", G_CALLBACK (embed_callback), G_OBJECT(result));

  return result;
  //g_signal_connect(GTK_BUTTON(&widget_class->btn_embed), "clicked", G_CALLBACK (embed_callback), G_OBJECT(result));
  //g_signal_connect(widget_class->btn_embed, "clicked", G_CALLBACK (embed_callback), G_OBJECT(result));
  /*g_signal_connect(widget_class->btn_embed, "clicked", G_CALLBACK (embed_callback), G_OBJECT(widget_class));*/

}
