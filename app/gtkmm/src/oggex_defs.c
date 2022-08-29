#include "oggex_gtk_defs.h"
const char* get_version() {
  /*char* result[5];*/
  unsigned int size = strlen(VERSION_MAJOR) + strlen(VERSION_MINOR) + strlen(VERSION_PATCH) + 3;
  char* result = malloc(size);
  //unsigned int fname_size = strlen(APP_ID) + strlen(RESOURCES_DIR) + strlen(RESOURCES_GTK_DIR) + 3;
  sprintf(result, "%s.%s.%s", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH);
  return result;
}
