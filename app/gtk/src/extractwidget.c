#include "extractwidget.h"
#include "oggex-config.h"

typedef struct {
  int thing;
} ExtractWidgetPrivate;

G_DEFINE_TYPE_WITH_PRIVATE (ExtractWidget, extract_widget, GTK_TYPE_GRID)

static void extract_widget_class_init (ExtractWidgetClass *klass) {
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);
  gtk_widget_class_set_template_from_resource (widget_class, UI_EXTRACT_WIDGET);
}

static void extract_widget_init (ExtractWidget *self) {
  gtk_widget_init_template (GTK_WIDGET (self));
}

ExtractWidget* extract_widget_new (void) {
  return g_object_new (EXTRACT_WIDGET_TYPE_WIDGET, NULL);
}
