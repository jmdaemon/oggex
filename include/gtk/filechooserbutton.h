#pragma once
#ifndef OGGEX_FILECHOOSER_BUTTON_H
#define OGGEX_FILECHOOSER_BUTTON_H

#include "oggex-config.h"
#include <gtk/gtk.h>

G_BEGIN_DECLS

#define FILECHOOSER_BUTTON_TYPE_FILECHOOSER (filechooserbutton_get_type())
G_DECLARE_FINAL_TYPE(FileChooserButton, filechooserbutton, OGGEX, FILECHOOSER, GtkButton)

struct _FileChooserButton {
  GtkButton parent_instance;
};

/* Getters */
const char* filechooserbutton_get_prompt(FileChooserButton *self);
bool filechooserbutton_get_shortpaths(FileChooserButton *self);
GFile* filechooserbutton_get_file(FileChooserButton *self);
GtkFileChooserNative* filechooserbutton_get_fcn(FileChooserButton *self);
GtkFileChooserAction filechooserbutton_get_action(FileChooserButton *self);

/* Setters */
static void filechooserbutton_set_prompt(FileChooserButton *self, const char* prompt);
static void filechooserbutton_set_prompt(FileChooserButton *self, const char* prompt);
static void filechooserbutton_set_file(FileChooserButton *self, GFile *file);
static void filechooserbutton_set_fcn(FileChooserButton *self, GtkFileChooserNative* fcn);
static void filechooserbutton_set_action(FileChooserButton *self, GtkFileChooserAction action);

/* Signal Handlers */
static void filechooserbutton_browse(GtkNativeDialog *native, int response, gpointer user_data);
static void filechooserbutton_show(GtkButton* self, gpointer user_data);

/* Class Constructor */
FileChooserButton* filechooserbutton_new(const char* prompt, const char* filter, bool shortpaths, GtkFileChooserAction action);

G_END_DECLS

#endif // OGGEX_FILECHOOSER_BUTTON_H
