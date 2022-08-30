#pragma once
#ifndef OGGEX_GTK_DEFS_H
#define OGGEX_GTK_DEFS_H

#include "Version.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <gtk/gtk.h>

static const char* APP_ID = "/io/github/com/jmdaemon/oggex";
static const char* RESOURCES_DIR = "../../../resources";
static const char* RESOURCES_GTK_DIR = "gtk";

/* UI Files */
static const char* UI_OGGEX_WINDOW = "oggex-window.ui";
static const char* UI_HELP_OVERLAY = "help-overlay.ui";

static const char* PROGRAM_NAME = "oggex";
static const gchar *authors[] = {"Joseph Diza", NULL};

const char* get_version();
const char* get_ui_resource(const char* ui_file);

#endif // OGGEX_GTK_DEFS_H
