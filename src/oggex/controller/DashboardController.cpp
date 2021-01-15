#include "Dashboard.h"
#include "DashboardWindow.h"
#include "Embed.h"
#include "EmbedWindow.h"

#include <iostream>
#include <exception>

DashboardController::DashboardController() : Gtk::Application("com.github.jmdaemon.oggex", Gio::APPLICATION_HANDLES_OPEN) {
}

Glib::RefPtr<DashboardController> DashboardController::create() {
  return Glib::RefPtr<DashboardController>(new DashboardController());
}

DashboardWindow* DashboardController::create_appwindow() {
  auto appwindow = DashboardWindow::create();
  auto embedWindow = EmbedWindow::create();

  add_window(*appwindow);
  add_window(*embedWindow);

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

void DashboardController::on_navigate() {

  //DashboardWindow* appwindow = nullptr;
  Gtk::ApplicationWindow* appwindow = nullptr;
  auto windows = get_windows();
  if (windows.size() > 0)
    appwindow = dynamic_cast<Gtk::ApplicationWindow*>(windows[0]);
    //appwindow = dynamic_cast<EmbedWindow*>(windows[0]);

  try {
    if (!appwindow) {
      appwindow = create_appwindow();
      // appwindow->add_to_stack();
    }
    appwindow->present();
  }
  catch (const Glib::Error& ex) {
    std::cerr << "DashboardController::on_navigate(): " << ex.what() << std::endl;
  } catch (const std::exception& ex) {
    std::cerr << "DashboardController::on_navigate(): " << ex.what() << std::endl;
  }
}

