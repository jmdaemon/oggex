#pragma once
#ifndef OGGEX_EMBEDWIDGET_H
#define OGGEX_EMBEDWIDGET_H

#include "filechooserbutton.h"

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define EMBED_WIDGET_TYPE_WIDGET (embed_widget_get_type())
G_DECLARE_DERIVABLE_TYPE(EmbedWidget, embed_widget, OGGEX, EMBED_WIDGET, GtkGrid)
  
struct _EmbedWidgetClass {
  GtkGridClass parent_instance;

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

  /* Custom Widgets */
  //FileChooserButton* fcb_image;
  //FileChooserButton* fcb_audio;
};

EmbedWidget* embed_widget_new (void);

//extern "C" void test_callback(GtkButton* self, gpointer user_data);
//extern "C" void embed_callback(GtkButton* self, gpointer user_data);
//static void test_callback(GtkButton* self, gpointer user_data);
//static void test_callback(GtkWidget* self, gpointer user_data);
static void test_callback(GtkWidget* self);

//#ifdef __cplusplus
//extern "C"
//{
//#endif

//void embed_callback(GtkButton* self, gpointer user_data);
static void embed_callback(GtkButton* self, gpointer user_data);

//#ifdef __cplusplus
//}
//#endif

G_END_DECLS

#endif // OGGEX_EMBEDWIDGET_H
