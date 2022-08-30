#pragma once
#ifndef OGGEX_EMBEDWIDGET_H
#define OGGEX_EMBEDWIDGET_H

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define EMBED_WIDGET_TYPE_WIDGET (embed_widget_get_type())

G_DECLARE_FINAL_TYPE (EmbedWidget, embed_widget, OGGEX, WIDGET, GtkWidget)

G_END_DECLS
#endif // OGGEX_EMBEDWIDGET_H
