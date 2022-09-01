#pragma once
#ifndef OGGEX_EXTRACTWIDGET_H
#define OGGEX_EXTRACTWIDGET_H

#include "filechooserbutton.h"
#include "cli.h"

G_BEGIN_DECLS

#define EXTRACT_WIDGET_TYPE_WIDGET (extract_widget_get_type())
G_DECLARE_FINAL_TYPE(ExtractWidget, extract_widget, OGGEX, EXTRACT_WIDGET, GtkGrid)
  
struct _ExtractWidget {
  GtkGrid parent_instance;

  /* Template widgets */
  GtkLabel              *lbl_extract;
  GtkLabel              *lbl_embedded;
  FileChooserButton     *fcb_embedded;
  GtkLabel              *lbl_dest;
  FileChooserButton     *fcb_dest;
  GtkButton             *btn_extract;
};

ExtractWidget* extract_widget_new (void);
static void extract_callback(GtkButton* self, gpointer user_data);

G_END_DECLS
#endif // OGGEX_EXTRACTWIDGET_H
