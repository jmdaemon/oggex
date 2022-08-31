#pragma once
#ifndef OGGEX_EXTRACTWIDGET_H
#define OGGEX_EXTRACTWIDGET_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define EXTRACT_WIDGET_TYPE_WIDGET (extract_widget_get_type())
G_DECLARE_DERIVABLE_TYPE(ExtractWidget, extract_widget, OGGEX, EXTRACT_WIDGET, GtkGrid)
  
struct _ExtractWidgetClass {
  GtkGridClass parent_instance;

  /* Template widgets */
  GtkLabel              *lbl_extract;
  GtkLabel              *lbl_embedded;
  GtkButton             *fc_embedded;
  GtkLabel              *lbl_dest;
  GtkButton             *fc_dest;
  GtkButton             *btn_extract;
};

ExtractWidget* extract_widget_new (void);

G_END_DECLS
#endif // OGGEX_EXTRACTWIDGET_H
