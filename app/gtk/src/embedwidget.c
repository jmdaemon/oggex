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

/*#define EMBED_WIDGET(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), EMBED_WIDGET_TYPE_WIDGET, EmbedWidget))*/

EmbedWidget* embed_widget_new (void) {
  EmbedWidget* result = g_object_new (EMBED_WIDGET_TYPE_WIDGET, NULL);
  
  /*embed_widget_init(result);*/
  /*embed_widget_class_init(OGGEX_EMBED_WIDGET_CLASS(result));*/

  /*EmbedWidgetClass* widget_class = OGGEX_EMBED_WIDGET_CLASS(result);*/

  /*embed_widget_init(result);*/
  /*EmbedWidgetClass* widget_class = OGGEX_EMBED_WIDGET_GET_CLASS(result);*/
  /*EmbedWidgetClass* asdf = embed_widget_get_type();*/


  /*EmbedWidgetClass* widget_class = OGGEX_EMBED_WIDGET_CLASS(result);*/
  /*G_TYPE_INSTANCE_GET_CLASS(result, EMBED_WIDGET_TYPE_WIDGET, EmbedWidgetClass);*/

  /*EmbedWidgetClass* widget_class = EmbedWidgetClass(result);*/
  /*EmbedWidgetClass* widget_class = EMBED_WIDGET(result);*/

  /*widget_class->parent_instance*/

  puts("Before");
  /*EmbedWidgetClass* widget_class = OGGEX_EMBED_WIDGET_CLASS(result);*/
  /*GtkWidgetClass* widget_class = (EmbedWidgetClass*) OGGEX_EMBED_WIDGET_CLASS(result);*/
  /*EmbedWidgetClass* widget_class = OGGEX_EMBED_WIDGET_CLASS(self);*/

  /*GtkWidgetClass* widget_class = (EmbedWidgetClass*) OGGEX_EMBED_WIDGET_CLASS(result);*/
  /*GtkWidgetClass* widget_class = G_TYPE_INSTANCE_GET_CLASS(result, EMBED_WIDGET_TYPE_WIDGET, EmbedWidgetClass);*/

  /*EmbedWidgetClass* widget_class = G_TYPE_INSTANCE_GET_CLASS(result, EMBED_WIDGET_TYPE_WIDGET, EmbedWidgetClass);*/

  EmbedWidgetClass* widget_class = OGGEX_EMBED_WIDGET_GET_CLASS(result);
  /*GtkWidgetClass *klass = GTK_WIDGET_CLASS (widget_class);*/
  /*OGGEX_EMBED_WIDGET_CLASS(result)*/
  /*EmbedWidgetClass* widget_class = OGGEX_EMBED_WIDGET_CLASS(result);*/

  puts("After");
  
  /*if (OGGEX_IS_EMBED_WIDGET_CLASS(widget_class) != 0) {*/
    /*fprintf(stderr, "Embed Widget class is null. Exiting...");*/
    /*exit(1);*/
  /*}*/

  puts("Initializing fcb_image");
  widget_class->fcb_image = filechooserbutton_new("Open Image", "Image Files (*.png *.jpg *.bmp)", GTK_FILE_CHOOSER_ACTION_OPEN);
  printf("fcb_image %p\n", widget_class->fcb_image);
  /*widget_class->fcb_audio->parent_instance = *GTK_BUTTON(widget_class->fcb_image);*/

  puts("Initializing fcb_audio");
  widget_class->fcb_audio = filechooserbutton_new("Open Audio", "Audio Files (*.ogg)", GTK_FILE_CHOOSER_ACTION_OPEN);
  printf("fcb_audio %p\n", widget_class->fcb_audio);
  /*widget_class->fcb_audio->parent_instance = *GTK_BUTTON(widget_class->fcb_audio);*/

  puts("Adding fcb_image to Grid");
  /*GtkWidget* widget = GTK_WIDGET(widget_class->fcb_image);*/
  /*gtk_grid_attach(&result->parent_instance, widget, 1, 1, 1, 1);*/
  /*gtk_grid_attach(&result->parent_instance, GTK_WIDGET(GTK_GRID(widget_class->fcb_image)), 1, 1, 1, 1);*/
  /*GtkWidget* widget = GTK_WIDGET(&widget_class->fcb_image->parent_instance);*/
  /*GObject* widget = G_OBJECT(widget_class->fcb_image);*/
  /*gtk_grid_attach(&result->parent_instance, widget, 1, 1, 1, 1);*/
  /*GtkWidget* widget = GTK_WIDGET(widget_class->fcb_image->parent_instance->parent_instance);*/

  GtkGrid* grid = NULL;
  /*grid = &result->parent_instance;*/
  grid = &result->parent_instance;
  if (!grid) {
    fprintf(stderr, "embed_grid is null. Exiting...");
    exit(2);
  }
  printf("grid %p\n", grid);

  /*GtkButton btn = NULL;*/
  GtkButton* btn = NULL;
  /*GtkButton btn;*/
  btn = &widget_class->fcb_image->parent_instance;
  /*btn = &widget_class->fcb_image->parent_instance;*/
  /*btn = &widget_class->fcb_image->parent_instance;*/
  /*btn = GTK_BUTTON(&widget_class->fcb_image);*/
  /*btn = GTK_BUTTON(gtk_widget_get_root(GTK_WIDGET(widget_class->fcb_image)));*/
  /*btn = GTK_BUTTON(gtk_widget_get_root(GTK_WIDGET(widget_class->fcb_image)));*/

  /*GtkRoot* root = gtk_widget_get_root(GTK_WIDGET(widget_class->fcb_image));*/
  /*btn = GTK_BUTTON(root);*/

  if (!btn) {
    fprintf(stderr, "btn is null. Exiting...");
    exit(3);
  }
  printf("btn %p\n", btn);

  GtkWidget* widget = NULL;
  /*widget = GTK_WIDGET(btn);*/
  /*widget = GTK_WIDGET(btn);*/
  /*widget = GTK_WIDGET(&widget_class->fcb_image->parent_instance);*/
  /*widget = GTK_WIDGET(&widget_class->fcb_image);*/
  /*widget = &widget_class->fcb_image->parent_instance.parent_instance;*/
  /*widget = GTK_WIDGET(&widget_class->fcb_image->parent_instance.parent_instance);*/
  widget = &widget_class->fcb_image->parent_instance.parent_instance;
  if (!widget) {
    fprintf(stderr, "widget is null. Exiting...");
    exit(4);
  }

  GtkButton button;

  /*
  if(GTK_IS_WIDGET_CLASS(btn)) {
    widget = GTK_WIDGET(btn);
    if (!widget) {
      fprintf(stderr, "widget is null. Exiting...");
      exit(4);
    }
  }
  */
  printf("widget %p\n", widget);
    /*&widget_class->fcb_image->parent_instance.parent_instance;*/
  /*GtkWidget *widget = &widget_class->fcb_image->parent_instance.parent_instance;*/
  /*gtk_grid_attach(&result->parent_instance, widget, 1, 1, 1, 1);*/
  /*gtk_grid_attach(grid, widget, 1, 1, 1, 1);*/
  /**gtk_grid_attach(grid, widget, 1, 1, 1, 1);*/
  /*gtk_grid_attach(&result->parent_instance, GTK_WIDGET(&widget_class->fcb_image->parent_instance), 1, 1, 1, 1);*/
  /*gtk_grid_attach(&result->parent_instance, widget, 1, 1, 1, 1);*/

  /*gtk_grid_attach(grid, widget, 1, 1, 1, 1);*/
  /*gtk_grid_attach(grid, GTK_WIDGET(&button), 1, 1, 1, 1);*/
  gtk_grid_attach(grid, GTK_WIDGET(btn), 1, 1, 1, 1);

  puts("Adding fcb_audio to Grid");
  /*gtk_grid_attach(&result->parent_instance, GTK_WIDGET(widget_class->fcb_audio), 1, 2, 1, 1);*/

  /*EmbedWidgetClass* widget_class = G_TYPE_INSTANCE_GET_CLASS(result, EMBED_WIDGET_TYPE_WIDGET, EmbedWidgetClass);*/
  
  /*result->fcb_image;*/

  /*GtkFileFilter *filter = gtk_file_filter_new ();*/
  /*gtk_file_filter_add_pattern (filter, "*");*/

  /*GtkFileFilter();*/
  /*gtk_file_chooser_add_filter();*/

  /*gtk_file_filter_get_name*/

  /*GtkFileChooser *chooser = GTK_FILE_CHOOSER(filechooserbutton_get_fcn(widget_class->fcb_image));*/



  /*EmbedWidgetPrivate* priv = G_TYPE_CLASS_GET_PRIVATE(result, EMBED_WIDGET_TYPE_WIDGET, EmbedWidgetPrivate);*/
  /*EmbedWidgetClass* priv = EMBED_WIDGET_TYPE_WIDGET(result, EMBED_WIDGET_TYPE_WIDGET);*/
  /*priv->btn = filechooserbutton_new("");*/
  /*return g_object_new (EMBED_WIDGET_TYPE_WIDGET, NULL);*/

  /* Add the file chooser widgets to the embed_widget user interface */
  /*gtk_grid_attach(widget_class->parent_instance, widget_class->fcb_image, 1, 1, 1, 1);*/
  /*gtk_grid_attach(&result->parent_instance, widget_class->fcb_image, 1, 1, 1, 1);*/


  /*gtk_grid_attach(&self->parent_instance, GTK_WIDGET(widget_class->fcb_image), 1, 1, 1, 1);*/
  /*gtk_grid_attach(&self->parent_instance, GTK_WIDGET(widget_class->fcb_audio), 1, 2, 1, 1);*/


  return result;
}
