#include "embedwidget.h"

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

EmbedWidget* embed_widget_new (void) {
  EmbedWidget* result = g_object_new (EMBED_WIDGET_TYPE_WIDGET, NULL);
  EmbedWidgetClass* widget_class = OGGEX_EMBED_WIDGET_GET_CLASS(result);
  
  if (!widget_class) {
    fprintf(stderr, "Embed Widget class is null. Exiting...");
    exit(1);
  }

  puts("Initializing fcb_image");
  widget_class->fcb_image = filechooserbutton_new("Open Image", "Image Files (*.png *.jpg *.bmp)", GTK_FILE_CHOOSER_ACTION_OPEN);
  printf("fcb_image %p\n", widget_class->fcb_image);

  puts("Initializing fcb_audio");
  widget_class->fcb_audio = filechooserbutton_new("Open Audio", "Audio Files (*.ogg)", GTK_FILE_CHOOSER_ACTION_OPEN);
  printf("fcb_audio %p\n", widget_class->fcb_audio);

  puts("Adding fcb_image to Grid");

  /*EmbedWidget* grid = &result->parent_instance;*/
  EmbedWidget* grid = result;
  if (!grid) {
    fprintf(stderr, "embed_grid is null. Exiting...");
    exit(2);
  }
  printf("grid %p\n", grid);

  FileChooserButton* image = widget_class->fcb_image;
  if (!image) {
    fprintf(stderr, "image widget is null. Exiting...");
    exit(4);
  }
  printf("image %p\n", image);

  FileChooserButton* audio = widget_class->fcb_audio;
  if (!audio) {
    fprintf(stderr, "audio widget is null. Exiting...");
    exit(4);
  }
  printf("audio %p\n", audio);

  puts("Adding fcb_image to Grid");
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(image), 1, 1, 1, 1);

  puts("Adding fcb_audio to Grid");
  gtk_grid_attach(GTK_GRID(grid), GTK_WIDGET(audio), 1, 2, 1, 1);
  return result;
}
