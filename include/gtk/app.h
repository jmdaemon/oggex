#pragma once
#ifndef OGGEX_GTKMM_APP_H
#define OGGEX_GTKMM_APP_H

#include <gtkmm.h>

class AppWindow;

class Application: public Gtk::Application {
protected:
  Application();

public:
  static Glib::RefPtr<Application> create();

protected:
  // Override default signal handlers:
  void on_activate() override;
  void on_open(const Gio::Application::type_vec_files& files, const Glib::ustring& hint) override;

private:
  AppWindow* create_appwindow();
  void on_hide_window(Gtk::Window* window);
};

#endif // OGGEX_GTKMM_APP_H
