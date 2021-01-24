#include "Embed.h"
#include "EmbedWindow.h"

#include <iostream>
#include <exception>

#include <gtkmm.h>

Embed::Embed() : Gtk::Application("com.github.jmdaemon.oggex", Gio::APPLICATION_HANDLES_OPEN) {
}

Glib::RefPtr<Embed> Embed::create() {
  return Glib::RefPtr<Embed>(new Embed());
}

EmbedWindow* Embed::create_appwindow() {
  auto appwindow = EmbedWindow::create();

  add_window(*appwindow);

  appwindow->signal_hide().connect(sigc::bind<Gtk::ApplicationWindow*>(sigc::mem_fun(*this,
    &Embed::on_hide_window), appwindow));
  return appwindow;
}


void Embed::on_activate() {
  try {
  auto appwindow = create_appwindow();
  appwindow->present();
  } catch (const Glib::Error& ex) {
    std::cerr << "Embed::on_activate(): " << ex.what() << std::endl;
  } catch (const std::exception& ex) {
    std::cerr << "Embed::on_activate(): " << ex.what() << std::endl;
  }

}

void Embed::on_startup() {
}

void Embed::on_hide_window(Gtk::Window* window) {
  delete window;
}
