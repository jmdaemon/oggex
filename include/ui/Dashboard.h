#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <gtkmm.h>

class DashboardWindow;
class DashboardController : public Gtk::Application {
  private:
    //Gtk::Button* embedWindow;
    //Gtk::Button* extractWindow;

    DashboardWindow* create_appwindow();
    void on_hide_window(Gtk::Window* window);

  protected:
    DashboardController();

    void on_activate() override;
    void on_navigate();

    void on_button_embed_clicked();
    void on_button_extract_clicked();

  public:
    static Glib::RefPtr<DashboardController> create();
};

#endif
