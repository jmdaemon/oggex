#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <gtkmm.h>
#include "DashboardWindow.h"

class DashboardWindow;
class Dashboard : public Gtk::Application {
  private: 
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    //Gtk::Button* embedWindow;
    //Gtk::Button* extractWindow;

    DashboardWindow* create_appwindow();
    void on_hide_window(Gtk::Window* window);

  protected:
    Dashboard();

    void on_startup() override;
    void on_activate() override;

    void on_navigate();

    void on_button_embed_clicked();
    void on_button_extract_clicked();

  public:
    static Glib::RefPtr<Dashboard> create();
};

#endif
