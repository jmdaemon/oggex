#include "oggex-config.h"
#include "oggex-window.h"
#include "oggex_gtk_defs.h"

const char* get_ui_resource(const char* ui_file) {
  unsigned int fname_size = strlen(APP_ID) + strlen(RESOURCES_DIR) + strlen(RESOURCES_GTK_DIR) + 3;
  char* result = malloc(fname_size);

  sprintf(result, "%s/%s/%s/%s", APP_ID, RESOURCES_DIR, RESOURCES_GTK_DIR, ui_file);
  return result;
}

struct _OggexWindow {
  GtkApplicationWindow  parent_instance;

  /* Template widgets */
  GtkHeaderBar        *header_bar;
  GtkLabel            *label;
};

G_DEFINE_TYPE (OggexWindow, oggex_window, GTK_TYPE_APPLICATION_WINDOW)

static void oggex_window_class_init (OggexWindowClass *klass) {
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  /*gtk_widget_class_set_template_from_resource (widget_class, "/io/github/com/jmdaemon/oggex/../../../resources/gtk/oggex-window.ui");*/
  /* TODO: Free resource in oggex window destructor */
  const char* resource = get_ui_resource(UI_OGGEX_WINDOW);
  gtk_widget_class_set_template_from_resource (widget_class, resource);
  gtk_widget_class_bind_template_child (widget_class, OggexWindow, header_bar);
  gtk_widget_class_bind_template_child (widget_class, OggexWindow, label);
  /*free(resource);*/
}

static void oggex_window_init (OggexWindow *self) {
  gtk_widget_init_template (GTK_WIDGET (self));
}
