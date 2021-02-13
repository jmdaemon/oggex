#include "OggexApp.h"
#include "OggexWin.h"
#include "Embed.h"
#include "EmbedWindow.h"

#include <iostream>
#include <exception>

OggexApp::OggexApp() : Gtk::Application("com.github.jmdaemon.oggex", Gio::APPLICATION_HANDLES_OPEN) {
}

Glib::RefPtr<OggexApp> OggexApp::create() {
  return Glib::RefPtr<OggexApp>(new OggexApp());
}

OggexWin* OggexApp::create_appwindow() {
  auto appwindow = OggexWin::create();
  auto embedWindow = EmbedWindow::create();

  add_window(*appwindow);
  add_window(*embedWindow);

  appwindow->signal_hide().connect(sigc::bind<Gtk::ApplicationWindow*>(sigc::mem_fun(*this,
    &OggexApp::on_hide_window), appwindow));

  embedWindow->present();

  return appwindow;
}

void OggexApp::on_activate() {
  try {
  auto appwindow = create_appwindow();
  appwindow->present();
  } catch (const Glib::Error& ex) {
    std::cerr << "OggexApp::on_activate(): " << ex.what() << std::endl;
  } catch (const std::exception& ex) {
    std::cerr << "OggexApp::on_activate(): " << ex.what() << std::endl;
  }

}

void OggexApp::on_startup() {
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

void OggexApp::on_hide_window(Gtk::Window* window) {
  delete window;
}

void OggexApp::on_navigate() {

  //OggexWin* appwindow = nullptr;
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
    std::cerr << "OggexApp::on_navigate(): " << ex.what() << std::endl;
  } catch (const std::exception& ex) {
    std::cerr << "OggexApp::on_navigate(): " << ex.what() << std::endl;
  }
}

