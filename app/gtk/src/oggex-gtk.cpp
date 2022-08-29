#include "app.h"

int main(int argc, char* argv[]) {
  auto app = App::create();

  // Start the application, showing the initial window,
  // and opening extra views for any files that it is asked to open,
  // for instance as a command-line parameter.
  // run() will return when the last window has been closed.
  return app->run(argc, argv);
}
