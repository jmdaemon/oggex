#ifndef DASHBOARD_WINDOW_H
#define DASHBOARD_WINDOW_H

#include <gtkmm.h>
#include "Resources.h"

class DashboardWindow : public Gtk::ApplicationWindow {
  protected:
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    //Gtk::Button* embedWindowButton;

    Gtk::Stack* pages;
    Gtk::StackSidebar* navigationPanel;
    //Gtk::StackSwitcher* navigationPanel;
    Gtk::Grid* embedGrid;
    //Glib::RefPtr<Gtk::Grid> embedGrid;

  public: 
    //Gtk::Stack* pages;
    //Gtk::StackSidebar* navigationPanel;
    DashboardWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    static DashboardWindow* create();
};

#endif
