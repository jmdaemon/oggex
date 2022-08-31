#pragma once
#ifndef OGGEX_GTK_APP_H
#define OGGEX_GTK_APP_H

/* Support header include for C++ */
#ifdef __cplusplus
extern "C" {
#endif

#include <gtk/gtk.h>

G_BEGIN_DECLS

#define OGGEX_TYPE_APPLICATION (oggex_application_get_type())

G_DECLARE_FINAL_TYPE (OggexApplication, oggex_application, OGGEX, APPLICATION, GtkApplication)

OggexApplication *oggex_application_new (gchar *application_id, GApplicationFlags flags);

G_END_DECLS

#ifdef __cplusplus
}
#endif

#endif // OGGEX_GTK_APP_H
