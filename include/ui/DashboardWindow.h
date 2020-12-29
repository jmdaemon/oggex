#ifndef DASHBOARD_WINDOW_H
#define DASHBOARD_WINDOW_H

#include <gtkmm.h>

class DashboardWindow : public Gtk::ApplicationWindow {
  public:
  DashboardWindow();
  void open_file_view(const Glib::RefPtr<Gio::File>& file);
};

#endif
