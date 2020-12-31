#ifndef EMBED_H
#define EMBED_H

#include <gtkmm.h>

class EmbedWindow;
class EmbedController : public Gtk::Application {
  private:
    EmbedWindow* create_appwindow();
    void on_hide_window(Gtk::Window* window);

  protected:
    EmbedController();

    // Override default signal handlers:
    void on_activate() override;
    void on_open(const Gio::Application::type_vec_files& files, const Glib::ustring& hint) override;

  public:
    static Glib::RefPtr<EmbedController> create();
};

#endif 
