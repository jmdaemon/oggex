#include "extractwidget.h"

typedef struct {
  const char* path; /* TODO: Replace with Media media struct */
} ExtractWidgetPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (ExtractWidget, extract_widget, GTK_TYPE_GRID)

static void extract_widget_class_init (ExtractWidgetClass *klass) {
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  /* TODO: Free resource in oggex window destructor */
  const char* resource = "/io/github/com/jmdaemon/oggex/../../../resources/gtk/extractwidget.ui";
  gtk_widget_class_set_template_from_resource (widget_class, resource);

  /*free(resource);*/
}

static void extract_widget_init (ExtractWidget *self) {
  gtk_widget_init_template (GTK_WIDGET (self));
}

ExtractWidget* extract_widget_new (void) {
  return g_object_new (EXTRACT_WIDGET_TYPE_WIDGET, NULL);
}
