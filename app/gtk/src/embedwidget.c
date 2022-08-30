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

  /*free(resource);*/
}

static void embed_widget_init (EmbedWidget *self) {
  gtk_widget_init_template (GTK_WIDGET (self));
}

EmbedWidget* embed_widget_new (void) {
  return g_object_new (EMBED_WIDGET_TYPE_WIDGET, NULL);
}
