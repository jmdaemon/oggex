#ifndef EMBED_H
#define EMBED_H

#include <gtkmm.h>

class EmbedWindow;
class Embed : public Gtk::Application {
  private:
    EmbedWindow* create_appwindow();
    void on_hide_window(Gtk::Window* window);

  protected:
    Embed();

    void on_activate() override;

  public:
    //EmbedWindow* create_appwindow();
    static Glib::RefPtr<Embed> create();
};

#endif 
