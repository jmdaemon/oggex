#ifndef EMBED_WINDOW_H
#define EMBED_WINDOW_H

#include <gtkmm.h>

class EmbedWindow : public Gtk::ApplicationWindow {
  protected:
    Glib::RefPtr<Gtk::Builder> m_refBuilder;

  public: 
    EmbedWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
    static EmbedWindow* create();

    void on_button_embed_clicked();
    void on_button_extract_clicked();
};


#endif
