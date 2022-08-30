#pragma once
#ifndef OGGEX_APPWINDOW_H
#define OGGEX_APPWINDOW_H

#include <gtkmm.h>

class AppWindow : public Gtk::ApplicationWindow {
protected:
  Glib::RefPtr<Gtk::Builder> builder;
public:
  AppWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& builder);

  static AppWindow* create();

  void open_file_view(const Glib::RefPtr<Gio::File>& file);
};

#endif // OGGEX_APP_WINDOW_H
