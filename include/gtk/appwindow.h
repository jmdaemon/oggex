#pragma once
#ifndef OGGEX_APPWINDOW_H
#define OGGEX_APPWINDOW_H

#include <gtkmm.h>

class AppWindow : public Gtk::ApplicationWindow {
public:
  AppWindow();

  void open_file_view(const Glib::RefPtr<Gio::File>& file);
};

#endif // OGGEX_APP_WINDOW_H
