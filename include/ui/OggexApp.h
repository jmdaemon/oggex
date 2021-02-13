#ifndef OGGEX_APP_H
#define OGGEX_APP_H

#include <gtkmm.h>
#include "OggexWin.h"

class OggexWin;
class OggexApp : public Gtk::Application {
  private: 
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    //Gtk::Button* embedWindow;
    //Gtk::Button* extractWindow;

    OggexWin* create_appwindow();
    void on_hide_window(Gtk::Window* window);

  protected:
    OggexApp();

    void on_startup() override;
    void on_activate() override;

    void on_navigate();

    void on_button_embed_clicked();
    void on_button_extract_clicked();

  public:
    static Glib::RefPtr<OggexApp> create();
};

#endif
