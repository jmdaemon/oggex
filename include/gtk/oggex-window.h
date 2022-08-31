#pragma once
#ifndef OGGEX_GTK_WINDOW_H
#define OGGEX_GTK_WINDOW_H

/* Support header include for C++ */
#ifdef __cplusplus
extern "C" {
#endif

#include "oggex-config.h"
#include "oggex_gtk_defs.h"
#include "embedwidget.h"
#include "extractwidget.h"
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define OGGEX_TYPE_WINDOW (oggex_window_get_type())

G_DECLARE_FINAL_TYPE (OggexWindow, oggex_window, OGGEX, WINDOW, GtkApplicationWindow)

G_END_DECLS

#ifdef __cplusplus
}
#endif

#endif // OGGEX_GTK_WINDOW_H
