#include "Dashboard.h"
#include "DashboardWindow.h"
#include "Embed.h"
#include "EmbedWindow.h"

#include <iostream>
#include <exception>

Dashboard::Dashboard() : Gtk::Application("com.github.jmdaemon.oggex", Gio::APPLICATION_HANDLES_OPEN) {
}

Glib::RefPtr<Dashboard> Dashboard::create() {
  return Glib::RefPtr<Dashboard>(new Dashboard());
}

DashboardWindow* Dashboard::create_appwindow() {
  auto appwindow = DashboardWindow::create();
  auto embedWindow = EmbedWindow::create();

  add_window(*appwindow);
  add_window(*embedWindow);

  appwindow->signal_hide().connect(sigc::bind<Gtk::ApplicationWindow*>(sigc::mem_fun(*this,
    &Dashboard::on_hide_window), appwindow));

  embedWindow->present();

  return appwindow;
}

void Dashboard::on_activate() {
  try {
  auto appwindow = create_appwindow();
  appwindow->present();
  } catch (const Glib::Error& ex) {
    std::cerr << "Dashboard::on_activate(): " << ex.what() << std::endl;
  } catch (const std::exception& ex) {
    std::cerr << "Dashboard::on_activate(): " << ex.what() << std::endl;
  }

}

void Dashboard::on_startup() {
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

void Dashboard::on_hide_window(Gtk::Window* window) {
  delete window;
}

void Dashboard::on_navigate() {

  //DashboardWindow* appwindow = nullptr;
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
    std::cerr << "Dashboard::on_navigate(): " << ex.what() << std::endl;
  } catch (const std::exception& ex) {
    std::cerr << "Dashboard::on_navigate(): " << ex.what() << std::endl;
  }
}

