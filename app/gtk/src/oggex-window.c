#include "oggex-config.h"
#include "oggex-window.h"
#include "oggex_gtk_defs.h"

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
  GtkStackPage        *page1;
  /*GtkGrid             *embed_grid;*/
  /*EmbedWidget         *embed_widget;*/
  GtkStackPage        *page2;
  GtkGrid             *extract_grid;
  EmbedWidget         *embed_widget;
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

  gtk_widget_class_bind_template_child (widget_class, OggexWindow, home_stacksidebar);
  gtk_widget_class_bind_template_child (widget_class, OggexWindow, home_stack);
  gtk_widget_class_bind_template_child (widget_class, OggexWindow, page0);
  gtk_widget_class_bind_template_child (widget_class, OggexWindow, lbl_title);
  gtk_widget_class_bind_template_child (widget_class, OggexWindow, page1);
  /*gtk_widget_class_bind_template_child (widget_class, OggexWindow, embed_grid);*/
  /*gtk_widget_class_bind_template_child (widget_class, OggexWindow, embed_widget);*/
  gtk_widget_class_bind_template_child (widget_class, OggexWindow, page2);
  gtk_widget_class_bind_template_child (widget_class, OggexWindow, extract_grid);
  /*free(resource);*/
}

static void oggex_window_init (OggexWindow *self) {
  GtkWidget* widget = GTK_WIDGET (self);
  gtk_widget_init_template(widget);

  /*GtkWidget* embedwidget = GTK_WIDGET(self->embed_widget);*/
  /*gtk_widget_init_template(embedwidget);*/
  
  self->embed_widget = embed_widget_new();

  /*gtk_widget_get_first_child(widget);*/
  /*gtk_stack_add_child(self->home_stack, GTK_WIDGET(self->embed_widget));*/
  /*gtk_stack_add_child(self->home_stack, GTK_WIDGET(self->embed_widget));*/
  gtk_stack_add_titled(self->home_stack, GTK_WIDGET(self->embed_widget), "child", "Embed");
  /*gtk_stack_add_child(self->home_stack, self.embedwidget);*/

  /*gtk_widget_add*/
  /*gtk_widget_init_template(GTK_WIDGET(self->embed_widget));*/
  
  /*self->page0;*/
  
  /*self->home_paned;*/
  /*GtkWidget *page = gtk_widget_get_first_child (widget);*/
  /*gtk_widget_get_next_sibling (child);*/

  /*for(*/
     /*child != NULL;*/
     /*child = gtk_widget_get_next_sibling (child))*/

  
  /*for(page = gtk_widget_get_first_child (widget);*/
     /*child != NULL;*/
     /*child = gtk_widget_get_next_sibling (child))*/

  /*
  GtkWidget *child;
  char* name;
  for (child = gtk_widget_get_first_child (widget);
     child != NULL;
     child = gtk_widget_get_next_sibling (child)) {

    // Do stuff with @child 
    g_assert (gtk_widget_get_parent (child) == widget);
    name = gtk_widget_get_name(child);
    printf("Widget: %s\n", name);
  }
  */
}
