#include "Dashboard.h"
#include "DashboardWindow.h"

#include <iostream>
#include <exception>

DashboardController::DashboardController() : Gtk::Application("com.github.jmdaemon.oggex", Gio::APPLICATION_HANDLES_OPEN) {
}

Glib::RefPtr<DashboardController> DashboardController::create() {
  return Glib::RefPtr<DashboardController>(new DashboardController());
}

DashboardWindow* DashboardController::create_appwindow() {
  auto appwindow = DashboardWindow::create();

  add_window(*appwindow);

  appwindow->signal_hide().connect(sigc::bind<Gtk::ApplicationWindow*>(sigc::mem_fun(*this,
    &DashboardController::on_hide_window), appwindow));

  return appwindow;
}

void DashboardController::on_activate() {
  try {
  auto appwindow = create_appwindow();
  appwindow->present();
  } catch (const Glib::Error& ex) {
    std::cerr << "DashboardController::on_activate(): " << ex.what() << std::endl;
  } catch (const std::exception& ex) {
    std::cerr << "DashboardController::on_activate(): " << ex.what() << std::endl;
  }

}

void DashboardController::on_hide_window(Gtk::Window* window) {
  delete window;
}

