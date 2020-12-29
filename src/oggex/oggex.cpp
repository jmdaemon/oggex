#include "Dashboard.h"

#include <gtkmm.h>

#include <fmt/core.h>
#include <fmt/printf.h>

using namespace std;

int main(int argc, char *argv[]) {
  auto application = DashboardController::create();
  return application->run(argc, argv);
}
