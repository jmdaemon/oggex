#pragma once
#ifndef OGGEX_EMBEDWIDGET_H
#define OGGEX_EMBEDWIDGET_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define EMBED_WIDGET_TYPE_WIDGET (embed_widget_get_type())

//G_DECLARE_FINAL_TYPE (EmbedWidget, embed_widget, OGGEX, WIDGET, GtkWidget)
//G_DECLARE_DERIVABLE_TYPE(EmbedWidget, embed_widget, OGGEX, WIDGET, GtkWidget)
G_DECLARE_DERIVABLE_TYPE(EmbedWidget, embed_widget, OGGEX, WIDGET, GtkGrid)
  
struct _EmbedWidgetClass {
  //GtkWidget parent_instance;
  //GtkWidgetClass parent_instance;
  GtkGridClass parent_instance;

  /* Template widgets */
  /*GtkHeaderBar        *header_bar;*/
  /*GtkPaned            *home_paned;*/

  //GtkGrid               *embed_grid;
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

EmbedWidget* embed_widget_new (void);

G_END_DECLS
#endif // OGGEX_EMBEDWIDGET_H
