#include "oggex-config.h"
#include "oggex-window.h"
#include "oggex_gtk_defs.h"

struct _OggexWindow {
  GtkApplicationWindow  parent_instance;

  /* Template widgets */
  GtkHeaderBar        *header_bar;
  GtkPaned            *home_paned;
  /*GtkStackSidebar     *home_stacksidebar;*/
  /*GtkStack            *home_stack;*/
  /*GtkStackPage        *page0;*/
  /*GtkLabel            *lbl_title;*/
  /*GtkStackPage        *page1;*/
  /*GtkStackPage        *page2;*/
  /*GtkLabel            *label;*/
};

G_DEFINE_TYPE (OggexWindow, oggex_window, GTK_TYPE_APPLICATION_WINDOW)

static void oggex_window_class_init (OggexWindowClass *klass) {
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  /*gtk_widget_class_set_template_from_resource (widget_class, "/io/github/com/jmdaemon/oggex/../../../resources/gtk/oggex-window.ui");*/
  /* TODO: Free resource in oggex window destructor */
  const char* resource = get_ui_resource(UI_OGGEX_WINDOW);
  gtk_widget_class_set_template_from_resource (widget_class, resource);
  gtk_widget_class_bind_template_child (widget_class, OggexWindow, header_bar);
  /*gtk_widget_class_bind_template_child (widget_class, OggexWindow, label);*/
  gtk_widget_class_bind_template_child (widget_class, OggexWindow, home_paned);
  /*gtk_widget_class_bind_template_child (widget_class, OggexWindow, home_stacksidebar);*/
  /*gtk_widget_class_bind_template_child (widget_class, OggexWindow, home_stack);*/
  /*gtk_widget_class_bind_template_child (widget_class, OggexWindow, page0);*/
  /*gtk_widget_class_bind_template_child (widget_class, OggexWindow, lbl_title);*/
  /*gtk_widget_class_bind_template_child (widget_class, OggexWindow, page1);*/
  /*gtk_widget_class_bind_template_child (widget_class, OggexWindow, page2);*/
  /*free(resource);*/
}

static void oggex_window_init (OggexWindow *self) {
  gtk_widget_init_template (GTK_WIDGET (self));
}
