#pragma once
#ifndef OGGEX_EMBEDWIDGET_H
#define OGGEX_EMBEDWIDGET_H

#include "filechooserbutton.h"

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define EMBED_WIDGET_TYPE_WIDGET (embed_widget_get_type())
G_DECLARE_FINAL_TYPE(EmbedWidget, embed_widget, OGGEX, EMBED_WIDGET, GtkGrid)
  
struct _EmbedWidget {
  GtkGrid parent_instance;

  /* Template widgets */
  GtkLabel              *lbl_dest;
  GtkLabel              *lbl_tag;
  GtkLabel              *lbl_image;
  FileChooserButton     *fcb_image;
  GtkLabel              *lbl_audio;
  FileChooserButton     *fcb_audio;
  GtkLabel              *lbl_embed;
  GtkEntry              *e_tag;
  GtkEntry              *e_dest;
  GtkButton             *btn_embed;
};

EmbedWidget* embed_widget_new (void);
static void embed_callback(GtkButton* self, gpointer user_data);

G_END_DECLS

#endif // OGGEX_EMBEDWIDGET_H
