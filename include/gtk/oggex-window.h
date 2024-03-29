#pragma once
#ifndef OGGEX_GTK_WINDOW_H
#define OGGEX_GTK_WINDOW_H

#include "embedwidget.h"
#include "extractwidget.h"

G_BEGIN_DECLS

#define OGGEX_TYPE_WINDOW (oggex_window_get_type())

G_DECLARE_FINAL_TYPE (OggexWindow, oggex_window, OGGEX, WINDOW, GtkApplicationWindow)

G_END_DECLS

#endif // OGGEX_GTK_WINDOW_H
