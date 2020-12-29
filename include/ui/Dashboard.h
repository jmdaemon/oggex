#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <gtkmm.h>

class DashboardWindow;
class DashboardController : public Gtk::Application {
  private:
    DashboardWindow* create_appwindow();
    void on_hide_window(Gtk::Window* window);

  protected:
    DashboardController();

    // Override default signal handlers:
    void on_activate() override;
    void on_open(const Gio::Application::type_vec_files& files, const Glib::ustring& hint) override;

  public:
    static Glib::RefPtr<DashboardController> create();
};

#endif
