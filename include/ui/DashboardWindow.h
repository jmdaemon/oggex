#ifndef DASHBOARD_WINDOW_H
#define DASHBOARD_WINDOW_H

#include <gtkmm.h>

class DashboardWindow : public Gtk::ApplicationWindow {
  protected:
    Glib::RefPtr<Gtk::Builder> m_refBuilder;

  public: 
    DashboardWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    static DashboardWindow* create();
};

#endif
