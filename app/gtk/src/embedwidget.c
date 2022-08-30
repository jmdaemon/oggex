#include "embedwidget.h"

struct _EmbedWidget {
  GtkWidget parent_instance;

  /* Template widgets */
  /*GtkHeaderBar        *header_bar;*/
  /*GtkPaned            *home_paned;*/

  GtkGrid               *embed_grid;
  GtkLabel              *lbl_dest;
  GtkLabel              *lbl_tag;
  /*GtkButton             *lbl_tag;*/
  GtkLabel              *lbl_audio;
  /*GtkButton             *lbl_tag;*/
  GtkLabel              *lbl_image;
  GtkLabel              *lbl_embed;
  GtkEntry              *e_tag;
  GtkEntry              *e_dest;
  GtkButton             *btn_embed;
};

G_DEFINE_TYPE (EmbedWidget, embed_widget, EMBED_WIDGET_TYPE_WIDGET)

static void embed_widget_class_init (EmbedWidgetClass *klass) {
  GtkWidgetClass *widget_class = GTK_WIDGET_CLASS (klass);

  /*gtk_widget_class_set_template_from_resource (widget_class, "/io/github/com/jmdaemon/oggex/../../../resources/gtk/oggex-window.ui");*/
  /* TODO: Free resource in oggex window destructor */
  const char* resource = "/io/github/com/jmdaemon/oggex/../../../resources/gtk/embedwidget.ui";
  gtk_widget_class_set_template_from_resource (widget_class, resource);
  gtk_widget_class_bind_template_child (widget_class, EmbedWidget, embed_grid);
  gtk_widget_class_bind_template_child (widget_class, EmbedWidget, lbl_dest);
  gtk_widget_class_bind_template_child (widget_class, EmbedWidget, lbl_dest);
  gtk_widget_class_bind_template_child (widget_class, EmbedWidget, lbl_tag);
  /*gtk_widget_class_bind_template_child (widget_class, OggexWindow, label);*/
  gtk_widget_class_bind_template_child (widget_class, EmbedWidget, lbl_audio);
  /*gtk_widget_class_bind_template_child (widget_class, OggexWindow, label);*/
  gtk_widget_class_bind_template_child (widget_class, EmbedWidget, lbl_image);
  gtk_widget_class_bind_template_child (widget_class, EmbedWidget, lbl_embed);
  gtk_widget_class_bind_template_child (widget_class, EmbedWidget, e_tag);
  gtk_widget_class_bind_template_child (widget_class, EmbedWidget, e_dest);
  gtk_widget_class_bind_template_child (widget_class, EmbedWidget, btn_embed);
  /*free(resource);*/
}

static void embed_widget_init (EmbedWidget *self) {
  gtk_widget_init_template (GTK_WIDGET (self));
}
