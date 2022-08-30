#include "oggex-window.h"

struct _OggexWindow {
  GtkApplicationWindow  parent_instance;

  /* Template widgets */
  GtkHeaderBar        *header_bar;
  GtkPaned            *home_paned;

  GtkStackSidebar     *home_stacksidebar;
  GtkStack            *home_stack;
  GtkStackPage        *page0;
  GtkGrid             *home_grid;
  GtkLabel            *lbl_title;

  /* Custom Widgets */
  EmbedWidget         *embed_widget;
  ExtractWidget       *extract_widget;
};

G_DEFINE_TYPE (OggexWindow, oggex_window, GTK_TYPE_APPLICATION_WINDOW)

static void oggex_window_class_init (OggexWindowClass *klass) {
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  /* TODO: Free resource in oggex window destructor */
  const char* resource = get_ui_resource(UI_OGGEX_WINDOW);
  gtk_widget_class_set_template_from_resource (widget_class, resource);
  gtk_widget_class_bind_template_child (widget_class, OggexWindow, header_bar);
  gtk_widget_class_bind_template_child (widget_class, OggexWindow, home_paned);
  gtk_widget_class_bind_template_child (widget_class, OggexWindow, home_stacksidebar);
  gtk_widget_class_bind_template_child (widget_class, OggexWindow, home_stack);
  gtk_widget_class_bind_template_child (widget_class, OggexWindow, page0);
  gtk_widget_class_bind_template_child (widget_class, OggexWindow, lbl_title);
  /*free(resource);*/
}

static void oggex_window_init (OggexWindow *self) {
  GtkWidget* widget = GTK_WIDGET (self);
  gtk_widget_init_template(widget);

  /* Add EmbedWidget to the main window */
  self->embed_widget = embed_widget_new();
  gtk_stack_add_titled(self->home_stack, GTK_WIDGET(self->embed_widget), "child", "Embed");

  /* Add ExtractWidget to the main window */
  self->extract_widget = extract_widget_new();
  gtk_stack_add_titled(self->home_stack, GTK_WIDGET(self->extract_widget), "child", "Extract");
}
