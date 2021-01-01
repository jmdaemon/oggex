#include "Dashboard.h"
#include "Embed.h"

#include <gtkmm.h>

#include <fmt/core.h>
#include <fmt/printf.h> 

using namespace std;

int main(int argc, char *argv[]) {
  //auto application = DashboardController::create();
  auto application = EmbedController::create();
  return application->run(argc, argv);
}
