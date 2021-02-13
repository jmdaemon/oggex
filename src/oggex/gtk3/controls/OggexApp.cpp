#include "Oggex.h"
#include "OggexWindow.h"
#include "Embed.h"
#include "EmbedWindow.h"

#include <iostream>
#include <exception>

Oggex::Oggex() : Gtk::Application("com.github.jmdaemon.oggex", Gio::APPLICATION_HANDLES_OPEN) {
}

Glib::RefPtr<Oggex> Oggex::create() {
  return Glib::RefPtr<Oggex>(new Oggex());
}

OggexWindow* Oggex::create_appwindow() {
  auto appwindow = OggexWindow::create();
  auto embedWindow = EmbedWindow::create();

  add_window(*appwindow);
  add_window(*embedWindow);

  appwindow->signal_hide().connect(sigc::bind<Gtk::ApplicationWindow*>(sigc::mem_fun(*this,
    &Oggex::on_hide_window), appwindow));

  embedWindow->present();

  return appwindow;
}

void Oggex::on_activate() {
  try {
  auto appwindow = create_appwindow();
  appwindow->present();
  } catch (const Glib::Error& ex) {
    std::cerr << "Oggex::on_activate(): " << ex.what() << std::endl;
  } catch (const std::exception& ex) {
    std::cerr << "Oggex::on_activate(): " << ex.what() << std::endl;
  }

}

void Oggex::on_startup() {
  Gtk::Application::on_startup();

  m_refBuilder = Gtk::Builder::create();
  m_refBuilder->add_from_file("resources/xml/gtk3/MenuBar.ui");
  auto object = m_refBuilder->get_object("MenuBar");
  //auto gmenu = std::dynamic_pointer_cast<Gio::Menu>(object);
  auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
  if (!gmenu)
    g_warning("GMenu not found");
  else
    set_menubar(gmenu);
}

void Oggex::on_hide_window(Gtk::Window* window) {
  delete window;
}

void Oggex::on_navigate() {

  //OggexWindow* appwindow = nullptr;
  //Gtk::ApplicationWindow* appwindow = nullptr;
  EmbedWindow* appwindow = nullptr;
  auto windows = get_windows();
  if (windows.size() > 0)
    appwindow = dynamic_cast<EmbedWindow*>(windows[1]);
    //appwindow = dynamic_cast<EmbedWindow*>(windows[0]);

  try {
    //if (!appwindow) {
      //appwindow = create_appwindow();
      //// appwindow->add_to_stack();
    //}
    appwindow->present();
  }
  catch (const Glib::Error& ex) {
    std::cerr << "Oggex::on_navigate(): " << ex.what() << std::endl;
  } catch (const std::exception& ex) {
    std::cerr << "Oggex::on_navigate(): " << ex.what() << std::endl;
  }
}

