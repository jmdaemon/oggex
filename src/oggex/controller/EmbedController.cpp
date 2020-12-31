#include "Embed.h"

#include <gtkmm.h>

EmbedController::EmbedController() : Gtk::Application("com.github.jmdaemon.oggex", Gio::APPLICATION_HANDLES_OPEN) {
}

Glib::RefPtr<EmbedController> EmbedController::create() {
  return Glib::RefPtr<EmbedController>(new EmbedController());
}

EmbedWindow* EmbedController::create_appwindow() {
  auto appwindow = DashboardWindow::create();

  add_window(*appwindow);

  appwindow->signal_hide().connect(sigc::bind<Gtk::ApplicationWindow*>(sigc::mem_fun(*this,
    &EmbedController::on_hide_window), appwindow));
}


void EmbedController::on_activate() {
  try {
  auto appwindow = create_appwindow();
  appwindow->present();
  } catch (const Glib::Error& ex) {
    std::cerr << "EmbedController::on_activate(): " << ex.what() << std::endl;
  } catch (const std::exception& ex) {
    std::cerr << "EmbedController::on_activate(): " << ex.what() << std::endl;
  }

}

void EmbedController::on_hide_window(Gtk::Window* window) {
  delete window;
}
