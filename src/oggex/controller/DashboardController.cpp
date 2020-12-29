#include "Dashboard.h"
#include "DashboardWindow.h"

//#include <giomm/application.h>
//#include <gio/gio.h>
DashboardController::DashboardController() : Gtk::Application("com.github.jmdaemon.oggex", Gio::APPLICATION_HANDLES_OPEN) {
}

Glib::RefPtr<DashboardController> DashboardController::create() {
  return Glib::RefPtr<DashboardController>(new DashboardController());
}

DashboardWindow* DashboardController::create_appwindow() {
  auto appwindow = new DashboardWindow();

  add_window(*appwindow);

  appwindow->signal_hide().connect(sigc::bind(sigc::mem_fun(*this,
    &DashboardController::on_hide_window), appwindow));

  return appwindow;
}

void DashboardController::on_activate() {
  auto appwindow = create_appwindow();
  appwindow->present();
}

void DashboardController::on_open(const Gio::Application::type_vec_files& files,
  const Glib::ustring& ) {
  DashboardWindow* appwindow = nullptr;
  auto windows = get_windows();
  if (windows.size() > 0)
    appwindow = dynamic_cast<DashboardWindow*>(windows[0]);

  if (!appwindow)
    appwindow = create_appwindow();

  for (const auto& file : files)
    appwindow->open_file_view(file);

  appwindow->present();
}

void DashboardController::on_hide_window(Gtk::Window* window) {
  delete window;
}

